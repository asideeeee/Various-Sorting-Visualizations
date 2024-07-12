# 项目说明

  这是我们小组数据结构可视化的作业项目.

## 文件概要
allsort.cpp \               所有的排序算法类,每一个排序算法对应一个类,它们均继承自SortObject类
basecanva.cpp \             基本画布类,本质上是一个控件,动画将在其显示范围内绘制
main.cpp \                  主函数,无需多言
mainScene.cpp \             主窗口界面,选择是观看单个排序算法可视化还是多种排序算法的对比
second_sort.cpp \           多种排序算法的对比当前最大支持两种算法的同时展示.此文件是其中一个排序算法的类,它目前还与allsort和sortobject两个类无关.
setcase.cpp \               单个排序算法展示之前的样本设置窗口.
singlechoosescene.cpp \     单个排序算法展示之前的算法选择窗口.
sort_alogrithm.cpp \        多种排序算法的对比当前最大支持两种算法的同时展示.此文件是其中另一个排序算法的类,它目前还与allsort和sortobject两个类无关.
sortdisplay.cpp \           单个排序算法展示界面的窗口.其中包含了BaseCanva控件
sortobject.cpp \            排序算法虚基类,为画布BaseCanva提供展示每种排序算法的接口.如果需要写某个排序算法的展示逻辑,在对应的继承类中实现虚函数即可.
widget.cpp \                多种排序算法的对比界面类.
