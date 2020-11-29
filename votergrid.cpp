#include "votergrid.h"
#include <iostream>

VoterGrid::VoterGrid() {
    initialize(512, 256, 0.5);
}

void VoterGrid::initialize(int w, int h, double theta) {
    width = w;
    height = h;
    size = width * height;
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



voter VoterGrid::step() {
    voter voter_to_change = queue.top();
    queue.pop();
    int min_index = std::get<1>(voter_to_change);
    cur_time = std::get<0>(voter_to_change);

    queue.push(std::make_pair(cur_time + exp_dist(gen), min_index));
    int side = unif_dist(gen);
    int row = get_row(min_index);
    int col = get_col(min_index);
    switch (side) {
    case 0:  // links
        grid[min_index] = get_opinion(row, col-1);
        break;

    case 1:  // rechts
        grid[min_index] = get_opinion(row, col+1);
        break;

    case 2:  // oben
        grid[min_index] = get_opinion(row-1, col);
        break;

    case 3:  // unten
        grid[min_index] = get_opinion(row+1, col);
        break;

    default:
        std::cout << "Warnung: Nachbarauswahl gescheitert!" << std::endl;
        break;
    }
    //std::cout << "Zeit: " << cur_time << " und Voter: " << min_index << std::endl;
    return voter_to_change;
}

void VoterGrid::start() {

}

void VoterGrid::stop() {

}

bool VoterGrid::get_opinion(int x, int y) {
    return grid[index(x,y)];
}

int VoterGrid::get_width() {
    return width;
}

int VoterGrid::get_height() {
    return height;
}

int VoterGrid::get_row(int index) {
    return index / width;
}

int VoterGrid::get_col(int index) {
    return index % width;
}

int VoterGrid::index(int x, int y) {
    int new_x = (x + width) % width;
    int new_y = (y + height) % height;
    return width * new_y + new_x;
}
