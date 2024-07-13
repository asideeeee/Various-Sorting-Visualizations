#ifndef SORTDISPLAY_H
#define SORTDISPLAY_H

#include <QWidget>
#include "basecanva.h"
#include <QLabel>

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
    explicit SortDisplay(QWidget* prev,QWidget *parent = nullptr);
    ~SortDisplay();

    BaseCanva* getCanva();
    Ui::SortDisplay* getSortDisplayUi();

private slots:
    void on_startButton_released();

    void on_exitButton_released();

    void on_pauseButton_released();

    void on_nextButton_released();

    void on_withdrawButton_released();

    void on_speedSpinBox_valueChanged(int arg1);

    void on_debugButton_released();

signals:
    void displayWindowClosed();

private:
    Ui::SortDisplay *ui;
    QWidget* previous;
};

#endif // SORTDISPLAY_H
