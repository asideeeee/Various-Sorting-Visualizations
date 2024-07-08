#ifndef HEAPSORTVISUALIZATION_H
#define HEAPSORTVISUALIZATION_H

#include <QWidget>
#include"treenode.h"
#include"QLabel"
#include<qpainter.h>

namespace Ui {
class heapSortVisualization;
}

class heapSortVisualization : public QWidget
{
    Q_OBJECT

public:
    explicit heapSortVisualization(QWidget *parent = nullptr);
    ~heapSortVisualization();

private:
    Ui::heapSortVisualization *ui;
    QVector<treeNode*> nodes;//这是保存node的vector
    QVector<bool>nodesState;//用于记录node的状态，false状态表示节点中没有值
    QVector<int>val;//储存获取到的样本，最多不超过15个就行

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // HEAPSORTVISUALIZATION_H
