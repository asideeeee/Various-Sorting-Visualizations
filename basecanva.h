#ifndef BASECANVA_H
#define BASECANVA_H

#include <QObject>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QPropertyAnimation>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QEventLoop>
#include <QThread>
#include <QTimer>

class SortObject;

class RectItem : public QObject, public QGraphicsRectItem {
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    RectItem(qreal x, qreal y, qreal width, qreal height)
        : QGraphicsRectItem(x, y, width, height) {
        setFlag(QGraphicsItem::ItemIsMovable);
    }
};


////////////
/// \brief The BaseCanva class
/// 画布控件类
class BaseCanva : public QGraphicsView
{
    Q_OBJECT
public:
    explicit BaseCanva(QWidget *parent = nullptr);

    //窗口显示适配函数,请不要调用
    void initializeRect();
    void repaintRect();

    //开始排序函数,还未实现
    void sort(int cnt,int interval);
    //暂停函数,还未实现
    void pause();

signals:

public slots:
    //取消交换时红色标记的函数.会自动调用,不要手动调用.
    void cancelSwapMark();
    //设置排序参数,不需要在编写排序算法时调用
    void setSortParameter(SortObject* in,std::vector<int>* sampleIn);

    //交换函数,会自动进行颜色标记
    void animatedSwap(int i, int j);
    //比较函数,效果上相当于返回sample[i]<sample[j].
    //在编写排序算法时,进行样本间比较请使用该函数.
    void animatedCmp(int i,int j);
    //在排序完成后请调用该函数,将已经排序完成的样本标成绿色.
    void completeMark();

protected:
    //对窗口缩放的响应函数
    void resizeEvent(QResizeEvent* event) override;

public:
    SortObject *sortObj=nullptr;
    std::vector<int>* sample;
    QList<RectItem*> allRect;
    QGraphicsScene *scene;

    //样本参数记录
    int cap = 0;
    int maxVal = 0;
    int minVal = 0;
    int maxDifference = 0;

    //显示边框预留空位宽度
    const int leftSpace = 0;
    const int rightSpace = 0;
    const int topSpace = 0;
    const int bottomSpace = 0;

    //记录正在被交换的两个长方形索引
    int swapping1 = 0;
    int swapping2 = 0;

    //记录上一次被比较的两个元素索引
    int lastI = 0;
    int lastJ = 0;

    //操作间间隔
    int interval = 60;
};



//////////////////////
///
//为了防止占用GUI线程,新建一个专为completeMark函数准备的标记
class SortCompleteThread:public QThread{
    Q_OBJECT

public:
    SortCompleteThread(int cap,QList<RectItem*>* arr,QObject* parent = nullptr):cap(cap)
        ,arr(arr)
        ,QThread(parent)
    {}

private:
    int cap;
    QList<RectItem*>* arr;

signals:
    void updateRequest();

protected:
    void run() override;
};

#endif // BASECANVA_H



