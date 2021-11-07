#pragma once
#include <vector>
#include <queue>
#include <map>
#include <tuple>
#include "node.hpp"
#include "tile.hpp"

const int NUM_WOOD = 4;
const int NUM_SHEEP = 4;
const int NUM_WHEAT = 4;
const int NUM_BRICK = 3;
const int NUM_STONE = 3;
const int NUM_DESERT = 1;

struct Board {
    int board_radius;
    std::vector<Tile> resource_pile;
    std::vector<int> token_pile;

    std::vector<std::vector<Node>> board_nodes;
    std::vector<std::vector<Tile>> board_tiles;

    std::map<int, float> payoffs;

    Board(int radius):board_radius(radius) {
        init_token_pile();
        init_resource_pile();
        init_nodes();
        init_tiles();
        calc_adj();
        calc_tile_adj();
    };

    Board() = default;

    // Board(const Board&) = delete;
    // Board(Board&&) = default;

private:
    void init_resource(Resource r, int n);
    int draw_token();
    Tile draw_tile();

    // Initialization functions
    void init_resource_pile();
    void init_token_pile();
    void init_nodes();
    void init_tiles();
    void calc_adj();
    void calc_tile_adj();
    

public:
    // Print functions
    void print_board();
    void print_resources();
    void print_tile_adj();
    void print_possible_moves();
    void print_payoffs();

    // Game functions 
    std::vector<std::tuple<Board, int, int>> getPossibleMoves(int player);
    void place_settlement(int player, int row, int col);
    void evaluate_payoffs(const std::map<int, Utility>& utilities);
};

struct BoardState {
    BoardState(Board b, int r, int c):board(b), row(r), col(c) {};

    Board board;
    int row;
    int col;
};