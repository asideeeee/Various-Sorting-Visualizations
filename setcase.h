#ifndef SETCASE_H
#define SETCASE_H

#include <QWidget>
#include "mainScene.h"
#include <cstdlib>
#include <ctime>

namespace Ui {
class setCase;
}

class setCase : public QWidget
{
    Q_OBJECT

public:
    explicit setCase(int sortType,int wigetMultiplier=3,QWidget *parent = nullptr);
    ~setCase();
    Widget* root;

private slots:
    void on_customizeBtn_released();

private:
    Ui::setCase *ui;
    int wigetMultiplier;
    Widget* getRootScene(QWidget *widget);
    void sendSample();
    void sendRandSample();
    std::vector<int> genRandSample(int cap);
};

#define MAX_CAPACITY 300

#endif // SETCASE_H
