#ifndef VOTERGRID_H
#define VOTERGRID_H

#include <random>
#include <cstddef>
#include <utility>
#include <queue>
#include <vector>
#include <array>
#include <numeric>
#include <iostream>

typedef float simuliation_time;

template<int dim>
class VoterGrid
{

public:
    typedef std::array<int, dim> GridCoord;
    VoterGrid(GridCoord);

    void initialize(GridCoord coord, double theta);
    bool step();
    bool get_opinion(GridCoord coord);
    bool get_opinion(int index);
    bool consens();
    GridCoord coordinates(int index);
    GridCoord get_dimensions();
    GridCoord get_recent_opinion_lookaround();
private:
    bool* grid = nullptr;
    GridCoord grid_dimensions;
    int size;
    double cur_time = 0.0;
    int decisions = 0;
    int one_sites = 0;
    GridCoord recent_opinion_lookaround;

    std::mt19937 gen{std::random_device{}()};
    std::bernoulli_distribution bernoulli{0.5};
    std::uniform_int_distribution<int> dimension_dist{0,dim-1};
    std::uniform_int_distribution<int> next_voter_dist;
    std::exponential_distribution<double> waiting_time_dist;

    int index(GridCoord coord);
};

template<int dim>
VoterGrid<dim>::VoterGrid(GridCoord dimensions) {
    initialize(dimensions, 0.6);
}

template<int dim>
void VoterGrid<dim>::initialize(GridCoord dimensions, double theta) {
    grid_dimensions = dimensions;
    size = std::accumulate(grid_dimensions.begin(), grid_dimensions.end(), 1, std::multiplies<int>());
    if(grid) {
        delete [] grid;
    }
    grid = new bool[size];
    next_voter_dist = std::uniform_int_distribution<int>{0,size-1};
    waiting_time_dist = std::exponential_distribution<double>{static_cast<double>(size)};

    std::bernoulli_distribution initial_dist(theta);
    for(int i = 0; i < size; i++) {
        grid[i] = initial_dist(gen);
        one_sites += grid[i]? 1: 0;
    }
}

template<int dim>
bool VoterGrid<dim>::step() {
    cur_time += waiting_time_dist(gen);

    int voter_index = next_voter_dist(gen);
    recent_opinion_lookaround = coordinates(voter_index);

    GridCoord neighbour = recent_opinion_lookaround;
    neighbour[dimension_dist(gen)] += bernoulli(gen)? 1: -1;
    bool neighbour_opinion = get_opinion(neighbour);
    if(grid[voter_index] != neighbour_opinion) {
        one_sites += neighbour_opinion? 1: -1;
        grid[voter_index] = neighbour_opinion;
        return true;
    }

    return false;
}

template<int dim>
int VoterGrid<dim>::index(GridCoord coord) {
    int accum = 0;
    int temp = 1;
    for(int i = 0; i < dim; i++) {
        accum += temp * ((coord[i] + grid_dimensions[i]) % grid_dimensions[i]);
        temp *= grid_dimensions[i];
    }
    return accum;
}

template<int dim>
typename VoterGrid<dim>::GridCoord VoterGrid<dim>::coordinates(int index) {
    typename VoterGrid<dim>::GridCoord coords;
    for(int i = 0; i < dim; i++) {
        coords[i] = index % grid_dimensions[i];
        index /= grid_dimensions[i];
    }
    return coords;
}

template<int dim>
bool VoterGrid<dim>::get_opinion(GridCoord coord) {
    return grid[index(coord)];
}

template<int dim>
bool VoterGrid<dim>::get_opinion(int index) {
    return grid[index];
}

template<int dim>
typename VoterGrid<dim>::GridCoord VoterGrid<dim>::get_dimensions() {
    return grid_dimensions;
}

template<int dim>
typename VoterGrid<dim>::GridCoord VoterGrid<dim>::get_recent_opinion_lookaround() {
    return recent_opinion_lookaround;
}

template<int dim>
bool VoterGrid<dim>::consens() {
    return (one_sites == 0) && (one_sites == size);
}


#endif // VOTERGRID_H
