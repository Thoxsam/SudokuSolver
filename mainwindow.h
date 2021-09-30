#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemDelegate>
#include <QLineEdit>
#include <QIntValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool checkSudoku();
    bool checkRow(int row);
    bool checkColumn(int col);
    bool checkBlock(int row, int col);
    void getSudoku();

    bool solveBrute(int row, int col);

    int sudoku[9][9];

private slots:
    void on_checkButton_released();
    void on_solveButton_released();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
