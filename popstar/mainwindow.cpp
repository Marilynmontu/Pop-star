#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

// 让MainWindow能在鼠标不按下时就跟踪鼠标轨迹，可以参考这里：
// http://stackoverflow.com/questions/9638420/qmainwindow-not-tracking-mouse-with-setmousetracking

const int GRID_SIZE = 40;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_field = new Field(10, 10);
    m_field->generate();

    m_cur_col = m_cur_row = -1;

    centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
    setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete m_field;

    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
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

    // 设置描边为黑色
    p.setPen(Qt::black);

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

    // 描边是白色
    p.setPen(Qt::white);
    // 没有画刷，就是不填充
    p.setBrush(Qt::NoBrush);

    if (m_cur_col >= 0) {
        QRect rect = rectFromLoc(m_cur_col, m_cur_row);
        p.drawRect(rect);
    }
}
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    QPoint pt = e->pos();
    int col = pt.x() / GRID_SIZE;
    int row = pt.y() / GRID_SIZE;

    // 与上次相比，所在的格子发生了变化
    if (col != m_cur_col || row != m_cur_row||col>=9||row>=9) {
        // [TODO] 检测是不是在区域内？
       if(col >=0&& col <=9&&row >=0&&row<=9)
       {
        m_cur_col = col;
        m_cur_row = row;
       }
       else
       m_cur_col = m_cur_row = -1;
        // 显示新坐标
        qDebug() << m_cur_col << m_cur_row;

        // 告诉窗体重新画图，相当于间接调用了 paintEvent
        repaint();
    }
}

QRect MainWindow::rectFromLoc(int col, int row)
{
     return QRect(col * GRID_SIZE, row * GRID_SIZE, GRID_SIZE, GRID_SIZE);
}
