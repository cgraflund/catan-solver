#include "test.hpp"
#include "../src/board.hpp"

void testBoardSize(Board& board) {
    // Nodes
    assert(board.board_nodes[0].size() == 7);
    assert(board.board_nodes[1].size() == 9);
    assert(board.board_nodes[2].size() == 11);
    assert(board.board_nodes[3].size() == 11);
    assert(board.board_nodes[4].size() == 9);
    assert(board.board_nodes[5].size() == 7);

    // Tiles
    assert(board.board_tiles[0].size() == 3);
    assert(board.board_tiles[1].size() == 4);
    assert(board.board_tiles[2].size() == 5);
    assert(board.board_tiles[3].size() == 4);
    assert(board.board_tiles[4].size() == 3);
}

void testNodeAdj(Board& board) {
    const auto& adj1 = board.board_nodes[0][0].adjacent_nodes;
    assert(adj1.size() == 2);
    assert(adj1.count(&board.board_nodes[0][1]));
    assert(adj1.count(&board.board_nodes[1][1]));

    const auto& adj2 = board.board_nodes[2][5].adjacent_nodes;
    assert(adj2.size() == 3);
    assert(adj2.count(&board.board_nodes[1][4]));
    assert(adj2.count(&board.board_nodes[2][4]));
    assert(adj2.count(&board.board_nodes[2][6]));

    const auto& adj3 = board.board_nodes[5][1].adjacent_nodes;
    assert(adj3.size() == 2);
    assert(adj3.count(&board.board_nodes[5][0]));
    assert(adj3.count(&board.board_nodes[5][2]));

    const auto& adj4 = board.board_nodes[3][10].adjacent_nodes;
    assert(adj4.size() == 2);
    assert(adj4.count(&board.board_nodes[2][10]));
    assert(adj4.count(&board.board_nodes[3][9]));

    const auto& adj5 = board.board_nodes[2][2].adjacent_nodes;
    assert(adj5.size() == 3);
    assert(adj5.count(&board.board_nodes[2][1]));
    assert(adj5.count(&board.board_nodes[2][3]));
    assert(adj5.count(&board.board_nodes[3][2]));
}

void testTileAdj(Board& board) {
    const auto& adj1 = board.board_nodes[0][0].adjacent_tiles;
    assert(adj1.size() == 1);
    assert(adj1.count(&board.board_tiles[0][0]));

    const auto& adj2 = board.board_nodes[2][5].adjacent_tiles;
    assert(adj2.size() == 3);
    assert(adj2.count(&board.board_tiles[1][1]));
    assert(adj2.count(&board.board_tiles[1][2]));
    assert(adj2.count(&board.board_tiles[2][2]));

    const auto& adj3 = board.board_nodes[4][2].adjacent_tiles;
    assert(adj3.size() == 3);
    assert(adj3.count(&board.board_tiles[3][0]));
    assert(adj3.count(&board.board_tiles[3][1]));
    assert(adj3.count(&board.board_tiles[4][0]));

    const auto& adj4 = board.board_nodes[2][1].adjacent_tiles;
    assert(adj4.size() == 2);
    assert(adj4.count(&board.board_tiles[1][0]));
    assert(adj4.count(&board.board_tiles[2][0]));

    const auto& adj5 = board.board_nodes[5][4].adjacent_tiles;
    assert(adj5.size() == 2);
    assert(adj5.count(&board.board_tiles[4][1]));
    assert(adj5.count(&board.board_tiles[4][2]));

    const auto& adj6 = board.board_nodes[3][10].adjacent_tiles;
    assert(adj6.size() == 1);
    assert(adj6.count(&board.board_tiles[2][4]));

    const auto& adj7 = board.board_nodes[1][6].adjacent_tiles;
    assert(adj7.size() == 3);
    assert(adj7.count(&board.board_tiles[0][2]));
    assert(adj7.count(&board.board_tiles[1][2]));
    assert(adj7.count(&board.board_tiles[1][3]));

}

void test_board() {
    Board board(2);
    testBoardSize(board);
    testNodeAdj(board);
    testTileAdj(board);
}