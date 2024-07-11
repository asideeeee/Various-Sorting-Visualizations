#ifndef BASECANVA_H
#define BASECANVA_H

#include <QObject>
#include <QWidget>

class BaseCanva : public QWidget
{
    Q_OBJECT
public:
    explicit BaseCanva(QWidget *parent = nullptr);

signals:
};

#endif // BASECANVA_H
