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
#include <QMutex>
#include <QMutexLocker>
#include <QWaitCondition>

//前向声明
class BaseCanva;

//排序算法抽象基类.
class SortObject : public QObject
{
    Q_OBJECT
public:
    explicit SortObject(int type,std::vector<int>* sampIn,QObject *parent = nullptr);

    //此数据记录了主线程设置的动画间隔值
    int interval = 60;

    //请在每次进行交换之前调用如下函数
    void swapping(int i,int j);
    //请在每次进行比较之前调用如下函数
    void comparing(int i,int j);

    //该函数会根据当前排序展示处于单步执行状态还是连续执行状态,然后自动决定是否进行时长为interval的暂停
    //除了最初的暂停,不要手动调用
    void pause();

    //请通过该指针,使用at()函数访问样本数据.
    std::vector<int>* sample;

    //指示排序类型的编号
    int type = -1;

    //指示排序状态.如果该值为true,则表明展示当前处于单步执行状态,等待用户按下"下一步"或"开始排序"
    //如果为false,则表明当前处于连续执行状态.等待用户按下"暂停排序"或排序完成信号.
    bool singleStepMode = true;


    QMutex mutex;
    QWaitCondition condition;

public slots:
    //排序算法函数.这一函数应该放有排序算法的核心逻辑.
    //其中的每次进行交换的时候,请不要使用std::swap,直接使用本类中本地的swap函数即可
    //每次进行比较"之前",请手动emit cmpSignal,并传入当前正在比较的两个索引.
    virtual void sort() = 0;

signals:
    void swapSignal(int i,int j);
    void cmpSignal(int i,int j);
    void completeSignal();

    void startSortSignal();
    void nextStepSignal();
};


///////////////////
/// \brief The RectItem class
/// 矩形类,为适配动画存在
class RectItem : public QObject, public QGraphicsRectItem {
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    RectItem(qreal x, qreal y, qreal width, qreal height)
        : QGraphicsRectItem(x, y, width, height) {
        setFlag(QGraphicsItem::ItemIsMovable,false);
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

signals:

public slots:
    //取消交换时红色标记的函数.会自动调用,不要手动调用.
    void cancelSwapMark();
    //交换函数,会自动进行颜色标记,不要手动调用
    void animatedSwap(int i, int j);


    void animatedCmp(int i,int j);
    //在排序完成后请调用该函数,将已经排序完成的样本标成绿色.
    void completeMark();

protected:
    //对窗口缩放的响应函数
    void resizeEvent(QResizeEvent* event) override;


public:
    SortObject *sortObj;
    std::vector<int>* sample;
    std::vector<RectItem*> allRect;
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
    int interval = 40;

};



//////////////////////
/// SortCompleteThread类
//为了防止占用GUI线程,新建一个专为completeMark函数准备的标记
class SortCompleteThread:public QThread{
    Q_OBJECT

public:
    SortCompleteThread(int cap,std::vector<RectItem*>* arr,QObject* parent = nullptr):QThread(parent)
        ,cap(cap)
        ,arr(arr)
    {}

private:
    int cap;
    std::vector<RectItem*>* arr;

signals:
    void updateRequest();

protected:
    void run() override;
};

#endif // BASECANVA_H



