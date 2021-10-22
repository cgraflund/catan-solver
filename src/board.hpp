#pragma once
#include <vector>
#include "node.hpp"


struct Board {
    int board_radius;
    std::vector<std::vector<Node>> board_nodes;
    std::vector<std::vector<Tile>> board_tiles;

    Board(int radius):board_radius(radius) {
        init_nodes();
        init_tiles();
        calc_adj();
    };

    Board(const Board&) = delete;
    Board(Board&&) = default;

private:
    void init_nodes();
    void init_tiles();
    void calc_adj();
};