#include "sortobject.h"

SortObject::SortObject(int type, QObject *parent)
    : QObject{parent}
    , type(type)
{}
