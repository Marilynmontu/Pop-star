#ifndef FIELD_H
#define FIELD_H

#include <vector>

struct Loc
{
    int col, row;
    Loc(int col_,int row_) : col(col_), row(row_) { }

    // 定义了这个，就可以使用std::find查找元素了
    bool operator==(const Loc &o) { return col == o.col && row == o.row; }
};

class Field
{
public:
    Field(int cols, int rows);
    ~Field();
    int &grid(int col, int row);

    // 属性访问器
    int cols() const { return m_cols; }
    int rows() const { return m_rows; }
    std::vector<Loc> &connected() { return m_connected; }

    // 生成随机棋盘
    void generate();

    // 从某块开始，查找与它连通的块
    void find_connected(int col, int row);
    // 清空连通列表
    void clear_connected();

    // 简单的“消去”
    void eliminate();
    //收缩方块
    void shrink();

private:
    int m_cols, m_rows;
    int *m_grids;

    std::vector<Loc> m_connected;
    void dfs(int col, int row, bool *vis, int color);
    bool validate(int col,int row);
};

#endif // FIELD_H
