#include "PageSingleSort.h"
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

PageSingleSort::PageSingleSort(QWidget *parent) : QWidget(parent) { setupUI(); }

void PageSingleSort::setupUI() {
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setContentsMargins(20, 20, 20, 20);

  QGroupBox *gb = new QGroupBox("单算法演示设置");
  QHBoxLayout *configLayout = new QHBoxLayout(gb);

  comboAlgo = new QComboBox();
  comboAlgo->addItems({"直接插入排序", "折半插入排序", "希尔排序", "冒泡排序",
                       "快速排序", "直接选择排序", "堆排序", "归并排序",
                       "基数排序"});

  comboData = new QComboBox();
  comboData->addItems({"随机生成", "1-N 洗牌", "自定义"});

  spinSize = new QSpinBox();
  spinSize->setRange(5, 300);
  spinSize->setValue(50);

  customEdit = new QLineEdit();
  customEdit->setPlaceholderText("如: 5 2 9 1 5 6");
  customEdit->setDisabled(true);

  connect(comboData, QOverload<int>::of(&QComboBox::currentIndexChanged),
          [this](int idx) {
            customEdit->setDisabled(idx != 2);
            spinSize->setDisabled(idx == 2);
          });

  btnGen = new QPushButton("生成并准备");
  connect(btnGen, &QPushButton::clicked, this,
          &PageSingleSort::onGenerateClicked);

  configLayout->addWidget(new QLabel("算法:"));
  configLayout->addWidget(comboAlgo);
  configLayout->addWidget(new QLabel("数据:"));
  configLayout->addWidget(comboData);
  configLayout->addWidget(new QLabel("数量:"));
  configLayout->addWidget(spinSize);
  configLayout->addWidget(customEdit);
  configLayout->addWidget(btnGen);

  QPushButton *btnInfo = new QPushButton("i");
  btnInfo->setFixedSize(24, 24);
  btnInfo->setStyleSheet(
      "border-radius:12px; background:#00adb5; color:white; font-weight:bold;");
  btnInfo->setToolTip("快捷操作：\n• Space: 播放 / "
                      "暂停\n\n数据面板说明：\n左下角动态实时显示步数、交换次数"
                      "、比较次数和最后一次算法完全执行(后台)所需耗时。");
  configLayout->addWidget(btnInfo);

  visualizer = new VisualizerWidget();
  statusLabel = new QLabel("等待生成...");

  QShortcut *spaceShortcut = new QShortcut(QKeySequence(Qt::Key_Space), this);
  connect(spaceShortcut, &QShortcut::activated, this, [this]() {
    if (!this->isVisible())
      return;
    if (visualizer->isPlaying())
      visualizer->pause();
    else
      visualizer->play();
  });

  connect(visualizer, &VisualizerWidget::frameChanged,
          [this](int idx, const QString &desc) {
            statusLabel->setText(
                QString("步数: %1 / %2  |  交换数: %3  |  比较数: %4  |  "
                        "算法实际耗时: %5 ms  |  动作: %6")
                    .arg(idx)
                    .arg(std::max(0, visualizer->getFrameCount() - 1))
                    .arg(visualizer->getSwapCount())
                    .arg(visualizer->getCompareCount())
                    .arg(m_lastExecutionTime, 0, 'f', 2)
                    .arg(desc));
          });

  QWidget *playback = createPlaybackPanel(visualizer);

  layout->addWidget(gb, 0);
  layout->addWidget(visualizer, 1);
  layout->addWidget(statusLabel);
  layout->addWidget(playback, 0);
}

void PageSingleSort::onGenerateClicked() {
  auto data = generateData(spinSize->value(), comboData->currentIndex(),
                           customEdit->text());
  if (data.empty())
    return;
  SortType type = static_cast<SortType>(comboAlgo->currentIndex());

  auto start = std::chrono::high_resolution_clock::now();
  auto frames = SortAlgorithm::generateFrames(type, data);
  auto end = std::chrono::high_resolution_clock::now();
  m_lastExecutionTime =
      std::chrono::duration<double, std::milli>(end - start).count();

  visualizer->setFrames(frames);
}

std::vector<int> PageSingleSort::generateData(int capacity, int type,
                                              const QString &customStr) {
  std::vector<int> data;
  if (type == 0) { // Random
    data.resize(capacity);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    for (int i = 0; i < capacity; i++)
      data[i] = dis(gen);
  } else if (type == 1) { // Sequential
    data.resize(capacity);
    for (int i = 0; i < capacity; i++)
      data[i] = i + 1;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(data.begin(), data.end(), gen);
  } else { // Custom
    QStringList parts = customStr.split(' ', Qt::SkipEmptyParts);
    for (const QString &p : parts) {
      bool ok;
      int v = p.toInt(&ok);
      if (ok)
        data.push_back(v);
    }
  }
  return data;
}

QWidget *PageSingleSort::createPlaybackPanel(VisualizerWidget *target) {
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
