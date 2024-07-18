#ifndef SORTDISPLAY_H
#define SORTDISPLAY_H

#include "basecanva.h"

/////////////
///
/// 排序展示界面
namespace Ui {
class SortDisplay;
}

class SortDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit SortDisplay(QWidget* prev,std::vector<int>* sampIn,SortObject* sortObjIn,QWidget *parent = nullptr);
    ~SortDisplay();

    BaseCanva* getCanva();
    void setResizable();

private slots:
    void on_exitButton_released();

    void on_withdrawButton_released();

    void on_speedSpinBox_valueChanged(int arg1);

    void on_startWithdrawButton_released();

    void on_nextButton_released();

    void on_pauseButton_released();

    void on_startButton_released();

    void disableAllBtn();

    void updatingData(qint64 time);

signals:
    void displayWindowClosed();

    void beginWithdraw();
    void beginWithdrawerSort();
    //void testSig();

private:
    Ui::SortDisplay *ui;
    QWidget* previous;
    QThread* sortThread;
    QThread* withdrawThread;
};

#endif // SORTDISPLAY_H
