#ifndef SORTDISPLAY_H
#define SORTDISPLAY_H

#include <QDialog>
#include "basecanva.h"

namespace Ui {
class SortDisplay;
}

class SortDisplay : public QDialog
{
    Q_OBJECT

public:
    explicit SortDisplay(QWidget *parent = nullptr);
    ~SortDisplay();

private:
    Ui::SortDisplay *ui;
};

#endif // SORTDISPLAY_H
