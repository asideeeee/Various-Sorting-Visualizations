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
    explicit singleChooseScene(int wigetMultiplier=3,QWidget* prev = nullptr,QWidget *parent = nullptr);
    ~singleChooseScene();

private slots:
    void on_backToMainBtn_released();

private:
    Ui::singleChooseScene *ui;
    QWidget* previous;
};

#endif // SINGLECHOOSESCENE_H
