#include "field.h"
#include <ctime>
#include <algorithm>
#include <random>
#include <QtGlobal>
#include <QtDebug>

Field::Field(int cols, int rows,int scores)
    : m_cols(cols),
      m_rows(rows),
      m_grids(new int[cols * rows]),
      m_scores(scores),
      m_num(cols*rows)
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

void Field::dfs(int col, int row, bool *vis, int color)
{
    // 这个位置存在吗
    if (col < 0 || col >= m_cols || row < 0 || row >= m_rows)
        return;

    // 如果，之前已经遍历过
    if (vis[row * m_cols + col])
        return;

    // 色不同不相为谋
    if (grid(col, row) != color)
        return;

    // 标记
    vis[row * m_cols + col] = true;

    // 加入列表
    m_connected.push_back(Loc(col, row));

    dfs(col + 1, row, vis, color); // 右
    dfs(col, row + 1, vis, color); // 下
    dfs(col - 1, row, vis, color); // 左
    dfs(col, row - 1, vis, color); // 上
}

void Field::findConnected(int col, int row)
{
    // 首先必须是有颜色的方块
    if (grid(col, row) == 0)
        return;

    // 分配一个布尔数组，用于存储标记
    bool *vis = new bool[m_rows * m_cols];

    // 初始化成全没有标记
    std::fill(vis, vis + (m_rows * m_cols), false);

    // 进行dfs
    dfs(col, row, vis, grid(col, row));

    // 释放数组
    delete[] vis;
}

void Field::clearConnected()
{
    m_connected.clear();
}

void Field::eliminate()
{
    for (auto iter = m_connected.begin(); iter != m_connected.end(); iter++) {
        grid(iter->col, iter->row) = 0;
    }
    m_connected.clear();
}


void Field::shrink()
{
    int read_col=0;
    int write_col=0;
    for(read_col=0;read_col<m_cols;read_col++)
    {
        bool cleared = true;
        for (int row = 0; row < m_rows; row++) {
            if (grid(read_col, row) != 0) {
                cleared = false;
                break;
            }
        }
        if(cleared)  continue;
        else
        {
            if (read_col > write_col){
           for (int row = 0; row < m_rows; row++)
               grid(write_col, row) = grid(read_col, row);
           for (int row = 0; row < m_rows; row++)
               grid(read_col, row) = 0;

            }
            write_col++;
        }
    }

    for( int col=0;col < m_cols;col++)
    {
        int read_row=0;int write_row=m_rows-1;
        for(read_row=m_rows-1;read_row>=0;read_row--)
        {
            if(grid(col,read_row)==0)continue;
            else
            {
                if(read_row<write_row)
                {
                grid(col,write_row)=grid(col,read_row);
                grid(col,read_row)=0;
                }
                write_row--;
            }
        }
    }
}

bool Field::validate(int col, int row)
{
    return (col>=0&&col<m_cols&&row>=0&&row<m_rows);
}

bool Field::hasMoreElim()
{
    static Loc vecs[] =
    {
        { 1, 0 }, // 右
        { 0, 1 }, // 下
        { -1, 0 }, // 左
        { 0, -1 } // 上
    };

    for (int row = 0; row < m_rows; row++) {
        for (int col = 0; col < m_cols; col++) {
            for (int i = 0; i < 4; i++) {
                Loc &vec = vecs[i];
                int color = grid(col, row);
                if (color == 0)
                    continue;
                if (validate(col + vec.col, row + vec.row)
                    && grid(col + vec.col, row + vec.row) == color)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

void Field::cal_clear_score(int size)
{
    m_scores+=20+25*(size-2)+(size-2)*(size-3)*5; //(1+size-3)*(size-3)*10/2 等差数列，从第三个开始每一个方块比前一个方块多加10分
}

void Field::cal_extra_score(int size)
{
    switch(size)
    {
    case 0:m_scores+=2000;break;
    case 1:m_scores+=1980;break;
    case 2:m_scores+=1920;break;
    case 3:m_scores+=1680;break;
    case 4:m_scores+=1500;break;
    case 5:m_scores+=1280;break;
    case 6:m_scores+=1020;break;
    case 7:m_scores+=720;break;
    case 8:m_scores+=380;break;
    }
}

void Field::setNum(int num)
{
    m_num=num;
}
