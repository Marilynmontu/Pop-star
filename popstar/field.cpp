#include "field.h"
#include <ctime>
#include <algorithm>
#include <random>
#include <QtGlobal>

Field::Field(int cols, int rows)
    : m_cols(cols),
      m_rows(rows),
      m_grids(new int[cols * rows])
{
    // 把 grids 数组填充为 0
    std::fill(&m_grids[0], &m_grids[cols * rows], 0);
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

void Field::generate()
{
    // 声明一个对象：默认的随机数引擎（C++ 11 新增）
    // 用当前系统时间作为它的种子，保证每次都不同
    std::default_random_engine e(static_cast<unsigned int>(time(NULL)));

    // 声明一个均匀分布
    std::uniform_int_distribution<int> u(1, 5);

    for (int ix = 0; ix < m_cols; ix++) {
        for (int iy = 0; iy < m_rows; iy++) {
            grid(ix, iy) = u(e);
        }
    }
}
void Field::dfs(int col,int row,bool *vis,int color)
{}


