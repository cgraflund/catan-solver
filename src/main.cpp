#include <iostream>
#include <vector>

#include "board.hpp"


int main() {
    Board board(2);

    for (std::vector<Node> row: board.board_nodes) {
        for (Node col: row) {
            std::cout << "a";
        }
        std:: cout << "\n";

    }

    for (std::vector<Tile> row: board.board_tiles) {
        for (Tile col: row) {
            std::cout << "b";
        }
        std:: cout << "\n";

    }

    for (Node* n: board.board_nodes[5][1].adjacent_nodes) {
        std::cout << "Node: (" << n->row << "," << n->col << ")\n";
    }

    return 0;
}