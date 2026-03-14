#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  // Set default application properties
  QApplication::setStyle("Fusion"); // Fusion looks much better and works
                                    // cross-platform with custom palettes
  QApplication::setApplicationName("Modern Sorting Visualizer");
  QApplication::setApplicationVersion("1.0.0");

  MainWindow w;
  w.show();

  return a.exec();
}
