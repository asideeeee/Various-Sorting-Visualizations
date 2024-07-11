#include "sortdisplay.h"
#include "ui_sortdisplay.h"
#include "canva.h"

SortDisplay::SortDisplay(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SortDisplay)
{
    ui->setupUi(this);
}

SortDisplay::~SortDisplay()
{
    delete ui;
}
