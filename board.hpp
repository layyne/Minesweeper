// Contains Board class definition.

#ifndef BOARD_HPP
#define BOARD_HPP

#include "common.hpp"

class Board
{
    std::vector<std::vector<int>> board;
    std::vector<std::vector<bool>> covered;
    std::vector<std::vector<bool>> marked;
    int height, width, mines;
    int cr, cc;
    bool failed;

  public:
    Board(int, int);
    bool inBounds(int, int);
    void generate(int, int, int);
    void reserveFirstMove(int, int);
    void placeMines();
    void getNumberTiles();
    int countMines(int, int);
    void printDebug(int, int);
    void print();
    void fail();
    bool isFailed();
    void mark(int, int);
    void click(int, int);
    int countMarked(int, int);
    void bigClick(int, int);
    void move(int);
    int getR();
    int getC();
    // void cursesPrint();
};

// struct Tile
// {
//     bool revealed = false;
//     bool flagged = false;
//     bool isClickable();
// };

#endif
