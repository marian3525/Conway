#include "controller.hpp"
#include <thread>
#include <unistd.h>
#include <iostream>
using namespace std;

Controller::Controller(unsigned int xSize, unsigned int ySize, unsigned int initialCount, unsigned int iterations)
{
    this->iterations = iterations;
    this->xSize = xSize;
    this->ySize = ySize;
    this->wmutex = new std::mutex{};
    this->mmutex= new std::mutex{};

    tableNow.reserve(ySize);
    tableNext.reserve(ySize);

    for(unsigned int i=0; i<ySize; i++) {
        tableNow[i].reserve(xSize);
        tableNext[i].resize(xSize);
    }

    for(unsigned int i=0; i<ySize; i++) {
        for(unsigned int j=0; j<xSize; j++) {
            tableNow[i][j] = new Tile{&tableNow, &tableNext, i, j, xSize, ySize, State::dead};
            tableNext[i][j] = new Tile{&tableNow, &tableNext, i, j, xSize, ySize, State::dead};
        }
    }

    vector<pair<unsigned int, unsigned int>> initial;
    unsigned int i, j;
    srand(time(NULL));

    for (unsigned int c=0; c<initialCount; c++) {
        i = rand() % ySize;
        j = rand() % xSize;

        if(find_if(initial.begin(), initial.end(), [=](pair<unsigned int, unsigned int> p){return p.first==i && p.second==j;}) == initial.end())
            initial.push_back({i, j});
        else {
            c--;
        }
    }

    for_each(initial.begin(), initial.end(), [&](pair<unsigned int, unsigned int> p){
        tableNow[p.first][p.second] = new Tile{&tableNow, &tableNext, p.first, p.second, xSize, ySize, State::alive};
    });
    notifyObservers();
}

bool Controller::isDone() {
    return iterations == 0;
}

void Controller::startSimulation() {
    /**
      Start another thread where the simulation computations will run
    */
    worker = thread([&](){this->runSimulation();});
    wmutex->lock();
    mmutex->unlock();

    done = false;
    while(!done) {
        mmutex->lock();
        cout <<"main thread acquired lock, sending update"<<endl;
        onStepCompleted();

        wmutex->unlock();
        cout<< "main thead let the worker work"<<endl;
        usleep(100);
    }
    worker.join();
    cout<<"worker joined"<<endl;
    //onSimulationCompleted();
}

void Controller::runSimulation() {
    /**
      Computation thread
      */
    unsigned int cycle=0;
    while(cycle < iterations) {
        wmutex->lock();
        cout<<"executor thread got the lock, stepping..."<<endl;
        stepSimulation();
        mmutex->unlock();     // let the main thread do the updating
        cout<<"executor thread unlocked the main thread"<<endl;
        cycle++;
    }
    done = true;            // the main loop breaks and the onSimulationCompleted call is sent
}

void Controller::stepSimulation() {
    /**
      Computation thread
      */
    for(unsigned int i=0; i<ySize; i++)
        for(unsigned int j=0; j<xSize; j++)
            tableNow[i][j]->computeState();
    // after executing a step, the new updated matrix is newTable
    // swap objects
    swap(tableNow, tableNext);
}

void Controller::step() {
    stepSimulation();
    onStepCompleted();
}

void Controller::onStepCompleted() const {
    notifyObservers();
}

void Controller::onSimulationCompleted() const {
    //worker.join();
    notifyObservers();
}

unsigned int Controller::getXSize() const {
    return xSize;
}

unsigned int Controller::getYSize() const {
    return ySize;
}

unsigned int Controller::getPopulation() const {
    unsigned int sum = 0;
    for(unsigned int i=0; i<xSize; i++) {
        for(unsigned int j=0; j<ySize; j++) {
            if(tableNow[i][j]->getState() == alive) {
                sum++;
            }
        }
    }
    return sum;
}

Controller::~Controller() {
    if(worker.joinable())
        worker.join();
}
