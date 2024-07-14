#ifndef HEAPSORTVISUALIZATION_H
#define HEAPSORTVISUALIZATION_H

#include <QWidget>
#include"treenode.h"
#include"QLabel"
#include<qpainter.h>
#include<QListView>
#include<QStringListModel>
#include<vector>

namespace Ui {
class heapSortVisualization;
}

class heapSortVisualization : public QWidget
{
    Q_OBJECT

public slots:
    // 开始排序动画的槽函数，传入随机数数量
    void startSortingAnimation(int numRandomNumbers);

    // 初始化函数，传入数据数组的引用
    void  initialize(std::vector<int>& data);

    // 堆排序动画函数，传入数据数组的引用
    void   heapSortAnimation(std::vector<int>& arr);

    // 开始函数
    void  start();


public:
    explicit heapSortVisualization(QWidget *parent = nullptr);
    ~heapSortVisualization();

private:
    Ui::heapSortVisualization *ui;
    QVector<treeNode*> nodes;//这是保存node的vector
    QVector<bool>nodesState;//用于记录node的状态，false状态表示节点中没有值
    QVector<int>val;//储存获取到的样本，最多不超过15个就行
    QListView* listView; // 数组栏
    QStringListModel* listModel; // 数组栏的数据模型
    std::vector<int> randomData; // 存储生成的随机向量
    QWidget* chooseScene = nullptr;//跳转初始界面
    int wigetMultiplier = 3;

protected:
    void paintEvent(QPaintEvent *event);
    void  swapNodes(treeNode* node1, treeNode* node2);// 交换节点函数
    void  heapify1(std::vector<int>& arr, int n, int i);// 堆化函数
};

#endif // HEAPSORTVISUALIZATION_H