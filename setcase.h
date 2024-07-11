#ifndef SETCASE_H
#define SETCASE_H

#include <QWidget>
#include "mainScene.h"
#include <qmessagebox.h>


namespace Ui {
class setCase;
}

class setCase : public QWidget
{
    Q_OBJECT

public:
    explicit setCase(int sortType,int wigetMultiplier=3,QWidget* prev = nullptr,QWidget *parent = nullptr);
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

    void setRandSample();
};

#define MAX_CAPACITY 100

#endif // SETCASE_H
