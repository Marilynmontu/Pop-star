#include "field.h"
#include <algorithm>
#include <QtGlobal>

Field::Field(int cols, int rows)
    : m_cols(cols),
      m_rows(rows),
      m_grids(new int[cols * rows])
{
    // 把 grids 数组填充为 0
    std::fill(&m_grids[0], &m_grids[cols * rows], 0);

    // 测试的情况是：把最底行全填为1，把倒数第2行的一半填为2
    // 0 表示什么都没有
    // 1 2 表示不同的颜色
    for (int i = 0; i < cols; i++) {
        grid(i, rows - 1) = 1;
    }
    for (int i = 0; i < cols / 2; i++) {
        grid(i, rows - 2) = 2;
    }
}

Field::~Field()
{
    delete[] m_grids;
}

int &Field::grid(int col, int row)
{
    // 如果 col 和 row 不在范围内，就输出警告信息
    Q_ASSERT(col >= 0 && col < m_cols);
    Q_ASSERT(row >= 0 && row < m_rows);

    // 这里是把一个一维的数组当成二维用
    return m_grids[row * m_cols + col];
}
