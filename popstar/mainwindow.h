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
    void paintEvent(QPaintEvent*) override;
    void mouseMoveEvent(QMouseEvent*)override;
    Field *m_field;
    QRect rectFromLoc(int col, int row);
};

#endif // MAINWINDOW_H
