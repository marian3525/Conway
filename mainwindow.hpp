#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>
#include <memory>
#include <QStandardItemModel>
#include "tile.hpp"
#include "observer.hpp"
#include "controller.hpp"

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    explicit MainWindow(Controller* controller, unsigned int dotSize=10);
    void run();
    void onFrameReady(std::vector<std::vector<Tile*>>& frame);

    void onChange();

    void onRunButtonClick();
    void onStepButtonClick();

    ~MainWindow();

private:
    void bind();
    inline void setTile(int i, int j, QColor colour);
    Controller* controller;
    Ui::MainWindow *ui;
    QStandardItemModel* model;
    QTableWidget* table;
    QPushButton* runButton;
    QPushButton* stepButton;
    QLabel* populationLabel;
    unsigned int xSize, ySize, dotSize;
};
