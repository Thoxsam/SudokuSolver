#ifndef BOARD_H
#define BOARD_H

#include <iostream>

class Board
{
public:
    Board();

    bool checkSudoku();
    bool checkRow(int row);
    bool checkColumn(int col);
    bool checkBlock(int row, int col);
    void fillCell(int x, int y, int num);
    void print();
    int get(int x, int y);

private:
    int sudoku[9][9] {1};
};

#endif // BOARD_H
