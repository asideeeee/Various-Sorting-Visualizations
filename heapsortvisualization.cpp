#include "heapsortvisualization.h"
#include "ui_heapsortvisualization.h"
#include"singlechoosescene.h"
#include<memory.h>
#include"QLabel"
#include<qpainter.h>
#include<cmath>
#include <QTime>
#include <vector>
#include "treenode.h"
#include <algorithm>
#include <random>

heapSortVisualization::heapSortVisualization(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::heapSortVisualization)
{
    ui->setupUi(this);
    nodes = findChildren<treeNode*>();
    nodesState.resize(15, true); // 初始化nodesState
    // 创建数组栏
    listView = new QListView(this);
    listView->setGeometry(10, 40, 100, 250); // 设置数组栏的位置和大小
    listModel = new QStringListModel(this);
    listView->setModel(listModel);

    connect(ui->pushButton, &QPushButton::clicked, this, [=]() {
        start();
        });
    connect(ui->pushButton3, &QPushButton::clicked, this, [=]() {
        chooseScene = new singleChooseScene(wigetMultiplier, nullptr);
        chooseScene->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        chooseScene->show();
        });
}

void heapSortVisualization::start()
{
     heapSortAnimation(randomData);
}


void heapSortVisualization::startSortingAnimation(int numRandomNumbers)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100); // 生成1到100之间的随机整数


    for (int i = 0; i < numRandomNumbers; ++i) {
        randomData.push_back(distribution(gen)); // 将随机生成的数添加到数组中
    }
    initialize(randomData); // 调用initialize函数进行初始化
}
void heapSortVisualization::initialize(std::vector<int>& data) {
    int size = std::min(static_cast<int>(data.size()), 15);
    for (int i = 0; i < size; i++) {
        // 设置节点的值
        val.push_back(data[i]);
        nodes[i]->setVal(data[i]);
        // 设置节点可见
        nodes[i]->setVisible(true);
        //设置节点状态
        nodesState[i] = true;
        nodes[i]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }
    // 将多余的节点设为不可见
    for (int i = size; i < 15; i++) {
        nodes[i]->setVisible(false);
        nodesState[i] = false;
    }
    update();
}

void heapSortVisualization::swapNodes(treeNode* node1, treeNode* node2)
{
    // 高亮显示节点1和节点2
    node1->setHighlighted(true);
    node2->setHighlighted(true);
    node1->update();
    node2->update();

    // 延迟一小段时间，以可视化交换过程
    QTime dieTime = QTime::currentTime().addMSecs(1000);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);

    // 交换节点的值
    int temp = node1->getVal();
    node1->setVal(node2->getVal());
    node2->setVal(temp);

    // 取消高亮显示
    node1->setHighlighted(false);
    node2->setHighlighted(false);

    // 更新节点外观
    node1->update();
    node2->update();

}

void heapSortVisualization::heapify1(std::vector<int>& arr, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swapNodes(nodes[i], nodes[largest]);
        std::swap(arr[i], arr[largest]);
        heapify1(arr, n, largest);
    }
}

void heapSortVisualization::heapSortAnimation(std::vector<int>& arr)
{
    int n = arr.size();

    // 建立最大堆
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify1(arr, n, i);
    }

    // 堆排序
    for (int i = n - 1; i >= 0; i--) {
        swapNodes(nodes[0], nodes[i]);
        std::swap(arr[0], arr[i]);

        heapify1(arr, i, 0);
        nodes[i]->setVisible(false);
        nodesState[i] = false;
        listModel->insertRow(listModel->rowCount()); // 在数组栏中插入一行
        QModelIndex index = listModel->index(listModel->rowCount() - 1); // 获取新插入行的索引
        listModel->setData(index, QString::number(arr[i])); // 将节点的值移动到数组栏中，从下往上插入
        update();
    }
}

void heapSortVisualization::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    for (int i = 0; i < nodesState.size(); i++)
    {
        if (nodesState[i] == 0)
        {
            nodes[i]->setVisible(0);
        }
        else
        {
            if (i == 0)
                continue;
            //接下来画线
          //  QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);

            int radius = 23;
            QPoint center1(nodes[i]->x() + 26, nodes[i]->y() + 26); // 第一个圆的中心点
            QPoint center2(nodes[(i - 2 + i % 2) / 2]->x() + 26, nodes[(i - 2 + i % 2) / 2]->y() + 26); // 第二个圆的中心点

            // 计算连接线的最短直线端点
            double angle = std::atan2(center2.y() - center1.y(), center2.x() - center1.x());
            QPoint point1(center1.x() + radius * std::cos(angle), center1.y() + radius * std::sin(angle));
            QPoint point2(center2.x() - radius * std::cos(angle), center2.y() - radius * std::sin(angle));
            painter.drawLine(point1, point2);
        }
    }
}


heapSortVisualization::~heapSortVisualization()
{
    delete ui;
}