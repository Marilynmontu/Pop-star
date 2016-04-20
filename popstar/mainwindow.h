#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Field.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Field *m_field;
    int m_cur_col, m_cur_row;

    void paintEvent(QPaintEvent*) override;
    void mouseMoveEvent(QMouseEvent*)override;

    QRect rectFromLoc(int col, int row);
};

#endif // MAINWINDOW_H
