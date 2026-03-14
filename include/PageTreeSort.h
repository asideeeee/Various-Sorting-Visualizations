#ifndef PAGETREESORT_H
#define PAGETREESORT_H

#include "VisualizerWidget.h"
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>

class PageTreeSort : public QWidget {
  Q_OBJECT
public:
  explicit PageTreeSort(QWidget *parent = nullptr);

private slots:
  void onGenerateClicked();

private:
  void setupUI();
  std::vector<int> generateData(int capacity);
  QWidget *createPlaybackPanel(VisualizerWidget *target);

  QSpinBox *spinSize;
  QPushButton *btnGen;
  VisualizerWidget *vis;
  QLabel *statusLabel;
  double m_lastExecutionTime = 0.0;
};

#endif // PAGETREESORT_H
