#include "VisualizerWidget.h"
#include <QApplication>
#include <QPainter>
#include <QPainterPath>
#include <QStyleOption>
#include <algorithm>
#include <cmath>

VisualizerWidget::VisualizerWidget(QWidget *parent)
    : QWidget(parent), m_currentIndex(0), m_drawAsTree(false) {
  m_timer = new QTimer(this);
  connect(m_timer, &QTimer::timeout, this, &VisualizerWidget::stepForward);

  // Default size policy
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  setMinimumSize(400, 300);
}

void VisualizerWidget::setFrames(const std::vector<SortState> &frames) {
  m_frames = frames;
  m_currentIndex = 0;
  if (!m_frames.empty()) {
    emit frameChanged(0, m_frames[0].description);
  }
  update();
}

void VisualizerWidget::setDrawAsTree(bool isTree) {
  m_drawAsTree = isTree;
  update();
}

void VisualizerWidget::play() {
  if (m_frames.empty() || m_currentIndex >= m_frames.size() - 1) {
    m_currentIndex = 0; // Restart if at end
  }
  if (!m_timer->isActive()) {
    m_timer->start();
  }
}

void VisualizerWidget::pause() { m_timer->stop(); }

bool VisualizerWidget::isPlaying() const { return m_timer->isActive(); }

void VisualizerWidget::stepForward() {
  if (m_frames.empty())
    return;
  if (m_currentIndex < m_frames.size() - 1) {
    m_currentIndex++;
    emit frameChanged(m_currentIndex, m_frames[m_currentIndex].description);
    update();
  } else {
    pause();
    emit playbackFinished();
  }
}

void VisualizerWidget::stepBackward() {
  if (m_currentIndex > 0) {
    m_currentIndex--;
    emit frameChanged(m_currentIndex, m_frames[m_currentIndex].description);
    update();
  }
}

void VisualizerWidget::setSpeed(int delayMs) { m_timer->setInterval(delayMs); }

void VisualizerWidget::seekTo(int frameIndex) {
  if (m_frames.empty())
    return;
  m_currentIndex = std::clamp(frameIndex, 0, (int)m_frames.size() - 1);
  emit frameChanged(m_currentIndex, m_frames[m_currentIndex].description);
  update();
}

int VisualizerWidget::getFrameCount() const { return m_frames.size(); }

int VisualizerWidget::getCurrentFrameIndex() const { return m_currentIndex; }

int VisualizerWidget::getSwapCount() const {
  if (m_frames.empty() || m_currentIndex < 0 ||
      m_currentIndex >= m_frames.size())
    return 0;
  return m_frames[m_currentIndex].swapCount;
}

int VisualizerWidget::getCompareCount() const {
  if (m_frames.empty() || m_currentIndex < 0 ||
      m_currentIndex >= m_frames.size())
    return 0;
  return m_frames[m_currentIndex].compareCount;
}

void VisualizerWidget::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  // Optional: draw standard background using palette
  QStyleOption opt;
  opt.initFrom(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

  if (m_frames.empty()) {
    painter.drawText(rect(), Qt::AlignCenter, "暂无数据");
    return;
  }

  if (m_drawAsTree) {
    drawTree(painter);
  } else {
    drawBars(painter);
  }
}

void VisualizerWidget::drawBars(QPainter &painter) {
  const SortState &state = m_frames[m_currentIndex];
  const auto &arr = state.array;
  int n = arr.size();
  if (n == 0)
    return;

  int maxVal = *std::max_element(arr.begin(), arr.end());
  if (maxVal == 0)
    maxVal = 1;

  double barWidth = (double)width() / n;
  double bottomMargin = 40.0; // Space for text labels
  double heightScale = (double)(height() - 20 - bottomMargin) / maxVal;

  // Get colors from application palette for a unified look
  QColor normColor = palette().color(QPalette::Highlight).lighter(120);
  QColor activeColor = QColor(255, 99, 132); // Modern red/pink
  QColor pivotColor = QColor(255, 206, 86);  // Modern yellow/orange
  QColor sortedColor = QColor(75, 192, 192); // Modern teal
  QColor textColor = palette().color(QPalette::WindowText);

  for (int i = 0; i < n; ++i) {
    // 20px padding at top, bottomMargin at bottom
    double barHeight = arr[i] * heightScale;
    QRectF barRect(i * barWidth, height() - bottomMargin - barHeight,
                   barWidth - (barWidth > 3 ? 1 : 0), barHeight);

    QColor color = normColor;
    if (state.isSorted[i])
      color = sortedColor;
    if (i == state.active1 || i == state.active2)
      color = activeColor;
    if (i == state.pivot)
      color = pivotColor;

    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    painter.drawRect(barRect);

    // Draw bottom texts with adaptive stride to prevent overlap
    painter.setPen(textColor);
    QFont font = painter.font();
    font.setPixelSize(11);
    painter.setFont(font);

    // index labels like [1]
    QRectF idxRect(i * barWidth, height() - bottomMargin + 4,
                   barWidth > 20 ? barWidth : 20, 16);
    QRectF valRect(i * barWidth, height() - bottomMargin + 20,
                   barWidth > 20 ? barWidth : 20, 16);

    if (barWidth < 20) {
      // Center the text properly when barWidth is smaller than text width
      idxRect.moveLeft(i * barWidth + barWidth / 2.0 - 10);
      valRect.moveLeft(i * barWidth + barWidth / 2.0 - 10);
    }

    // 自适应的 stride，防止柱子太密导致文字重叠
    int stride = 1;
    if (barWidth < 25)
      stride = 2;
    if (barWidth < 15)
      stride = 5;
    if (barWidth < 8)
      stride = 10;
    if (barWidth < 5)
      stride = 20;
    if (barWidth < 2)
      stride = 50;

    // 选择性绘制：间隔绘制，另外保留开头和结尾
    // 为了防止结尾和前一个由于stride很密而重叠，如果结尾离上一个很近就不画结尾了或者用保证逻辑
    if (i % stride == 0 || (i == n - 1 && (i % stride) > stride / 2 + 1)) {
      painter.drawText(idxRect, Qt::AlignCenter, QString("[%1]").arg(i));
      painter.drawText(valRect, Qt::AlignCenter, QString::number(arr[i]));
    }
  }

  // Generate a swap indication arc
  if (state.isSwap && state.active1 != -1 && state.active2 != -1 &&
      state.active1 < n && state.active2 < n) {
    double x1 = state.active1 * barWidth + barWidth / 2.0;
    double x2 = state.active2 * barWidth + barWidth / 2.0;
    double topY =
        height() - bottomMargin -
        std::min(arr[state.active1], arr[state.active2]) * heightScale - 20;
    if (topY < 20)
      topY = 20; // Bound

    QPainterPath path;
    path.moveTo(x1,
                height() - bottomMargin - arr[state.active1] * heightScale - 5);
    path.quadTo((x1 + x2) / 2.0, topY - 40, x2,
                height() - bottomMargin - arr[state.active2] * heightScale - 5);

    painter.setBrush(Qt::NoBrush); // 清除之前可能遗留的（如主元的黄色）笔刷
    painter.setPen(QPen(QColor("#FF4081"), 2, Qt::DashLine));
    painter.drawPath(path);
  }
}

