#include "setcase.h"
#include "ui_setcase.h"
#include "sortdisplay.h"
#include "allsort.h"

//此窗口的逻辑编写已完成


//构造函数
SetCase::SetCase(int sortType,QWidget* prev,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::setCase)
    , previous(prev)
{
    ui->setupUi(this);
    switch(sortType)
    {
    case 1:
        ui->titleLabel->setText("直接插入排序");
        ui->textLabel->setText("时间复杂度：\n平均：O(n^2)\n最低：O(n)（已排序情况）\n最高：O(n^2)\n稳定性：稳定\n\n简介：插入排序是一种简单直观的排序算法，它的工作原理是通过构建有序序列，对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。\n插入排序在实现上，通常采用 in-place 排序（即只需用到 O(1) 的额外空间的排序），\n因而在从前到后逐步构建有序序列的过程中，对于未排序数据，从后向前扫描并逐步向前移动已排序元素，直到找到相应位置时进行插入。");
        break;
    case 2:
        ui->titleLabel->setText("折半插入排序");
        ui->textLabel->setText("时间复杂度：\n平均：O(n^2)\n最低：O(n log n)（极少情况）\n最高：O(n^2)\n稳定性：稳定\n\n简介：折半插入排序是对直接插入排序的改进，它通过利用二分查找来减少比较次数，但实际的插入操作仍然是线性的。\n在插入过程中，先使用二分查找确定插入位置，然后再进行插入操作，这样可以减少比较的次数，但移动元素的操作仍然需要线性时间");
        break;
    case 3:
        ui->titleLabel->setText("希尔排序");
        ui->textLabel->setText("时间复杂度：\n平均：O(n log n) ~ O(n^2)\n最低：O(n log n)\n最高：O(n^2)\n稳定性：不稳定\n\n简介：希尔排序是插入排序的一种改进版本，它通过定义一个间隔序列，对原始序列进行多次插入排序，最终使整个序列基本有序。\n希尔排序的关键在于定义间隔序列的选取，不同的间隔序列会影响到排序的效率和最终的有序性。\n在希尔排序中，通过逐步减小间隔，直至间隔为1时，完成最后一次插入排序，从而得到有序序列。");
        break;
    case 4:
        ui->titleLabel->setText("冒泡排序");
        ui->textLabel->setText("时间复杂度：\n平均：O(n^2)\n最低：O(n)（已排序情况）\n最高：O(n^2)\n稳定性：稳定\n\n简介：冒泡排序是一种简单直观的排序算法，它不断地比较相邻的两个元素，如果它们的顺序错误就将它们交换过来，直到没有任何一对需要交换，排序完成。\n在每一轮的排序过程中，都会使得当前最大的元素“浮”到数组的顶端，因此称为“冒泡排序”。");
        break;
    case 5:
        ui->titleLabel->setText("快速排序");
        ui->textLabel->setText("平均：O(n log n)\n最低：O(n log n)\n最高：O(n^2)（逆序情况）\n稳定性：不稳定\n\n简介：快速排序是一种高效的排序算法，基于分治法的思想。\n它选择一个基准元素，将小于基准的元素放在左边，大于基准的元素放在右边，然后递归地对左右两个子序列进行排序。\n快速排序的性能非常优秀，在平均情况下，时间复杂度为 O(n log n)，但在最坏情况下可能退化到 O(n^2)。");
        break;
    case 6:
        ui->titleLabel->setText("直接选择排序");
        ui->textLabel->setText("时间复杂度：\n平均：O(n^2)\n最低：O(n^2)\n最高：O(n^2)\n稳定性：不稳定\n\n简介：直接选择排序是一种简单直观的排序算法，它每次从待排序的数据元素中选择最小（或最大）的元素，将它与序列的第一个元素进行交换，直到整个序列有序。\n虽然直接选择排序也是一种基于比较的排序算法，但它的性能不如快速排序和归并排序。");
        break;
    case 7:
        ui->titleLabel->setText("堆排序");
        ui->textLabel->setText("时间复杂度：\n平均：O(n log n)\n最低：O(n log n)\n最高：O(n log n)\n稳定性：不稳定\n\n简介：堆排序利用堆的数据结构来实现排序过程，它将待排序的元素构建成一个最大堆（或最小堆），然后每次从堆顶取出最大（或最小）元素，将其与堆的末尾元素交换，然后重新调整堆。\n堆排序的时间复杂度为 O(n log n)，它是一种原地排序算法，但不稳定。");
        break;
    case 8:
        ui->titleLabel->setText("树形选择排序");
        ui->textLabel->setText("时间复杂度：\n平均：O(n log n)\n最低：O(n log n)\n最高：O(n^2)\n稳定性：稳定\n\n简介：树形选择排序利用二叉搜索树（BST）来对待排序序列进行排序，它通过不断地将元素插入到 BST 中，然后进行中序遍历，从而得到有序序列。\n树形选择排序的时间复杂度为 O(n log n)，它是一种稳定的排序算法。");
        break;
    case 9:
        ui->titleLabel->setText("归并排序");
        ui->textLabel->setText("时间复杂度：\n平均：O(n log n)\n最低：O(n log n)\n最高：O(n log n)\n稳定性：稳定\n\n简介：归并排序是一种基于分治思想的排序算法，它将待排序的序列递归地分成两个子序列，直到每个子序列只有一个元素，然后将两个有序子序列合并成一个有序序列。\n归并排序的时间复杂度为 O(n log n)，它是一种稳定的排序算法，但在实际应用中需要额外的空间。");
        break;
    case 10:
        ui->titleLabel->setText("基数排序");
        ui->textLabel->setText("时间复杂度：\n平均：O(d * (n + k))\n最低：O(d * (n + k))\n最高：O(d * (n + k))\n稳定性：稳定\n\n简介：基数排序是一种多关键字排序算法，它根据元素的位数依次进行排序，先按照最低有效位进行桶排序，然后再依次按照次低有效位进行桶排序，直到所有位数排完。\n基数排序的时间复杂度为 O(d * (n + k))，其中 d 是数字位数，k 是基数（桶的个数），是一种稳定的排序。");
        break;
    }
    connect(ui->randomBtn,&QPushButton::released,this,&SetCase::setRandSample);
    ui->sampModeDisp->setText("<还未提供样本>");
    this->resize(1280,720);
}


