#include "PageCompareSort.h"
#include "SortAlgorithm.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QKeySequence>
#include <QLabel>
#include <QShortcut>
#include <QSlider>
#include <QToolTip>
#include <QVBoxLayout>
#include <chrono>
#include <random>

PageCompareSort::PageCompareSort(QWidget *parent) : QWidget(parent) {
  setupUI();
}

void PageCompareSort::setupUI() {
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setContentsMargins(20, 20, 20, 20);

  QGroupBox *gb = new QGroupBox("并发多算法比较设置");
  QHBoxLayout *configLayout = new QHBoxLayout(gb);

  comboAlgo1 = new QComboBox();
  comboAlgo2 = new QComboBox();
  QStringList algos = {"直接插入排序", "折半插入排序", "希尔排序",
                       "冒泡排序",     "快速排序",     "直接选择排序",
                       "堆排序",       "归并排序",     "基数排序"};
  comboAlgo1->addItems(algos);
  comboAlgo2->addItems(algos);
  comboAlgo2->setCurrentIndex(3); // Default different algo

  comboData = new QComboBox();
  comboData->addItems({"随机生成", "1-N 洗牌"});

  spinSize = new QSpinBox();
  spinSize->setRange(5, 200);
  spinSize->setValue(100);

  btnGen = new QPushButton("生成并对比");
  connect(btnGen, &QPushButton::clicked, this,
          &PageCompareSort::onGenerateClicked);

  configLayout->addWidget(new QLabel("算法1:"));
  configLayout->addWidget(comboAlgo1);
  configLayout->addWidget(new QLabel("算法2:"));
  configLayout->addWidget(comboAlgo2);
  configLayout->addWidget(new QLabel("数据:"));
  configLayout->addWidget(comboData);
  configLayout->addWidget(new QLabel("数量:"));
  configLayout->addWidget(spinSize);
  configLayout->addWidget(btnGen);

  QPushButton *btnInfo = new QPushButton("i");
  btnInfo->setFixedSize(24, 24);
  btnInfo->setStyleSheet(
      "border-radius:12px; background:#00adb5; color:white; font-weight:bold;");
  btnInfo->setToolTip("快捷操作：\n• Space: 播放 / "
                      "暂停\n\n数据面板说明：\n用于并发对比两算法在时间、交换、"
                      "比较与过程步数上的性能表现。");
  configLayout->addWidget(btnInfo);

  QHBoxLayout *visLayout = new QHBoxLayout();
  vis1 = new VisualizerWidget();
  vis2 = new VisualizerWidget();

  QVBoxLayout *vVis1 = new QVBoxLayout();
  statusLabel1 = new QLabel("算法1 等待中...");
  vVis1->addWidget(vis1, 1);
  vVis1->addWidget(statusLabel1, 0);

  QVBoxLayout *vVis2 = new QVBoxLayout();
  statusLabel2 = new QLabel("算法2 等待中...");
  vVis2->addWidget(vis2, 1);
  vVis2->addWidget(statusLabel2, 0);

  visLayout->addLayout(vVis1);
  visLayout->addLayout(vVis2);

  QShortcut *spaceShortcut = new QShortcut(QKeySequence(Qt::Key_Space), this);
  connect(spaceShortcut, &QShortcut::activated, this, [this]() {
    if (!this->isVisible())
      return;
    if (vis1->isPlaying() || vis2->isPlaying()) {
      vis1->pause();
      vis2->pause();
    } else {
      vis1->play();
      vis2->play();
    }
  });

  connect(vis1, &VisualizerWidget::frameChanged,
          [this](int idx, const QString &desc) {
            statusLabel1->setText(
                QString("算法1 - 步数: %1 / %2  |  实际耗时: %3ms  |  "
                        "交换/比较: %4 / %5")
                    .arg(idx)
                    .arg(std::max(0, vis1->getFrameCount() - 1))
                    .arg(m_lastExecTime1, 0, 'f', 2)
                    .arg(vis1->getSwapCount())
                    .arg(vis1->getCompareCount()));
          });

  connect(vis2, &VisualizerWidget::frameChanged,
          [this](int idx, const QString &desc) {
            statusLabel2->setText(
                QString("算法2 - 步数: %1 / %2  |  实际耗时: %3ms  |  "
                        "交换/比较: %4 / %5")
                    .arg(idx)
                    .arg(std::max(0, vis2->getFrameCount() - 1))
                    .arg(m_lastExecTime2, 0, 'f', 2)
                    .arg(vis2->getSwapCount())
                    .arg(vis2->getCompareCount()));
          });

  QWidget *playback = createPlaybackPanel(vis1, vis2);

  layout->addWidget(gb, 0);
  layout->addLayout(visLayout, 1);
  layout->addWidget(playback, 0);
}

