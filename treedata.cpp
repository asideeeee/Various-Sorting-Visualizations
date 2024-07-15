#include "treedata.h"
#include "ui_treedata.h"
#include"ui_heapsortvisualization.h"

treedata::treedata(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::treedata)
{
    ui->setupUi(this);
;
    // 连接按钮点击信号与槽函数
    connect(ui->randomButton, &QPushButton::clicked, this, &treedata::handleRandomSampleSize);
    connect(ui->selfButton, &QPushButton::clicked, this, &treedata::handleInputData);
}

void treedata::handleInputData()
{
    // 获取输入的数据
    QString inputData = ui->lineEdit->text();
    QStringList inputDataList = inputData.split(" ");

    if (inputDataList.size() >= 15) {
        // 数据大于等于15个时，不执行后续操作
        return;
    }
    bool validInput = true;
    for (const QString& str : inputDataList) {
        bool ok;
        str.toInt(&ok);
        if (!ok) {
            // 如果有非数字的输入，不执行后续操作
            validInput = false;
            break;
        }
    }
    if (validInput) {
        inputDataVector.clear();  // 清空原有数据
        for (const QString& str : inputDataList) {
            inputDataVector.push_back(str.toInt());
        }

        sortingScene = new heapSortVisualization();
        this->hide();
        sortingScene->show();
        sortingScene->initialize(inputDataVector);
        sortingScene->heapSortAnimation(inputDataVector);
    }
}
void treedata::handleRandomSampleSize()
{
    bool ok;
    int sampleSize = ui->lineedit1->text().toInt(&ok);  // 获取 lineedit 中的值
    if (ok && sampleSize <= 15) {                       //输入的值小于等于15时，才触发函数
        sortingScene = new heapSortVisualization();
        this->hide();
        sortingScene->show();
        sortingScene->startSortingAnimation(sampleSize);  // 将样本大小传递给 startSortingAnimation 函数       
    }
}
treedata::~treedata()
{
    delete sortingScene; // 释放heapSortVisualization对象的内存
    delete ui;
}