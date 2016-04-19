#ifndef FIELD_H
#define FIELD_H


class Field
{
public:
    Field(int cols, int rows);
    ~Field();
    int &grid(int col, int row);

    // 属性访问器
    int cols() const { return m_cols; }
    int rows() const { return m_rows; }

private:
    int m_cols, m_rows;
    int *m_grids;
};

#endif // FIELD_H
