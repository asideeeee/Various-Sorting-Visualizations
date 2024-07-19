QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    allsort.cpp \
    basecanva.cpp \
    comparesortshow.cpp \
    heapsortvisualization.cpp \
    main.cpp \
    mainScene.cpp \
    mysort.cpp \
    setcase.cpp \
    setcase_second.cpp \
    singlechoosescene.cpp \
    sortdisplay.cpp \
    treedata.cpp \
    treenode.cpp

HEADERS += \
    allsort.h \
    basecanva.h \
    comparesortshow.h \
    heapsortvisualization.h \
    mainScene.h \
    mysort.h \
    setcase.h \
    setcase_second.h \
    singlechoosescene.h \
    sortdisplay.h \
    treedata.h \
    treenode.h

FORMS += \
    comparesortshow.ui \
    heapsortvisualization.ui \
    mainScene.ui \
    setcase.ui \
    setcase_second.ui \
    singlechoosescene.ui \
    sortdisplay.ui \
    treedata.ui \
    treenode.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    github_pull.pro.user
