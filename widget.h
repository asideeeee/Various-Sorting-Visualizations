#ifndef WIDGET_H
#define WIDGET_H

/////////////////
/// 注意:该文件需要做一点修改,此处仅作演示

#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include<QVector>
#include<QRandomGenerator>
#include<QTimer>
#include<QMessageBox>
#include"sort_alogrithm.h"
#include"second_sort.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = nullptr);
    ~mainWidget();
private:
    Ui::Widget *ui;
    //对象成员

    //算法索引
    int index_alogrithm_first=-1;
    int index_alogrithm_second=-1;
    //判断是否处于排序状态
    bool isSorting=false;
    //数据个数
    int num=0;
    //数组
    QVector<int>numbers;
    //数据框
    QVector<QLabel*>columns_first;
    QVector<QLabel*>columns_second;
    //排序速度,参数越小表示越快，在排序开始前设置；安全起见设置默认值
    int speed=60;

    //计时器对象
    QTimer*timer;
    int time_cost=0;

public slots:
    void generateData();
    void generateColumns();
    void swapColumns_first(int i,int j,QVector<int>numbers);
    void swapColumns_second(int i,int j,QVector<int>numbers);

    void updateColumns_first(int i,int j,QVector<int>numbers);
    void updateColumns_second(int i,int j,QVector<int>numbers);
};
#endif // WIDGET_H
