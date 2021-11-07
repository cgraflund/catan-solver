#pragma once
#include "board.hpp"
#include "utility.hpp"
#include "player.hpp"

struct Game {
    Board board;
    int num_players;
    std::map<int, Player> players;
    std::map<int, Utility> player_utilities;
    std::queue<int> turns;

    Game(int board_radius, int num_players):num_players(num_players) {
        board = Board(board_radius);
        init_players();
        init_turns();
    };

    void playGame() {
        std::cout << "Starting game..." << std::endl;
        board.print_resources();

        while (!turns.empty()) {
            int currentPlayer = turns.front();
            turns.pop();
            players.at(currentPlayer).makeBestMove(player_utilities, board, turns);
            board.print_board();
        }
        board.evaluate_payoffs(player_utilities);
        board.print_payoffs();
    };

private:
    void init_players() {
        Utility default_utility(1, 1, 1, 1, 1);

        for (int i = 1; i <= num_players; i++) {
            players.insert({i, Player(i)});
            player_utilities.insert({i, default_utility});
        }
    }

    void init_turns() {
        for (int i = 1; i <= num_players; i++) {
            turns.push(i);
        }
        for (int i = num_players; i >= 1; i--) {
            turns.push(i);
        }
    }

};