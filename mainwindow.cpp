#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_checkSolution.h"

class Delegate : public QItemDelegate {
public:
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
        QLineEdit *lineEdit = new QLineEdit(parent);
        // Set validator
        QIntValidator *validator = new QIntValidator(0, 9, lineEdit);
        lineEdit->setValidator(validator);
        return lineEdit;
    }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setItemDelegate(new Delegate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkSudoku() {
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

bool MainWindow::checkRow(int row) {
    bool visited[9] {false};

    for (int i = 0; i < 9; i++) {
        if (sudoku[row][i] > 0 && visited[sudoku[row][i] - 1]) {
            return false;
        } else {
            visited[sudoku[row][i] - 1] = true;
        }
    }
    return true;
}

bool MainWindow::checkColumn(int col) {
    bool visited[9] {false};

    for (int i = 0; i < 9; i++) {
        if (sudoku[i][col] > 0 && visited[sudoku[i][col] - 1 ]) {
            return false;
        } else {
            visited[sudoku[i][col] - 1] = true;
        }
    }
    return true;
}

bool MainWindow::checkBlock(int row, int col) {
    bool visited[9] {false};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[row][col] > 0 && visited[sudoku[row+i][col+j]]) {
                return false;
            } else {
                visited[sudoku[row+i][col+j]] = true;
            }
        }
    }
    return true;
}


void MainWindow::on_checkButton_released() {
    getSudoku();
    bool isCorrect = checkSudoku();

    QDialog *Correct = new QDialog();
    Correct->setFixedSize(300,100);
    QVBoxLayout *layout = new QVBoxLayout();
    QAbstractButton *exit = new QPushButton("Back");
    QLabel *label = new QLabel("Your solution is not correct!");
    if (isCorrect) {
        label->setText("Your solution is Correct");
    }
    label->setAlignment(Qt::AlignHCenter);
    layout->addWidget(label);
    layout->addWidget(exit);
    Correct->setLayout(layout);
    Correct->show();
    Correct->connect(exit, SIGNAL(clicked()), Correct, SLOT(close()));
}

void MainWindow::on_solveButton_released() {
    getSudoku();

    solveBrute(0, 0);

    for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                ui -> tableWidget -> setItem(i,j, new QTableWidgetItem);

                QString str = QString::number(sudoku[i][j]);
                ui -> tableWidget -> item(i,j) -> setText(str);
            }
        }
}

void MainWindow::getSudoku() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            QTableWidgetItem *cell = ui->tableWidget->item(i,j);
            if (cell) {
                sudoku[i][j] = cell->text().toInt();
            } else {
                sudoku[i][j] = 0;            }
        }
    }
}

bool MainWindow::solveBrute(int row, int col) {
    int next_row = (col == 8) ? (row + 1):row;
    int next_col = (col+1) % 9;

    //Case all 9 rows was solved
    if(row == 9) {
        return true;
    }

    //Go to next row and column
    if(sudoku[row][col] != 0) {
        return solveBrute(next_row, next_col);
    }

    for(int num = 1; num <= 9; num++){
        sudoku[row][col] = num;

        qDebug() << num;

        if(checkSudoku() && solveBrute(next_row, next_col)){
                return true;
        }

        //If it's not ok erase it and try again
        sudoku[row][col] = 0;
    }

    return 0;
}

