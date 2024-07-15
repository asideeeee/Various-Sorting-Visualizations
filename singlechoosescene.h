#ifndef SINGLECHOOSESCENE_H
#define SINGLECHOOSESCENE_H

#include <QWidget>
#include "heapsortvisualization.h"
#include"treedata.h"

namespace Ui {
class singleChooseScene;
}

class singleChooseScene : public QWidget
{
    Q_OBJECT

public:
    explicit singleChooseScene(QWidget* prev = nullptr,QWidget *parent = nullptr);
    ~singleChooseScene();

private slots:
    void on_backToMainBtn_released();

private:
    Ui::singleChooseScene *ui;
    treedata* sortingScene;
    QWidget* previous;
};

#endif // SINGLECHOOSESCENE_H
