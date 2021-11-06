#include "board.hpp"

#include <iostream>

void Board::init_token_pile() {
    // Placeholder for radius 2 board
    token_pile = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};
}

// Get a random token from the token pile and remove it from the pile
int Board::draw_token() {
    int index = rand() % token_pile.size();
    int token = token_pile[index];
    token_pile.erase(token_pile.begin() + index);
    return token;
}

void Board::init_resource(Resource r, int n) {
    for (int i = 0; i < n; i++) {
        int token = 0;
        if (r != desert) {
            token = draw_token();
        }
        resource_pile.push_back(Tile(r, token));
    }
}

void Board::init_resource_pile() {
    init_resource(Resource::wood, NUM_WOOD);
    init_resource(Resource::sheep, NUM_SHEEP);
    init_resource(Resource::brick, NUM_BRICK);
    init_resource(Resource::stone, NUM_STONE);
    init_resource(Resource::wheat, NUM_WHEAT);
    init_resource(Resource::desert, NUM_DESERT);
}

Tile Board::draw_tile() {
    int index = rand() % resource_pile.size();
    Tile tile = resource_pile[index];
    resource_pile.erase(resource_pile.begin() + index);
    return tile;
}

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
            Tile tile = draw_tile();
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