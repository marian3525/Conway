#include "mainwindow.hpp"
#include <QApplication>
#include "controller.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

int main(int argc, char **argv)
{
    unsigned int xSize=100, ySize=100, iterations=100, dotSize=15;
    unsigned int initials = 1000;

    Controller controller{xSize, ySize, initials, iterations};
    QApplication a {argc, argv};
    MainWindow w {&controller, dotSize};

    w.show();

    return a.exec();
}

/**
  TODO:
  * compute time it takes to init the space and show it in the status bar
  * let the user select the tiles which start populated
  * after run button, the table turns read only
  * show iteration number and stats
  * run the computations in the controller in another thread
 **/