void PageCompareSort::onGenerateClicked() {
  auto data = generateData(spinSize->value(), comboData->currentIndex());
  if (data.empty())
    return;

  SortType t1 = static_cast<SortType>(comboAlgo1->currentIndex());
  SortType t2 = static_cast<SortType>(comboAlgo2->currentIndex());

  auto start1 = std::chrono::high_resolution_clock::now();
  auto frames1 = SortAlgorithm::generateFrames(t1, data);
  auto end1 = std::chrono::high_resolution_clock::now();
  m_lastExecTime1 =
      std::chrono::duration<double, std::milli>(end1 - start1).count();

  auto start2 = std::chrono::high_resolution_clock::now();
  auto frames2 = SortAlgorithm::generateFrames(t2, data);
  auto end2 = std::chrono::high_resolution_clock::now();
  m_lastExecTime2 =
      std::chrono::duration<double, std::milli>(end2 - start2).count();

  vis1->setFrames(frames1);
  vis2->setFrames(frames2);
}

std::vector<int> PageCompareSort::generateData(int capacity, int type) {
  std::vector<int> data(capacity);
  if (type == 0) { // Random
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    for (int i = 0; i < capacity; i++)
      data[i] = dis(gen);
  } else { // Sequential
    for (int i = 0; i < capacity; i++)
      data[i] = i + 1;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(data.begin(), data.end(), gen);
  }
  return data;
}

QWidget *PageCompareSort::createPlaybackPanel(VisualizerWidget *target1,
                                              VisualizerWidget *target2) {
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
    if (target1)
      target1->setSpeed(delay);
    if (target2)
      target2->setSpeed(delay);
  };
  connect(speedSlider, &QSlider::valueChanged, updateSpeed);
  updateSpeed(speedSlider->value());

  connect(btnPlay, &QPushButton::clicked, [=]() {
    if (target1)
      target1->play();
    if (target2)
      target2->play();
    progressSlider->setDisabled(false);
  });
  connect(btnPause, &QPushButton::clicked, [=]() {
    if (target1)
      target1->pause();
    if (target2)
      target2->pause();
  });
  connect(btnPrev, &QPushButton::clicked, [=]() {
    if (target1) {
      target1->pause();
      target1->stepBackward();
    }
    if (target2) {
      target2->pause();
      target2->stepBackward();
    }
  });
  connect(btnNext, &QPushButton::clicked, [=]() {
    if (target1) {
      target1->pause();
      target1->stepForward();
    }
    if (target2) {
      target2->pause();
      target2->stepForward();
    }
  });

  if (target1) {
    connect(target1, &VisualizerWidget::frameChanged,
            [=](int idx, const QString &desc) {
              progressSlider->blockSignals(true);
              progressSlider->setMaximum(
                  std::max(0, target1->getFrameCount() - 1));
              progressSlider->setValue(idx);
              progressSlider->blockSignals(false);
            });
  }

  connect(progressSlider, &QSlider::valueChanged, [=](int val) {
    if (target1) {
      target1->pause();
      target1->seekTo(val);
    }
    if (target2) {
      target2->pause();
      target2->seekTo(val);
    }
  });

  return panel;
}