void VisualizerWidget::drawTree(QPainter &painter) {
  const SortState &state = m_frames[m_currentIndex];
  const auto &arr = state.array;
  int n = arr.size();
  if (n == 0)
    return;

  int maxLevel = std::log2(n);

  QColor normColor = palette().color(QPalette::Window).darker(110);
  QColor activeColor = QColor(255, 99, 132);
  QColor pivotColor = QColor(255, 206, 86);
  QColor sortedColor = QColor(75, 192, 192);
  QColor textColor = palette().color(QPalette::WindowText);
  QColor lineColor = palette().color(QPalette::WindowText).lighter(150);

  // Calculate node size based on height and width
  double nodeRadius = std::min(width() / std::pow(2, maxLevel) / 2.5,
                               (double)height() / (maxLevel + 2) / 2.5);
  if (nodeRadius > 25)
    nodeRadius = 25;
  if (nodeRadius < 5)
    nodeRadius = 5;

  // First pass: draw lines
  painter.setPen(QPen(lineColor, 2));
  for (int i = 0; i < n; ++i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    int level = std::log2(i + 1);
    double hSpacing = width() / (std::pow(2, level) + 1);
    double x = hSpacing * (i - std::pow(2, level) + 2);
    double y = (level + 1) * ((double)height() / (maxLevel + 2));

    if (left < n) {
      int lLevel = std::log2(left + 1);
      double lSpacing = width() / (std::pow(2, lLevel) + 1);
      double lx = lSpacing * (left - std::pow(2, lLevel) + 2);
      double ly = (lLevel + 1) * ((double)height() / (maxLevel + 2));
      painter.drawLine(QPointF(x, y), QPointF(lx, ly));
    }
    if (right < n) {
      int rLevel = std::log2(right + 1);
      double rSpacing = width() / (std::pow(2, rLevel) + 1);
      double rx = rSpacing * (right - std::pow(2, rLevel) + 2);
      double ry = (rLevel + 1) * ((double)height() / (maxLevel + 2));
      painter.drawLine(QPointF(x, y), QPointF(rx, ry));
    }
  }

  // Draw Swap Animation Arc
  if (state.isSwap && state.active1 != -1 && state.active2 != -1 &&
      state.active1 < n && state.active2 < n) {
    auto getNodePos = [&](int idx) -> QPointF {
      int level = std::log2(idx + 1);
      double hSpacing = width() / (std::pow(2, level) + 1);
      double x = hSpacing * (idx - std::pow(2, level) + 2);
      double y = (level + 1) * ((double)height() / (maxLevel + 2));
      return QPointF(x, y);
    };
    QPointF p1 = getNodePos(state.active1);
    QPointF p2 = getNodePos(state.active2);

    QPainterPath path;
    path.moveTo(p1);
    path.quadTo((p1.x() + p2.x()) / 2 + 50, (p1.y() + p2.y()) / 2 - 50, p2.x(),
                p2.y());

    painter.setBrush(Qt::NoBrush); // 防止自动闭合曲线或者被意外涂色
    painter.setPen(QPen(QColor("#FF4081"), 3, Qt::DashLine));
    painter.drawPath(path);
  }

  // Second pass: draw nodes
  QFont font = painter.font();
  font.setPixelSize(nodeRadius * 0.8);
  painter.setFont(font);

  for (int i = 0; i < n; ++i) {
    int level = std::log2(i + 1);
    double hSpacing = width() / (std::pow(2, level) + 1);
    double x = hSpacing * (i - std::pow(2, level) + 2);
    double y = (level + 1) * ((double)height() / (maxLevel + 2));

    QColor color = normColor;
    if (state.isSorted[i])
      color = sortedColor;
    if (i == state.active1 || i == state.active2)
      color = activeColor;
    if (i == state.pivot)
      color = pivotColor;

    painter.setBrush(color);
    painter.setPen(QPen(lineColor, 1));
    painter.drawEllipse(QPointF(x, y), nodeRadius, nodeRadius);

    painter.setPen(textColor);
    painter.drawText(
        QRectF(x - nodeRadius, y - nodeRadius, nodeRadius * 2, nodeRadius * 2),
        Qt::AlignCenter, QString::number(arr[i]));
  }
}
