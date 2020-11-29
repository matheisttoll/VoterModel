#include "votergrid.h"
#include <iostream>

VoterGrid::VoterGrid() {
    initialize(256, 256, 0.5);
}

void VoterGrid::initialize(int w, int h, double theta) {
    width = w;
    height = h;
    size = width * height;
    if(grid) {
        delete [] grid;
    }
    grid = new bool[size];

    if(times) {
        delete [] times;
    }
    std::bernoulli_distribution initial_dist{theta};
    times = new float[size];
    for(int i = 0; i < size; i++) {
        times[i] = exp_dist(gen);
        grid[i] = initial_dist(gen);
    }
}

float VoterGrid::step() {
    int min_index = 0;
    for(int i = 1; i < size; i++) {
        if(times[i] < times[min_index]) {
            min_index = i;
        }
    }
    float time_step = times[min_index];
    cur_time += time_step;
    for(int i = 0; i < size; i++) {
        times[i] -= time_step;
    }
    times[min_index] = exp_dist(gen);
    int side = unif_dist(gen);
    int row = size / width;
    int col = size % width;
    switch (side) {
    case 0:  // links
        grid[min_index] = grid[index(row, col-1)];
        break;

    case 1:  // rechts
        grid[min_index] = grid[index(row, col+1)];
        break;

    case 2:  // oben
        grid[min_index] = grid[index(row-1, col)];
        break;

    case 3:  // unten
        grid[min_index] = grid[index(row+1, col)];
        break;
    }
    // std::cout << time_step << std::endl;
    return time_step;
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

int VoterGrid::index(int x, int y) {
    if(y < 0) {
        y = height - 1;
    } else if(y >= height) {
        y = 0;
    } else if(x < 0) {
        x = width - 1;
    } else if(x >= width) {
        x = 0;
    }
    return width * y + x;
}
