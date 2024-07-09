#ifndef TREENODE_H
#define TREENODE_H

#include <QWidget>
#include<QPainter>

namespace Ui {
class treeNode;
}

class treeNode : public QWidget
{
    Q_OBJECT

public:
    explicit treeNode(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void setVal(int value);
    ~treeNode();

private:
    Ui::treeNode *ui;
    int val;
};

#endif // TREENODE_H
