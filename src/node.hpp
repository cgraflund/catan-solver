#pragma once
#include <unordered_set>
#include <iostream>

#include "tile.hpp"
#include "utility.hpp"

struct Node {
    Node(int row, int col): row{row}, col{col}  {}

    int row;
    int col;
    std::unordered_set<Node*> adjacent_nodes;
    std::unordered_set<Tile*> adjacent_tiles;

    int player = 0;

    void printAdjTiles() {
        std::cout << "Size: " << adjacent_tiles.size() << std::endl;
        for (Tile* t: adjacent_tiles) {
            std::cout << "Row: " << t->row << " Col: " << t->col << std::endl;
        }
    }

    bool isValidSpace() {
        if (player != 0) {
            return false;
        }
        for (Node* node: adjacent_nodes) {
            if (node->player != 0) {
                return false;
            }
        }
        return true;
    }

    float calculateUtility(Utility utility) {
        float total_utility = 0;
        for (Tile* t: adjacent_tiles) {
            total_utility += token_probability.at(t->token) * utility.getUtility(t->resource);
        }
        return total_utility;
    }
};