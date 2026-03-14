#include "PageTreeSort.h"
#include "SortAlgorithm.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QKeySequence>
#include <QShortcut>
#include <QSlider>
#include <QToolTip>
#include <QVBoxLayout>
#include <chrono>
#include <random>

PageTreeSort::PageTreeSort(QWidget *parent) : QWidget(parent) { setupUI(); }

void PageTreeSort::setupUI() {
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setContentsMargins(20, 20, 20, 20);

  QGroupBox *gb = new QGroupBox("堆排序树形演示 (最多支持 63 个节点)");
  QHBoxLayout *configLayout = new QHBoxLayout(gb);

  spinSize = new QSpinBox();
  spinSize->setRange(3, 63);
  spinSize->setValue(15);

  btnGen = new QPushButton("生成并展示堆排序");
  connect(btnGen, &QPushButton::clicked, this,
          &PageTreeSort::onGenerateClicked);

  configLayout->addWidget(new QLabel("节点数量:"));
  configLayout->addWidget(spinSize);
  configLayout->addStretch();
  configLayout->addWidget(btnGen);

  QPushButton *btnInfo = new QPushButton("i");
  btnInfo->setFixedSize(24, 24);
  btnInfo->setStyleSheet(
      "border-radius:12px; background:#00adb5; color:white; font-weight:bold;");
  btnInfo->setToolTip(
      "快捷操作：\n• Space: 播放 / "
      "暂停\n\n数据面板说明：\n展示堆排序过程中的交换与比较开销。");
  configLayout->addWidget(btnInfo);

  vis = new VisualizerWidget();
  vis->setDrawAsTree(true);

  statusLabel = new QLabel("等待生成...");

  QShortcut *spaceShortcut = new QShortcut(QKeySequence(Qt::Key_Space), this);
  connect(spaceShortcut, &QShortcut::activated, this, [this]() {
    if (!this->isVisible())
      return;
    if (vis->isPlaying())
      vis->pause();
    else
      vis->play();
  });

  connect(vis, &VisualizerWidget::frameChanged,
          [this](int idx, const QString &desc) {
            statusLabel->setText(
                QString("步数: %1 / %2  |  交换数: %3  |  比较数: %4  |  "
                        "算法实际耗时: %5 ms  |  动作: %6")
                    .arg(idx)
                    .arg(std::max(0, vis->getFrameCount() - 1))
                    .arg(vis->getSwapCount())
                    .arg(vis->getCompareCount())
                    .arg(m_lastExecutionTime, 0, 'f', 2)
                    .arg(desc));
          });

  QWidget *playback = createPlaybackPanel(vis);

  layout->addWidget(gb, 0);
  layout->addWidget(vis, 1);
  layout->addWidget(statusLabel);
  layout->addWidget(playback, 0);
}

void PageTreeSort::onGenerateClicked() {
  auto data = generateData(spinSize->value());

  auto start = std::chrono::high_resolution_clock::now();
  auto frames = SortAlgorithm::generateFrames(SortType::Heap, data);
  auto end = std::chrono::high_resolution_clock::now();
  m_lastExecutionTime =
      std::chrono::duration<double, std::milli>(end - start).count();

  vis->setFrames(frames);
}

std::vector<int> PageTreeSort::generateData(int capacity) {
  std::vector<int> data(capacity);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 100);
  for (int i = 0; i < capacity; i++)
    data[i] = dis(gen);
  return data;
}

QWidget *PageTreeSort::createPlaybackPanel(VisualizerWidget *target) {
  QWidget *panel = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout(panel);

  QHBoxLayout *controls = new QHBoxLayout();
  QPushButton *btnPlay = new QPushButton("▶ 播放");
  QPushButton *btnPause = new QPushButton("⏸ 暂停");
  QPushButton *btnPrev = new QPushButton("⏴ 步退");
  QPushButton *btnNext = new QPushButton("⏵ 步进");
  QLabel *speedLabel = new QLabel("速度:");
  QSlider *speedSlider = new QSlider(Qt::Horizontal);
  speedSlider->setRange(1, 100);
  speedSlider->setValue(50);
  speedSlider->setFixedWidth(150);

  controls->addWidget(btnPrev);
  controls->addWidget(btnPlay);
  controls->addWidget(btnPause);
  controls->addWidget(btnNext);
  controls->addStretch();
  controls->addWidget(speedLabel);
  controls->addWidget(speedSlider);

  QSlider *progressSlider = new QSlider(Qt::Horizontal);
  progressSlider->setRange(0, 100);
  progressSlider->setDisabled(true);

  layout->addLayout(controls);
  layout->addWidget(progressSlider);

  auto updateSpeed = [=](int v) {
    int delay = 101 - v;
    if (target)
      target->setSpeed(delay);
  };
  connect(speedSlider, &QSlider::valueChanged, updateSpeed);
  updateSpeed(speedSlider->value());

  connect(btnPlay, &QPushButton::clicked, [=]() {
    target->play();
    progressSlider->setDisabled(false);
  });
  connect(btnPause, &QPushButton::clicked, [=]() { target->pause(); });
  connect(btnPrev, &QPushButton::clicked, [=]() {
    target->pause();
    target->stepBackward();
  });
  connect(btnNext, &QPushButton::clicked, [=]() {
    target->pause();
    target->stepForward();
  });

  connect(target, &VisualizerWidget::frameChanged,
          [=](int idx, const QString &desc) {
            progressSlider->blockSignals(true);
            progressSlider->setMaximum(
                std::max(0, target->getFrameCount() - 1));
            progressSlider->setValue(idx);
            progressSlider->blockSignals(false);
          });

  connect(progressSlider, &QSlider::valueChanged, [=](int val) {
    target->pause();
    target->seekTo(val);
  });

  return panel;
}
