#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <unistd.h>
using namespace std;

MainWindow::MainWindow(Controller* controller, unsigned int dotSize) :
    controller{controller}, ui(new Ui::MainWindow), dotSize{dotSize}
{
    ui->setupUi(this);

    xSize = controller->getXSize();
    ySize = controller->getYSize();

    bind();
    controller->registerObserver(this);
    onChange();
}

void MainWindow::run() {

}

void MainWindow::onFrameReady(vector<vector<Tile*>>& frame) {
    for(unsigned int i=0; i<ySize; i++) {
        for(unsigned int j=0; j<xSize; j++) {
            if(frame[i][j]->getState() == State::alive) {
                setTile(static_cast<int>(i), static_cast<int>(j), Qt::green);
            }
            else if(frame[i][j]->getState()==State::dead){
                setTile(static_cast<int>(i), static_cast<int>(j), Qt::black);
            }
        }
    }
}

void MainWindow::onChange() {
    /**
      Contoller finished a computation step, get the table and display it
      */
    onFrameReady(controller->tableNow);
    populationLabel->setNum(static_cast<int>(controller->getPopulation()));
}

void MainWindow::bind() {
    table = findChild<QTableWidget*>("table");
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setRowCount(static_cast<int>(ySize));
    table->setColumnCount(static_cast<int>(xSize));

    // add headers
    for(unsigned int i=0; i < ySize; i++) {
        table->setRowHeight(static_cast<int>(i), static_cast<int>(dotSize));
    }

    for(unsigned int i=0; i<xSize; i++) {
        table->setColumnWidth(static_cast<int>(i), static_cast<int>(dotSize));
    }

    for(unsigned int i=0; i<ySize; i++) {
        for(unsigned int j=0; j<xSize; j++) {
            table->setItem(static_cast<int>(i), static_cast<int>(j), new QTableWidgetItem());
        }
    }

    runButton = findChild<QPushButton*>("runButton");
    connect(runButton, &QPushButton::clicked, this, &MainWindow::onRunButtonClick);

    stepButton = findChild<QPushButton*>("stepButton");
    connect(stepButton, &QPushButton::clicked, this, &MainWindow::onStepButtonClick);

    populationLabel = findChild<QLabel*>("populationLabel");
    populationLabel->setText("0");
}

void MainWindow::setTile(int i, int j, QColor colour) {
    table->item(i, j)->setData(Qt::BackgroundColorRole, colour);
}

void MainWindow::onRunButtonClick() {
    qDebug("Simulation starting....");
    controller->startSimulation();
}

void MainWindow::onStepButtonClick() {
    controller->step();
}

MainWindow::~MainWindow()
{
    delete controller;
    delete ui;
}
