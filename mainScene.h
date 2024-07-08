#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include "singlechoosescene.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    std::vector<int> sample;
    void receiveSample(std::vector<int> &arr);

private:
    Ui::Widget *ui;
    int wigetMultiplier = 3;
    QWidget *chooseScene = nullptr;
};
#endif // MAINSCENE_H
