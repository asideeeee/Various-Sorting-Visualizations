#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QString>

// Forward declarations of pages
class PageSingleSort;
class PageCompareSort;
class PageTreeSort;

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void onThemeToggled();

private:
  void setupUI();
  void switchTheme(bool isDark);

  bool m_isDark;

  QWidget *centralWidget;
  QStackedWidget *stackedWidget;
  QWidget *sideBar;

  QPushButton *btnThemeToggle;
  QPushButton *btnSinglePage;
  QPushButton *btnComparePage;
  QPushButton *btnTreePage;

  PageSingleSort *pageSingle;
  PageCompareSort *pageCompare;
  PageTreeSort *pageTree;
};

#endif // MAINWINDOW_H