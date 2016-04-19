#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_field = new Field(10, 10);
    m_field->generate();
}

MainWindow::~MainWindow()
{
    delete m_field;

    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
    const int GRID_SIZE = 40;

    // 颜色查找表
    static QColor colorTable[] = {
        QColor(),
        QColor(230, 69, 115),
        QColor(107, 202, 33),
        QColor(255, 186, 16),
        QColor(74, 194, 255),
        QColor(189, 61, 255)
    };

    QPainter p(this);
    for (int ix = 0; ix < m_field->cols(); ix++) {
        for (int iy = 0; iy < m_field->rows(); iy++) {
           int color = m_field->grid(ix, iy);

           if(color == 0)
               continue;

           // color 超界时，给出警告
           Q_ASSERT(color > 0 && color < sizeof(colorTable) / sizeof(QColor));

           p.setBrush(QBrush(colorTable[color]));
           p.drawRect(ix * GRID_SIZE, iy * GRID_SIZE, GRID_SIZE, GRID_SIZE);

        }
    }
}
