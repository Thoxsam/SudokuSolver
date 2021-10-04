#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <QString>

class Board
{
public:
    Board();

    bool checkSudoku();
    bool isValid(int x, int y);
    bool checkRow(int row);
    bool checkColumn(int col);
    bool checkBlock(int row, int col);
    void fillCell(int x, int y, int num);
    void print();
    void reset();
    QString getQString(int x, int y);
    int getInt(int x, int y);

    bool solveBrute();

private:
    int sudoku[9][9];
};

#endif // BOARD_H
