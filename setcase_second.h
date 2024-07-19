#ifndef SETCASE_SECOND_H
#define SETCASE_SECOND_H

#include <QWidget>
#include<vector>
#include<QMessageBox>
namespace Ui {
class setcase_second;
}

class setcase_second : public QWidget
{
    Q_OBJECT

public:
    explicit setcase_second(QWidget*pre=nullptr,QWidget *parent = nullptr);
    ~setcase_second();

private slots:
    void on_backBtn_clicked();

    void on_randomBtn_clicked();

    void on_customizeBtn_clicked();

    void on_startSort_clicked();

private:
    Ui::setcase_second *ui;
    int sort_index_first=-1;
    int sort_index_second=-1;
    QWidget*previous;

    std::vector<int>sample;

};

#endif // SETCASE_SECOND_H
