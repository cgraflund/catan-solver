#pragma once
#include "board.hpp"
#include "game.hpp"

#include <iostream>
#include <map>
#include <tuple>

struct Player {
    Player(int num):player(num) {}
    Player() = default;

    int player;

    void makeBestMove(std::map<int, Utility>& utilities, Board& board, std::queue<int> turns) {
        std::vector<std::tuple<Board, int, int>> states = board.getPossibleMoves(player);
        float score;
        float bestScore = std::numeric_limits<float>::lowest();
        std::pair<int, int> bestMove = {0,0};
        for (auto s: states) {
            auto& [state, row, col] = s;
            score = minimax(utilities, state, turns, std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max(), true);
            //std::cout << score << std::endl;
            std::cout << "." << std::flush;
            if (score > bestScore) {
                bestScore = score;
                
                bestMove = std::make_pair(row, col);
            }
        }
        std::cout << "Move found! Row: " << bestMove.first << " Col: " << bestMove.second << " Utility = " << bestScore << "\n";
        board.place_settlement(player, bestMove.first, bestMove.second);
    }

    float minimax(std::map<int, Utility>& utilities, Board& state, std::queue<int> turns, float alpha, float beta, bool maximize) {
        if (turns.empty()) {
            state.evaluate_payoffs(utilities);
            float utility = 0;
            for (int i = 1; i <= 2; i++) {
                if (i != player) {
                    utility += state.payoffs[player] - state.payoffs[i];
                }
                
            }
            return utility;
        }

        // Get the states for the next player
        int nextPlayer = turns.front();
        auto states = state.getPossibleMoves(nextPlayer);
        turns.pop();

        if (maximize) {
            float maxEval = std::numeric_limits<float>::lowest();
            for(auto s: states) {
                float eval = minimax(utilities, std::get<0>(s), turns, alpha, beta, player == nextPlayer);
                if (eval > maxEval) {
                    maxEval = eval;
                }
                if (eval > alpha) {
                    alpha = eval;
                }
                if (beta <= alpha) {
                    break;
                }
            }
            return maxEval;
        }
        else {
            float minEval = std::numeric_limits<float>::max();
            for(auto s: states) {
                float eval = minimax(utilities, std::get<0>(s), turns, alpha, beta, player == nextPlayer);
                if (eval < minEval) {
                    minEval = eval;
                }
                if (eval < beta) {
                    beta = eval;
                }
                if (beta <= alpha) {
                    break;
                }
            }
            return minEval;
        }
             
    }
};