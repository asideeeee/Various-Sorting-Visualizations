#ifndef SETCASE_H
#define SETCASE_H

#include <QWidget>

namespace Ui {
class setCase;
}

class setCase : public QWidget
{
    Q_OBJECT

public:
    explicit setCase(int sortType,int wigetMultiplier=3,QWidget *parent = nullptr);
    ~setCase();

private slots:
    void on_customizeBtn_released();

private:
    Ui::setCase *ui;
    int wigetMultiplier;

};

#endif // SETCASE_H
