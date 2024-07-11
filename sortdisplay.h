#ifndef SORTDISPLAY_H
#define SORTDISPLAY_H

#include <QWidget>
#include "basecanva.h"
#include "sortObject.h"

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

private:
    Ui::SortDisplay *ui;

    QWidget* previous;
};

#endif // SORTDISPLAY_H
