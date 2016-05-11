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
    Field(int cols, int rows,int scores);
    ~Field();
    int &grid(int col, int row);
    // 属性访问器
    int cols() const { return m_cols; }
    int rows() const { return m_rows; }
    int scores() const { return m_scores;}
    int nums() const {return m_num;}
    std::vector<Loc> &connected() { return m_connected; }

    // 生成随机棋盘
    void generate();

    // 从某块开始，查找与它连通的块
    void findConnected(int col, int row);
    // 清空连通列表
    void clearConnected();

    // 简单的“消去”
    void eliminate();

    // 收缩方块
    void shrink();

    // 判定GameOver
    bool hasMoreElim();
    //计算消除所得分数
    void cal_clear_score(int size);

    //计算额外得分
    void cal_extra_score(int sizes);

    //设置方块数量
    void setNum(int num);
private:
    int m_cols, m_rows;
    int *m_grids;
    int m_scores;
    int m_num;
    std::vector<Loc> m_connected;
    void dfs(int col, int row, bool *vis, int color);
    bool validate(int col,int row);
};

#endif // FIELD_H
