#include "board.hpp"

#include <iostream>


void Board::init_nodes() {
    int height = (board_radius + 1) * 2;

    for (int row = 0; row < height; row++) {
        std::vector<Node> row_vec;

        int width = height + 1;
        if (row < height / 2)
            width += (row % (height / 2)) * 2;
        else
            width += ((height - row - 1) % (height / 2)) * 2 ;
        for (int col = 0; col < width; col++) {
            row_vec.push_back(Node(row, col));
        }
        board_nodes.push_back(row_vec);
    }
}

void Board::init_tiles() {
    int height = board_radius * 2 + 1;

    for (int row = 0; row < height; row++) {
        std::vector<Tile> row_vec;
        int width = board_radius + 1;
        if (row <= board_radius)
            width += row % (board_radius + 1);
        else
            width += (height - row - 1) % (board_radius + 1);
        for (int col = 0; col < width; col++) {
            Tile tile;// = getTile(); // return a random tile from tileset
            row_vec.push_back(tile);
        }
        board_tiles.push_back(row_vec);
    }
}

void Board::calc_adj() {

    for (int row = 0; row < board_nodes.size(); row++) {
        for (int col = 0; col < board_nodes[row].size(); col++) {
            // Horizontal Connections:
            if (col != 0) {
                board_nodes[row][col].adjacent_nodes.emplace(&board_nodes[row][col - 1]);
            }
            if (col != board_nodes[row].size() - 1) {
                board_nodes[row][col].adjacent_nodes.emplace(&board_nodes[row][col + 1]);
            }

            // Vertical Connections
            if (row < board_radius + 1) {
                // Even column
                if (col % 2 == 0 && row != board_nodes.size() - 1) {
                    if (row != board_radius) {
                        board_nodes[row][col].adjacent_nodes.emplace(&board_nodes[row + 1][col + 1]);
                    }
                    // Exception for middle rows
                    else {
                        board_nodes[row][col].adjacent_nodes.emplace(&board_nodes[row + 1][col]);
                    }      
                }
                // Odd column
                else if (col % 2 == 1 && row != 0) {
                    board_nodes[row][col].adjacent_nodes.emplace(&board_nodes[row - 1][col - 1]);
                }

            } 
            else {
                // Even col
                if (col % 2 == 0 && row != 0) {
                    if (row != board_radius + 1) {
                        board_nodes[row][col].adjacent_nodes.emplace(&board_nodes[row - 1][col + 1]);
                    }
                    // Exception for middle rows
                    else {
                        
                        board_nodes[row][col].adjacent_nodes.emplace(&board_nodes[row - 1][col]);
                    } 
                }
                // Odd col
                else if (col % 2 == 1 && row != board_nodes.size() - 1) {
                    board_nodes[row][col].adjacent_nodes.emplace(&board_nodes[row + 1][col - 1]);
                }
            }
        }
    }
}