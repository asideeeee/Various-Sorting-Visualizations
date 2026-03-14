#include "MainWindow.h"
#include "PageCompareSort.h"
#include "PageSingleSort.h"
#include "PageTreeSort.h"

#include <QGuiApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPalette>
#include <QStyle>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_isDark(true) {
  setupUI();
  switchTheme(m_isDark);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
  setWindowTitle("Modern Sorting Visualizer");
  resize(1280, 720);
  setMinimumSize(1000, 600);

  centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);

  QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
  mainLayout->setContentsMargins(0, 0, 0, 0);
  mainLayout->setSpacing(0);

  // Sidebar
  sideBar = new QWidget(this);
  sideBar->setObjectName("sideBar");
  sideBar->setFixedWidth(220);

  QVBoxLayout *sideLayout = new QVBoxLayout(sideBar);
  sideLayout->setSpacing(15);

  QLabel *logo = new QLabel("Sorting Vis", sideBar);
  logo->setObjectName("logoText");
  logo->setAlignment(Qt::AlignCenter);

  btnSinglePage = new QPushButton("单算法演示");
  btnComparePage = new QPushButton("多算法比较");
  btnTreePage = new QPushButton("堆/树形演示");
  btnThemeToggle = new QPushButton("切换明暗主题");

  btnSinglePage->setCheckable(true);
  btnComparePage->setCheckable(true);
  btnTreePage->setCheckable(true);

  sideLayout->addWidget(logo);
  sideLayout->addSpacing(30);
  sideLayout->addWidget(btnSinglePage);
  sideLayout->addWidget(btnComparePage);
  sideLayout->addWidget(btnTreePage);
  sideLayout->addStretch();
  sideLayout->addWidget(btnThemeToggle);

  // Stacked Widget holds modularized pages
  stackedWidget = new QStackedWidget(this);

  pageSingle = new PageSingleSort(this);
  pageCompare = new PageCompareSort(this);
  pageTree = new PageTreeSort(this);

  stackedWidget->addWidget(pageSingle);
  stackedWidget->addWidget(pageCompare);
  stackedWidget->addWidget(pageTree);

  mainLayout->addWidget(sideBar);
  mainLayout->addWidget(stackedWidget);

  // Sidebar Navigation Connections
  connect(btnSinglePage, &QPushButton::clicked, [this]() {
    stackedWidget->setCurrentIndex(0);
    btnSinglePage->setChecked(true);
    btnComparePage->setChecked(false);
    btnTreePage->setChecked(false);
  });
  connect(btnComparePage, &QPushButton::clicked, [this]() {
    stackedWidget->setCurrentIndex(1);
    btnComparePage->setChecked(true);
    btnSinglePage->setChecked(false);
    btnTreePage->setChecked(false);
  });
  connect(btnTreePage, &QPushButton::clicked, [this]() {
    stackedWidget->setCurrentIndex(2);
    btnTreePage->setChecked(true);
    btnSinglePage->setChecked(false);
    btnComparePage->setChecked(false);
  });
  connect(btnThemeToggle, &QPushButton::clicked, this,
          &MainWindow::onThemeToggled);

  // Select the first page by default
  btnSinglePage->click();
}

void MainWindow::onThemeToggled() {
  m_isDark = !m_isDark;
  switchTheme(m_isDark);
}

void MainWindow::switchTheme(bool isDark) {
  QPalette pal = qApp->palette();

  if (isDark) {
    pal.setColor(QPalette::Window, QColor(30, 30, 30));
    pal.setColor(QPalette::WindowText, Qt::white);
    pal.setColor(QPalette::Base, QColor(40, 40, 40));
    pal.setColor(QPalette::AlternateBase, QColor(45, 45, 45));
    pal.setColor(QPalette::ToolTipBase, Qt::white);
    pal.setColor(QPalette::ToolTipText, Qt::white);
    pal.setColor(QPalette::Text, Qt::white);
    pal.setColor(QPalette::Button, QColor(50, 50, 50));
    pal.setColor(QPalette::ButtonText, Qt::white);
    pal.setColor(QPalette::Link, QColor(42, 130, 218));
    pal.setColor(QPalette::Highlight, QColor(42, 130, 218));
    pal.setColor(QPalette::HighlightedText, Qt::black);
  } else {
    pal = style()->standardPalette();
    pal.setColor(QPalette::Window, QColor(245, 245, 245));
    pal.setColor(QPalette::WindowText, Qt::black);
    pal.setColor(QPalette::Base, Qt::white);
    pal.setColor(QPalette::Text, Qt::black);
    pal.setColor(QPalette::Button, QColor(230, 230, 230));
    pal.setColor(QPalette::ButtonText, Qt::black);
    pal.setColor(QPalette::Highlight, QColor(0, 120, 215));
  }

  qApp->setPalette(pal);

  QString qss = isDark ? R"(
        #sideBar { background: #252526; border-right: 1px solid #333; }
        #logoText { font-size: 24px; font-weight: bold; color: #fff; margin: 15px;}
        QPushButton { border: 1px solid #555; border-radius: 4px; padding: 6px 12px; background: #333; color: #fff;}
        QPushButton:hover { background: #444; }
        QPushButton:checked { background: #0e639c; border-color: #0e639c; color: white;}
        QGroupBox { border: 1px solid #555; border-radius: 4px; margin-top: 10px;}
        QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 3px;}
        QComboBox, QSpinBox, QLineEdit { border: 1px solid #555; border-radius: 3px; padding: 4px; background: #3c3c3c; color: #fff;}
        QComboBox::drop-down { border: none; }
        QSlider::groove:horizontal { border: 1px solid #999; height: 6px; background: #555; margin: 2px 0; border-radius: 3px; }
        QSlider::handle:horizontal { background: #0e639c; border: 1px solid #0e639c; width: 14px; margin: -4px 0; border-radius: 7px; }
    )"
                       : R"(
        #sideBar { background: #f3f3f3; border-right: 1px solid #ddd; }
        #logoText { font-size: 24px; font-weight: bold; color: #333; margin: 15px;}
        QPushButton { border: 1px solid #ccc; border-radius: 4px; padding: 6px 12px; background: #fff; color: #333;}
        QPushButton:hover { background: #eee; }
        QPushButton:checked { background: #0078d7; border-color: #0078d7; color: white;}
        QGroupBox { border: 1px solid #ccc; border-radius: 4px; margin-top: 10px;}
        QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 3px;}
        QComboBox, QSpinBox, QLineEdit { border: 1px solid #ccc; border-radius: 3px; padding: 4px; background: #fff; color: #333;}
        QComboBox::drop-down { border: none; }
        QSlider::groove:horizontal { border: 1px solid #999; height: 6px; background: #ddd; margin: 2px 0; border-radius: 3px; }
        QSlider::handle:horizontal { background: #0078d7; border: 1px solid #0078d7; width: 14px; margin: -4px 0; border-radius: 7px; }
    )";

  this->setStyleSheet(qss);
}