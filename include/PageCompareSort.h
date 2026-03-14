#ifndef PAGECOMPARESORT_H
#define PAGECOMPARESORT_H

#include "VisualizerWidget.h"
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>

class PageCompareSort : public QWidget {
  Q_OBJECT
public:
  explicit PageCompareSort(QWidget *parent = nullptr);

private slots:
  void onGenerateClicked();

private:
  void setupUI();
  std::vector<int> generateData(int capacity, int type);
  QWidget *createPlaybackPanel(VisualizerWidget *target1,
                               VisualizerWidget *target2);

  QComboBox *comboAlgo1;
  QComboBox *comboAlgo2;
  QComboBox *comboData;
  QSpinBox *spinSize;
  QPushButton *btnGen;

  VisualizerWidget *vis1;
  VisualizerWidget *vis2;
  double m_lastExecTime1 = 0.0;
  double m_lastExecTime2 = 0.0;
  QLabel *statusLabel1;
  QLabel *statusLabel2;
};

#endif // PAGECOMPARESORT_H
