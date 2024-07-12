#ifndef SORTOBJECT_H
#define SORTOBJECT_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QPropertyAnimation>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QEventLoop>
#include <QThread>

class SortObject : public QObject
{
    Q_OBJECT
public:
    explicit SortObject(QObject *parent = nullptr);

    virtual void sort(int count,int interval) = 0;
    virtual void pause() = 0;
    virtual void draw(QPainter* painter,int width,int height) = 0;

signals:
    void runStatusChanged(bool running);

private:
    std::vector<int>* sample;

};

#endif // SORTOBJECT_H
