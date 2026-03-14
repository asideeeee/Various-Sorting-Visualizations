#ifndef VISUALIZERWIDGET_H
#define VISUALIZERWIDGET_H

#include "SortState.h"
#include <QTimer>
#include <QWidget>

class VisualizerWidget : public QWidget {
  Q_OBJECT

public:
  explicit VisualizerWidget(QWidget *parent = nullptr);

  void setFrames(const std::vector<SortState> &frames);
  void setDrawAsTree(bool isTree);

  // Playback control
  void play();
  void pause();
  void stepForward();
  void stepBackward();
  void setSpeed(int delayMs);
  void seekTo(int frameIndex);
  bool isPlaying() const;

  int getFrameCount() const;
  int getCurrentFrameIndex() const;
  int getSwapCount() const;
  int getCompareCount() const;

signals:
  void frameChanged(int index, const QString &description);
  void playbackFinished();

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  void drawBars(QPainter &painter);
  void drawTree(QPainter &painter);

  std::vector<SortState> m_frames;
  int m_currentIndex;
  bool m_drawAsTree;

  QTimer *m_timer;
};

#endif // VISUALIZERWIDGET_H