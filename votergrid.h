#ifndef VOTERGRID_H
#define VOTERGRID_H

#include <random>
#include <cstddef>
#include <utility>
#include <queue>
#include <vector>

typedef std::pair<float,int> voter;

class VoterGrid
{
public:
    VoterGrid();

    void initialize(int width, int height, double theta);
    voter step();
    void start();
    void stop();
    bool get_opinion(int x, int y);
    int get_width();
    int get_height();
    int get_row(int index);
    int get_col(int index);

private:
    bool* grid = nullptr;
    int width;
    int height;
    int size;
    float cur_time = 0.0f;
    int decisions = 0;

    std::mt19937 gen{std::random_device{}()};
    std::exponential_distribution<double> exp_dist{1};
    std::uniform_int_distribution<int> unif_dist{0,3};
    std::priority_queue<voter, std::vector<voter>, std::greater<voter> > queue;

    int index(int x, int y);
};

#endif // VOTERGRID_H
