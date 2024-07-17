#include "treenode.h"
#include "ui_treenode.h"
#include"QPainter"

treeNode::treeNode(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::treeNode)
{
    ui->setupUi(this);
}

void treeNode::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen(Qt::black,3);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);
    if (highlighted) {
        painter.setBrush(Qt::yellow);  // 设置高亮时的填充颜色
    }
    else {
        painter.setBrush(Qt::white);   // 设置普通状态下的填充颜色
    }
    painter.drawEllipse(QPoint(26,26),23,23);
}

void treeNode::setVal(int value)
{
    val=value;
    ui->valLabel->setText(QString::number(value));
    ui->valLabel->setStyleSheet("color:black;");
}

int treeNode::getVal() const
{
    return val;
}

treeNode::~treeNode()
{
    delete ui;
}
