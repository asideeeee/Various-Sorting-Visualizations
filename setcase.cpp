#include "setcase.h"
#include "ui_setcase.h"

setCase::setCase(int sortType,int wigetMultiplier,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::setCase)
{
    setFixedSize(320*wigetMultiplier,180*wigetMultiplier);
    ui->setupUi(this);
    switch(sortType)
    {
    case 1:
        ui->titleLabel->setText("直接插入排序");
        ui->textLabel->setText("时间复杂度：\n平均：O(n^2)\n最低：O(n)（已排序情况）\n最高：O(n^2)\n稳定性：稳定\n\n简介：插入排序是一种简单直观的排序算法，它的工作原理是通过构建有序序列，对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。插入排序在实现上，通常采用 in-place 排序（即只需用到 O(1) 的额外空间的排序），因而在从前到后逐步构建有序序列的过程中，对于未排序数据，从后向前扫描并逐步向前移动已排序元素，直到找到相应位置时进行插入。");
        break;
    case 2:
        ui->titleLabel->setText("折半插入排序");
        ui->textLabel->setText("时间复杂度：\n平均：O(n^2)\n最低：O(n log n)（极少情况）\n最高：O(n^2)\n稳定性：稳定\n\n简介：折半插入排序是对直接插入排序的改进，它通过利用二分查找来减少比较次数，但实际的插入操作仍然是线性的。在插入过程中，先使用二分查找确定插入位置，然后再进行插入操作，这样可以减少比较的次数，但移动元素的操作仍然需要线性时间");
        break;
    case 3:
        ui->titleLabel->setText("希尔排序");
        ui->textLabel->setText("时间复杂度：\n平均：O(n log n) ~ O(n^2)\n最低：O(n log n)\n最高：O(n^2)\n稳定性：不稳定\n\n简介：希尔排序是插入排序的一种改进版本，它通过定义一个间隔序列，对原始序列进行多次插入排序，最终使整个序列基本有序。希尔排序的关键在于定义间隔序列的选取，不同的间隔序列会影响到排序的效率和最终的有序性。在希尔排序中，通过逐步减小间隔，直至间隔为1时，完成最后一次插入排序，从而得到有序序列。");
        break;
    case 4:
        ui->titleLabel->setText("冒泡排序");
        ui->textLabel->setText("时间复杂度：\n平均：O(n^2)\n最低：O(n)（已排序情况）\n最高：O(n^2)\n稳定性：稳定\n\n简介：冒泡排序是一种简单直观的排序算法，它通过不断地比较相邻的两个元素，如果它们的顺序错误就将它们交换过来，直到没有任何一对需要交换，排序完成。在每一轮的排序过程中，都会使得当前最大的元素“浮”到数组的顶端，因此称为“冒泡排序”。");
        break;
    case 5:
        ui->titleLabel->setText("快速排序");
        ui->textLabel->setText("平均：O(n log n)\n最低：O(n log n)\n最高：O(n^2)（逆序情况）\n稳定性：不稳定\n\n简介：快速排序是一种高效的排序算法，基于分治法的思想。它选择一个基准元素，将小于基准的元素放在左边，大于基准的元素放在右边，然后递归地对左右两个子序列进行排序。快速排序的性能非常优秀，在平均情况下，时间复杂度为 O(n log n)，但在最坏情况下可能退化到 O(n^2)。");
        break;
    case 6:
        ui->titleLabel->setText("直接选择排序");
        ui->textLabel->setText("时间复杂度：\n平均：O(n^2)\n最低：O(n^2)\n最高：O(n^2)\n稳定性：不稳定\n\n简介：直接选择排序是一种简单直观的排序算法，它每次从待排序的数据元素中选择最小（或最大）的元素，将它与序列的第一个元素进行交换，直到整个序列有序。虽然直接选择排序也是一种基于比较的排序算法，但它的性能不如快速排序和归并排序。");
        break;
    case 7:
        ui->titleLabel->setText("堆排序");
        ui->textLabel->setText("时间复杂度：\n平均：O(n log n)\n最低：O(n log n)\n最高：O(n log n)\n稳定性：不稳定\n\n简介：堆排序利用堆的数据结构来实现排序过程，它将待排序的元素构建成一个最大堆（或最小堆），然后每次从堆顶取出最大（或最小）元素，将其与堆的末尾元素交换，然后重新调整堆。堆排序的时间复杂度为 O(n log n)，它是一种原地排序算法，但不稳定。");
        break;
    case 8:
        ui->titleLabel->setText("树形选择排序");
        ui->textLabel->setText("时间复杂度：\n平均：O(n log n)\n最低：O(n log n)\n最高：O(n^2)\n稳定性：稳定\n\n简介：树形选择排序利用二叉搜索树（BST）来对待排序序列进行排序，它通过不断地将元素插入到 BST 中，然后进行中序遍历，从而得到有序序列。树形选择排序的时间复杂度为 O(n log n)，它是一种稳定的排序算法。");
        break;
    case 9:
        ui->titleLabel->setText("归并排序");
        ui->textLabel->setText("时间复杂度：\n平均：O(n log n)\n最低：O(n log n)\n最高：O(n log n)\n稳定性：稳定\n\n简介：归并排序是一种基于分治思想的排序算法，它将待排序的序列递归地分成两个子序列，直到每个子序列只有一个元素，然后将两个有序子序列合并成一个有序序列。归并排序的时间复杂度为 O(n log n)，它是一种稳定的排序算法，但在实际应用中需要额外的空间。");
        break;
    case 10:
        ui->titleLabel->setText("基数排序");
        ui->textLabel->setText("时间复杂度：\n平均：O(d * (n + k))\n最低：O(d * (n + k))\n最高：O(d * (n + k))\n稳定性：稳定\n\n简介：基数排序是一种多关键字排序算法，它根据元素的位数依次进行排序，先按照最低有效位进行桶排序，然后再依次按照次低有效位进行桶排序，直到所有位数排完。基数排序的时间复杂度为 O(d * (n + k))，其中 d 是数字位数，k 是基数（桶的个数），是一种稳定的排序。");
        break;
    }
}

setCase::~setCase()
{
    delete ui;
}
