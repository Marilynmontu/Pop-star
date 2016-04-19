#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_field = new Field(10, 10);
}

MainWindow::~MainWindow()
{
    delete m_field;

    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
    const int GRID_SIZE = 40;

    QPainter p(this);
    p.setBrush(QBrush(Qt::red));

    for (int ix = 0; ix < m_field->cols(); ix++) {
        for (int iy = 0; iy < m_field->rows(); iy++) {
           int color = m_field->grid(ix, iy);

           if (color) {
               p.drawRect(ix * GRID_SIZE, iy * GRID_SIZE, GRID_SIZE, GRID_SIZE);
           }
        }
    }
}
