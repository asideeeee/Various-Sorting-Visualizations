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
    painter.drawEllipse(QPoint(26,26),23,23);
}

void treeNode::setVal(int value)
{
    val=value;
    ui->valLabel->setText(QString::number(value));
}

treeNode::~treeNode()
{
    delete ui;
}
