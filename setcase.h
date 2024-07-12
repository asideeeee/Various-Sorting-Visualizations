#ifndef SETCASE_H
#define SETCASE_H

#include <QWidget>
#include <qmessagebox.h>
#include "sortobject.h"

//此窗口的逻辑编写已完成

namespace Ui {
class setCase;
}

class setCase : public QWidget
{
    Q_OBJECT

public:
    explicit setCase(int sortType,QWidget* prev = nullptr,QWidget *parent = nullptr);
    ~setCase();
    std::vector<int> sample;

private slots:
    void on_customizeBtn_released();

    void on_startSort_released();

    void on_backBtn_released();

    void on_sequentialBtn_released();

private:
    Ui::setCase *ui;
    int wigetMultiplier;
    QWidget* previous;
    int sortType = -1;

    void setRandSample();
};

SortObject* creatSortObject(int type,QObject* parent);

#define MAX_CAPACITY 300

#endif // SETCASE_H
