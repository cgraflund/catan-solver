#include <iostream>
#include <vector>

#include "board.hpp"


int main() {
    srand((unsigned int)time(NULL));
    Board board(2);

    // for (std::vector<Node> row: board.board_nodes) {
    //     for (Node col: row) {
    //         std::cout << "a";
    //     }
    //     std:: cout << "\n";

    // }

    for (std::vector<Tile> row: board.board_tiles) {
        for (Tile col: row) {
            std::cout << "Resource: " << col.resource << " Token: " << col.token << std::endl;
        }
        

    }

    // for (Node* n: board.board_nodes[5][1].adjacent_nodes) {
    //     std::cout << "Node: (" << n->row << "," << n->col << ")\n";
    // }

    return 0;
}