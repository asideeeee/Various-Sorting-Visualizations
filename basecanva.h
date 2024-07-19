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
class WithdrawSort;

//排序算法抽象基类.将会被移动到子线程中执行
class SortObject : public QObject
{
    Q_OBJECT
public:
    explicit SortObject(int type,std::vector<int>* sampIn,QObject *parent = nullptr);

    //请在每次进行交换之前调用如下函数
    void swapping(int i,int j);
    //请在每次进行比较之前调用如下函数
    bool comparing(int i,int j);
    void assigning(int i = -1);

    //请通过该指针,使用at()函数访问样本数据.
    std::vector<int>* sample;

    //指示排序类型的编号
    int type = -1;

    //指示排序状态.如果该值为true,则表明展示当前处于单步执行状态,等待用户按下"下一步"或"开始排序"
    //如果为false,则表明当前处于连续执行状态.等待用户按下"暂停排序"或排序完成信号.
    bool singleStepMode = true;
    bool interruptRequested = false;

    //void testThreadId();

    QMutex mutex;               //主线程锁
    QWaitCondition condition;   //条件锁定器
    QElapsedTimer timer;
    qint64 timeCost = 0;

public slots:
    //排序算法函数.这一函数应该放有排序算法的核心逻辑.
    //其中的每次进行交换的时候,请不要使用std::swap,直接使用本类中本地的swap函数即可
    //每次进行比较"之前",请手动emit cmpSignal,并传入当前正在比较的两个索引.
    virtual void sort() = 0;
    void resumeSort();
    void forceNextStepSort();
    void pause();
    void setSingleStepMode();
    void tryNextStepSort();
    void interruptRequest();

signals:
    void swapSignal(int i,int j);
    void cmpSignal(int i,int j);
    void completeSignal();
    void assignSignal(int i);

    void executeWithdrawedAct();
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
    void finished();
    void dataUpdate(qint64 time);

public slots:
    //交换函数,会自动进行颜色标记,不要手动调用
    void animatedSwap(int i, int j);
    void animatedAssign(int i);
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
    WithdrawSort *withdrawSortObj;
    bool withdrawing = false;
    QThread* completeThread = nullptr;

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

    //记录排序统计数据
    int cmpCount = 0;
    int swapCount = 0;
    int assignCount = 0;
};



//////////////////////
/// SortCompleteThread类
//为了防止占用GUI线程,新建一个专为completeMark函数准备的标记
class SortCompleteThread:public QThread{
    Q_OBJECT

public:
    SortCompleteThread(int cap,std::vector<RectItem*>* arr,int lastI,int lastJ,QObject* parent = nullptr):QThread(parent)
        ,cap(cap)
        ,arr(arr)
        ,lastI(lastI)
        ,lastJ(lastJ)
    {}

private:
    int cap;
    std::vector<RectItem*>* arr;
    int lastI;
    int lastJ;

signals:
    void updateRequest();

protected:
    void run() override;
};


//////////////
// 撤回后重排序类,编号0
//为了防止占用GUI线程和主排序线程,新建一个专为撤回准备的线程
class WithdrawSort : public SortObject
{
    Q_OBJECT
public:
    explicit WithdrawSort(std::vector<int>* sampIn,QObject *parent = nullptr):
        SortObject(0,sampIn)
    {}

public slots:
    void sort() override;
    void withdraw();

signals:
    void normalized();

public:
    //记录当前处于有撤回状态还是无撤回状态
    bool normal = true;
    bool isSorting = false;
    bool isWithdrawing = false;
    //记录被撤回的操作类型,1代表交换,0代表比较
    std::vector<bool> executedIsSwap;
    //记录被操作的两个元素对应的索引
    //特别说明:此处的索引指的是被操作后索引,反向交换操作需要将其还原为操作前状态.
    std::vector<std::pair<int,int>> executedInfo;

    std::vector<bool> withdrawedIsSwap;
    std::vector<std::pair<int,int>> withdrawedInfo;
};


#endif // BASECANVA_H



