#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
    const int GRID_SIZE = 40;
    const int FIELD_SIZE = 9;
    QPainter p(this);
    p.setBrush(QBrush(Qt::red));
    //p.drawRect(10, 10, 100, 100);
       bool fill = true;
       for (int i = 0; i < FIELD_SIZE*FIELD_SIZE; i++) {
           int ix = i % FIELD_SIZE;
           int iy = i / FIELD_SIZE;
           if (fill) {
               p.drawRect(ix * GRID_SIZE, iy * GRID_SIZE, GRID_SIZE, GRID_SIZE);
           }
           fill = !fill;
    }
}
