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
            tile.row = row;
            tile.col = col;
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

void Board::calc_tile_adj() {
    for (int row = 0; row < board_nodes.size(); row++) {
        for (int col = 0; col < board_nodes[row].size(); col++) {
            // Top half of board
            if (row < board_radius + 1) {
                // Even row
                if (row % 2 == 0) {
                    // Even column
                    if (col % 2 == 0) {
                        if (col != 0) {
                            // Down left
                            board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row][col / 2 - 1]);
                        }
                        if (col != board_nodes[row].size() - 1) {
                            // Down right
                            board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row][col / 2]);
                        }
                        if (row != 0) {
                            // Straight up
                            if (col != 0 && col != board_nodes[row].size() - 1) {
                                board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row-1][col / 2 - 1]);
                            }
                        }       
                    }
                    // Odd column
                    else if (col % 2 == 1) {
                        if (row != 0) {
                            if (col != 1) {
                                // Up and to the left
                                board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row-1][col / 2 - 1]);
                            }
                            if (col != board_nodes[row].size() - 2) {
                                // Up and to the right
                                board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row-1][col / 2]);
                            }
                        }
                        if (row != board_nodes.size() - 1) {
                            // Straight up
                            board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row][col / 2]);
                        }
                    }
                }
                // Odd row
                else {
                    // Even column
                    if (col % 2 == 0) {
                        if (col != 0 && col != board_nodes[row].size() - 1) {
                            // Straight up
                            board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row-1][col / 2 - 1]);
                        }
                        if (col != 0) {
                            // Down left
                            board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row][col / 2 - 1]);
                        }
                        if (col != board_nodes[row].size() - 1) {
                            // Down right
                            board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row][col / 2]);
                        }
                    }
                    // Odd column
                    else {
                        // straight down
                        board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row][col / 2]);
                        if (col != 1) {
                            // up left
                            board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row-1][col / 2 - 1]);
                        }
                        if (col != board_nodes[row].size() - 2) {
                            // up right
                            board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row-1][col / 2]);
                        }
                    }
                }
            }
            // Bottom half of board
            else {
                // Even row
                if (row % 2 == 0) {
                    // Even col
                    if (col % 2 == 0) {
                        if (row != board_nodes.size() - 1) {
                            if (col != 0 & col != board_nodes[row].size() - 1)
                            //straight down
                            board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row][col / 2 - 1]);
                        }
                        if (col != 0) {
                            // Up left
                            board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row-1][col / 2 - 1]);
                        }
                        if (col != board_nodes[row].size() - 1) {
                            // Up right
                            board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row-1][col / 2]);
                        }
                    }
                    // Odd col
                    else {
                        // Straight up
                        board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row-1][col / 2]);

                        if (col != 1) {
                            // Down left
                            board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row][col / 2 - 1]);
                        }
                        if (col != board_nodes[row].size() - 2){
                            // Down right
                            board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row][col / 2]);
                        }
                    }
                }
                // Odd row
                else {
                    // Even col
                    if (col % 2 == 0) {
                        //std::cout << "Row: " << row << " Col: " << col << std::endl;
                        if (row != board_nodes.size() - 1 && col != 0 && col != board_nodes[row].size() - 1) {
                            //straight down
                            board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row][col / 2 - 1]);
                        }
                        if (col != 0) {
                            // Up left
                            board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row-1][col / 2 - 1]);
                        }
                        if (col != board_nodes[row].size() - 1) {
                            // Up right
                            board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row-1][col / 2]);
                        }
                    }
                    // Odd col
                    else {
                        // straight up
                        board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row-1][col / 2]);

                        if (row != board_nodes.size() - 1) {
                            if (col != 1) {
                                // Down left
                                board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row][col / 2 - 1]);
                            }
                            if (col != board_nodes[row].size() - 2) {
                                // Down right
                                board_nodes[row][col].adjacent_tiles.emplace(&board_tiles[row][col / 2]);
                            }
                        }                  
                    }
                }
            }
            
        }
    }
}

void Board::print_board() {
    for (int row = 0; row < board_nodes.size(); row++) {
        for (Node col: board_nodes[row]) {
            std::cout << col.player;
        }
        for (Tile t: )
        std::cout << "\n";

    }
}

void Board::print_resources() {
    for (std::vector<Tile> row: board_tiles) {
        for (Tile col: row) {
            std::cout << "Row: " << col.row << " Col: " << col.col << " Resource: " << col.resource << " Token: " << col.token << std::endl;
        }
    }
}  

void Board::print_tile_adj() {
    for (auto& row: board_nodes) {
        for (auto& node: row) {
            std::cout << "Node: " << node.row << " " << node.col << std::endl;
            node.printAdjTiles();
            std::cout << "\n";
        }
    }
}

void Board::print_possible_moves() {
    std::cout << "Possible moves:" << std::endl;
    for (int row = 0; row < board_nodes.size(); row++) {
        for (int col = 0; col < board_nodes[row].size(); col++) {
            if (board_nodes[row][col].isValidSpace()) {
                std::cout << "0";
            }
            else {
                std::cout << "X";
            }
        }
        std::cout << std::endl;
    }
}

void Board::print_payoffs() {
    for (int i = 1; i <= 2; i++) {
        std::cout <<"Player " << i << " payoff: " << payoffs.at(i) << std::endl;
    }
}

std::vector<std::tuple<Board, int, int>> Board::getPossibleMoves(int player) {
    std::vector<std::tuple<Board, int, int>> states;
    for (int row = 0; row < board_nodes.size(); row++) {
        for (int col = 0; col < board_nodes[row].size(); col++) {
            if (board_nodes[row][col].isValidSpace()) {
                Board new_state = *this;
                new_state.place_settlement(player, row, col);
                states.push_back({new_state, row, col});
            }
        }
    }
    return states;
}

void Board::place_settlement(int player, int row, int col) {
    board_nodes[row][col].player = player;
}

void Board::evaluate_payoffs(const std::map<int, Utility>& utilities) {
    payoffs.clear();

    for (auto& row: board_nodes) {
        for (auto& node: row) {
            if (node.player != 0) {
                payoffs[node.player] += node.calculateUtility(utilities.at(node.player));
            }
        }
    }
}