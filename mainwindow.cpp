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
    getSudoku();
    solveBrute();
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

void MainWindow::solveBrute() {
   if (board->solveBrute()) {
       setBoardView();
       board->print();
   } else {

   }
}

void MainWindow::setBoardView() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board->getInt(i, j) > 0)
                ui->tableWidget->setItem(i, j, new QTableWidgetItem(board->getQString(i, j)));
            else
                ui->tableWidget->setItem(i, j, new QTableWidgetItem());
        }
    }

}

void MainWindow::on_openButton_released() {
    QString num;
    QString filename = QFileDialog::getOpenFileName(
                this,
                "Open sudoku file",
                QDir::currentPath(),
                "Text files (*.txt*)");
    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite)) return;

    QTextStream in(&file);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            num = in.read(1);
            if (num.toInt() > 0)
                board->fillCell(i, j, num.toInt());
            else
                j--;
        }
    }
    file.close();
    setBoardView();
}

void MainWindow::on_saveButton_released() {
    QString fileName = QFileDialog::getSaveFileName(
                this,
                "Save sudoku",
                QDir::currentPath(),
                "Text files (*.txt*)");
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, "Unable to open file", file.errorString());
            return;
        }
        getSudoku();

        QDataStream out(&file);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board->getInt(i, j) >= 0)
                    out << board->getQString(i, j);
            }
            out << "\n";
        }
        file.close();
    }
}




void MainWindow::on_clearButton_released()
{
    board->reset();
}

