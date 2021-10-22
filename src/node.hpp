#pragma once
#include <unordered_set>

#include "tile.hpp"

struct Node {
    Node(int row, int col): row{row}, col{col}  {}

    int row;
    int col;
    std::unordered_set<Node*> adjacent_nodes;
    std::unordered_set<Tile*> adjacent_tiles;
    int utility;

    int calculateUtility() {

        for (Tile* t: adjacent_tiles) {
            
        }
        return utility;
    }
};