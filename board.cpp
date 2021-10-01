#include "board.h"

Board::Board()
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = 1;
        }
    }
}

bool Board::checkSudoku() {
    bool isCorrect {true};

    for (int i = 0; i < 9; i++) {
        isCorrect = isCorrect && checkColumn(i);
        isCorrect = isCorrect && checkRow(i);
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            isCorrect = isCorrect && checkBlock(3*i, 3*j);
         }
    }
    return isCorrect;
}

bool Board::checkRow(int row) {
    bool visited[9] {false, false, false,
                    false, false, false,
                    false, false, false};

    for (int i = 0; i < 9; i++) {
        if (visited[sudoku[row][i] - 1]) {
            return false;
        } else if (sudoku[row][i] > 0) {
            visited[sudoku[row][i] - 1] = true;
        }
    }
    return true;
}

bool Board::checkColumn(int col) {
    bool visited[9] {false, false, false,
                    false, false, false,
                    false, false, false};

    for (int i = 0; i < 9; i++) {
        if (visited[sudoku[i][col] - 1 ]) {
            return false;
        } else if (sudoku[i][col] > 0) {
            visited[sudoku[i][col] - 1] = true;
        }
    }
    return true;
}

bool Board::checkBlock(int row, int col) {
    bool visited[9] {false, false, false,
                    false, false, false,
                    false, false, false};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (visited[sudoku[row+i][col+j]] - 1) {
                return false;
            } else if (sudoku[row][col] > 0) {
                visited[sudoku[row+i][col+j] - 1] = true;
            }
        }
    }
    return true;
}

void Board::fillCell(int x, int y, int num) {
    sudoku[x][y] = num;
}

void Board::print() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << sudoku[i][j];
        }
        std::cout << std::endl;
    }
}

QString Board::getQString(int x, int y) {
    return QString::number(sudoku[x][y]);
}

int Board::getInt(int x, int y) {
    return sudoku[x][y];
}
