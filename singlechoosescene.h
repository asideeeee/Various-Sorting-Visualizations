#ifndef SINGLECHOOSESCENE_H
#define SINGLECHOOSESCENE_H

#include <QWidget>

namespace Ui {
class singleChooseScene;
}

class singleChooseScene : public QWidget
{
    Q_OBJECT

public:
    explicit singleChooseScene(int wigetMultiplier=3,QWidget *parent = nullptr);
    ~singleChooseScene();

private:
    Ui::singleChooseScene *ui;
};

#endif // SINGLECHOOSESCENE_H