//析构函数
SetCase::~SetCase()
{
    delete ui;
}


//手动输入样本按钮槽函数.
//注意:此函数还没有编写对非法输入的处理逻辑
void SetCase::on_customizeBtn_released()
{
    QString input = ui->textEdit->toPlainText();
    QStringList stringList = input.split(' ', Qt::SkipEmptyParts);
    sample.clear();

    bool ok;
    for (const QString &str : stringList) {
        int number = str.toInt(&ok);
        if (ok) {
            sample.push_back(number);
        }
    }
    int cap =sample.size();
    QString msg =QString("<已启用自定义样本.当前容量为 %1>").arg(QString::number(cap));
    ui->sampModeDisp->setText(msg);
    return;
}


//设置随机化样本按钮槽函数
void SetCase::setRandSample()
{
    bool isInt=false;
    QString inp=ui->randomCap->text();
    int cap = inp.toInt(&isInt);
    if(!isInt){
        QMessageBox::warning(this,"格式错误","输入的值不是整数.");
        return;
    }
    if(cap < 1){
        QMessageBox::warning(this,"容量过低","样本容量不能小于1.");
        return;
    }
    else if(cap > MAX_CAPACITY){
        QString msg = QString("样本容量不能高于 %1.").arg(MAX_CAPACITY);
        QMessageBox::warning(this,"容量过高",msg);
        return;
    }
    sample.clear();
    sample.resize(cap,0);;

    std::srand(std::time(nullptr));

    for(int i=0;i<cap;i++){
        int rdmNumber =std::rand()%MAX_CAPACITY+1;
        sample[i]=rdmNumber;
    }
    QString msg2 = QString("<已启用随机样本.当前容量为 %1>").arg(QString::number(cap));
    ui->sampModeDisp->setText(msg2);
    return;
}


//开始排序按钮槽函数
void SetCase::on_startSort_released()
{
    if(sample.empty())
    {
        QMessageBox::warning(this,"空样本错误","还未选择样本");
        return;
    }
    if(sample.size()>MAX_CAPACITY){
        QString msg = QString("样本容量不能高于 %1.请减少样本数量.").arg(MAX_CAPACITY);
        QMessageBox::warning(this,"样本过量",msg);
        return;
    }
    //样本选择界面下开始排序展示的按钮
    SortDisplay* sortDisplay = new SortDisplay(previous);
    sortDisplay->setAttribute(Qt::WA_DeleteOnClose);
    SortObject *sortObj = creatSortObject(sortType,sortDisplay->getCanva());
    this->hide();
    sortDisplay->show();
    sortDisplay->getCanva()->setSortParameter(sortObj,&sample);
    sortDisplay->getCanva()->initializeRect();
    connect(sortDisplay,&SortDisplay::displayWindowClosed,this,&SetCase::close);

    return;
}


//返回上一个界面按钮槽函数
void SetCase::on_backBtn_released()
{
    previous->show();
    this->close();
    return;
}


//生成序列化样本槽函数
void SetCase::on_sequentialBtn_released()
{
    bool isInt=false;
    QString inp=ui->randomCap->text();
    int cap = inp.toInt(&isInt);
    if(!isInt){
        QMessageBox::warning(this,"格式错误","输入的值不是整数.");
        return;
    }
    if(cap < 1){
        QMessageBox::warning(this,"容量过低","样本容量不能小于1.");
        return;
    }
    else if(cap > MAX_CAPACITY){
        QString msg = QString("样本容量不能高于 %1.").arg(MAX_CAPACITY);
        QMessageBox::warning(this,"容量过高",msg);
        return;
    }
    sample.clear();
    sample.resize(cap,0);
    for(int i=0;i<cap;i++){
        sample[i]=i+1;
    }
    //std::random_shuffle(sample.begin(),sample.end());

    QString msg2 = QString("<已启用序列化样本.当前容量为 %1>").arg(QString::number(cap));
    ui->sampModeDisp->setText(msg2);
    return;
}


//创建排序算法对象的辅助函数,用于连接展示界面与不同的排序算法
SortObject* creatSortObject(int type,QObject* parent){
    switch (type) {
    case 1: return new SimpleSelectSort(parent);
    case 2: return new HalfInsertSort(parent);
    case 3: return new ShellSort(parent);
    case 4: return new BubbleSort(parent);
    case 5: return new QuickSort(parent);
    case 6: return new SimpleSelectSort(parent);
    case 7: return new HeapSort(parent);
    case 8: return new TreeSelectSort(parent);
    case 9: return new MergeSort(parent);
    case 10: return new RadixSort(parent);
    default: return nullptr;
    }
}
