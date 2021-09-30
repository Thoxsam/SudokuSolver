#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemDelegate>
#include <QLineEdit>
#include <QIntValidator>
#include <QDialog>
#include <QLabel>
#include <iostream>
#include "board.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void getSudoku();
    bool solveBrute(int row, int col);

private slots:
    void on_checkButton_released();
    void on_solveButton_released();
private:
    void setBoardView();
    Board *board;

    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
