#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    board = new Board();
    setBoardView();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete board;
}


void MainWindow::on_checkButton_released() {
    getSudoku();
    bool isCorrect = board->checkSudoku();

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

}

void MainWindow::getSudoku() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            QTableWidgetItem *cell = ui->tableWidget->item(i,j);
            if (cell) {
                board->fillCell(i, j, cell->text().toInt());
            }
        }
    }
}

bool MainWindow::solveBrute(int row, int col) {
    return 0;
}

void MainWindow::setBoardView() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            QTableWidgetItem *temp = new QTableWidgetItem(board->get(i, j));
            ui->tableWidget->setItem(i, j, temp);
        }
    }
}



