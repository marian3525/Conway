#pragma once
#include <vector>
#include <algorithm>
#include <thread>
#include "tile.hpp"
#include "observed.hpp"
#include <mutex>

class Controller: public Observed
{
public:
    Controller(unsigned int xSize, unsigned int ySize, unsigned int initialCount, unsigned int iterations);
    ~Controller();
    std::vector<std::vector<Tile*>> tableNow;
    std::vector<std::vector<Tile*>> tableNext;

    void startSimulation();
    void step();
    bool isDone();

    unsigned int getXSize() const;
    unsigned int getYSize() const;
    unsigned int getPopulation() const;

private:
    void runSimulation();
    void stepSimulation();
    void onStepCompleted() const;
    void onSimulationCompleted() const;
    std::thread worker;
    std::mutex* wmutex;
    std::mutex* mmutex;
    unsigned int iterations;
    bool done=false;
    unsigned int xSize=10;
    unsigned int ySize=10;
};
