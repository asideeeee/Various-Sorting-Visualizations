#ifndef TREEDATA_H
#define TREEDATA_H

#include <QWidget>
#include "heapsortvisualization.h"
namespace Ui {
class treedata;
}

class treedata : public QWidget
{
    Q_OBJECT

public slots:
    // 槽函数，处理输入数据的操作
    void handleInputData();
    // 槽函数，处理随机样本大小的操作
    void handleRandomSampleSize();

public:
    explicit treedata(QWidget* parent = nullptr);
    std::vector<int> inputDataVector;  // 新增的成员变量用于存储输入的数据
    ~treedata();
private:
    Ui::treedata *ui;
    heapSortVisualization* sortingScene;
    
};
#endif // TREEDATA_H
