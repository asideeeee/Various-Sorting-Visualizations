#include "heapsortvisualization.h"
#include "ui_heapsortvisualization.h"
#include<memory.h>
#include"QLabel"
#include<qpainter.h>
#include<cmath>

heapSortVisualization::heapSortVisualization(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::heapSortVisualization)
{
    ui->setupUi(this);
    nodes=findChildren<treeNode*>();
    //初始化nodesstate,测试一下能不能跑，之后得用获取得到的样本初始化
    for(int i=0;i<15;i++)
    {
        nodesState.append(true);
        //顺便初始化一下val
        val.push_back(i);
        nodes[i]->setVal(i);
        nodes[i]->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);//使其他节点不会被弹簧挤压到消失节点位置
    }
    nodesState[14]=false;
    nodesState[13]=false;

    //nodes[0]->setVisible(false);，可以通过这个代码让某个node不可见
}

void heapSortVisualization::paintEvent(QPaintEvent *event)
{
    for(int i=0;i<nodesState.size();i++)
    {
        if(nodesState[i]==0)
        {
            nodes[i]->setVisible(0);
        }
        else
        {
            if(i==0)
                continue;
            //接下来画线
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);

            int radius = 23;
            QPoint center1(nodes[i]->x()+26,nodes[i]->y()+26); // 第一个圆的中心点
            QPoint center2(nodes[(i-2+i%2)/2]->x()+26, nodes[(i-2+i%2)/2]->y()+26); // 第二个圆的中心点

            // 计算连接线的最短直线端点
            double angle = std::atan2(center2.y() - center1.y(), center2.x() - center1.x());
            QPoint point1(center1.x() + radius * std::cos(angle), center1.y() + radius * std::sin(angle));
            QPoint point2(center2.x() - radius * std::cos(angle), center2.y() - radius * std::sin(angle));
            painter.drawLine(point1,point2);
        }
    }
}

heapSortVisualization::~heapSortVisualization()
{
    delete ui;
}
