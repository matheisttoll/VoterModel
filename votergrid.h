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

typedef std::pair<float,int> voter;
typedef float simuliation_time;

template<int dim>
class VoterGrid
{

public:
    typedef std::array<int, dim> GridCoord;
    VoterGrid(GridCoord);

    void initialize(GridCoord coord, double theta);
    voter step();
    //void start();
    //void stop();
    bool get_opinion(GridCoord coord);
    GridCoord get_dimensions();
    GridCoord coordinates(int index);

    bool get_opinion(int index);
private:
    bool* grid = nullptr;
    GridCoord grid_dimensions;
    int size;
    float cur_time = 0.0f;
    int decisions = 0;

    std::mt19937 gen{std::random_device{}()};
    std::exponential_distribution<double> exp_dist{1};
    std::bernoulli_distribution bernoulli{0.5};
    std::uniform_int_distribution<int> dimension_dist{0,dim-1};
    std::priority_queue<voter, std::vector<voter>, std::greater<voter> > queue;

    int index(GridCoord coord);
};

template<int dim>
VoterGrid<dim>::VoterGrid(GridCoord dimensions) {
    initialize(dimensions, 0.5);
}

template<int dim>
void VoterGrid<dim>::initialize(GridCoord dimensions, double theta) {
    grid_dimensions = dimensions;
    size = std::accumulate(grid_dimensions.begin(), grid_dimensions.end(), 1, std::multiplies<int>());
    if(grid) {
        delete [] grid;
    }
    grid = new bool[size];

    while(!queue.empty()) {
        queue.pop();
    }

    std::bernoulli_distribution initial_dist(theta);
    for(int i = 0; i < size; i++) {
        grid[i] = initial_dist(gen);
        queue.push(std::make_pair(exp_dist(gen),i));
    }
}

template<int dim>
voter VoterGrid<dim>::step() {
    voter voter_to_change = queue.top();
    queue.pop();
    int min_index = std::get<1>(voter_to_change);

    GridCoord neighbour = coordinates(min_index);
    neighbour[dimension_dist(gen)] += bernoulli(gen)? 1: -1;
    grid[min_index] = get_opinion(neighbour);

    cur_time = std::get<0>(voter_to_change);
    queue.push(std::make_pair(cur_time + exp_dist(gen), min_index));

    //std::cout << "Zeit: " << cur_time << " und Voter: " << min_index << std::endl;
    return voter_to_change;
}

template<int dim>
int VoterGrid<dim>::index(GridCoord coord) {
    int accum = 0;
    int temp = 1;
    //std::cout << "Koordinaten: ";
    for(int i = 0; i < dim; i++) {
        //std::cout << coord[i] << " ";
        accum += temp * ((coord[i] + grid_dimensions[i]) % grid_dimensions[i]);
        temp *= grid_dimensions[i];
    }
    //std::cout << accum << std::endl;
    //std::cout << std::endl << "Index: " << accum << std::endl;
    return accum;
}

template<int dim>
typename VoterGrid<dim>::GridCoord VoterGrid<dim>::coordinates(int index) {
    typename VoterGrid<dim>::GridCoord coords;
    //std::cout << "Index = " << index << ", Coordinates: ";
    for(int i = 0; i < dim; i++) {
        coords[i] = index % grid_dimensions[i];
        index /= grid_dimensions[i];
        //std::cout << coords.at(i) << " ";
    }
    //std::cout << std::endl;
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


#endif // VOTERGRID_H
