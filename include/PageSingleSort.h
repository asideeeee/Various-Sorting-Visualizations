#ifndef PAGESINGLESORT_H
#define PAGESINGLESORT_H

#include "VisualizerWidget.h"
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>

class PageSingleSort : public QWidget {
  Q_OBJECT
public:
  explicit PageSingleSort(QWidget *parent = nullptr);

signals:
  // We can emit signals if needed, or handle everything internally
  void dataGenerated(const std::vector<int> &data);

private slots:
  void onGenerateClicked();

private:
  void setupUI();
  std::vector<int> generateData(int capacity, int type,
                                const QString &customStr);
  QWidget *createPlaybackPanel(VisualizerWidget *target);

  QComboBox *comboAlgo;
  QComboBox *comboData;
  QSpinBox *spinSize;
  QLineEdit *customEdit;
  QPushButton *btnGen;
  VisualizerWidget *visualizer;
  QLabel *statusLabel;
  double m_lastExecutionTime = 0.0;
};

#endif // PAGESINGLESORT_H
