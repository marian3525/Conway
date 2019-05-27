#pragma once
#include <vector>
enum State {dead=0, alive=1};

class Tile
{
public:
    //Tile(std::vector<std::vector<Tile*>>* mapNow, std::vector<std::vector<Tile*>>* mapNext, int i, int j, int xSize, int ySize):

    Tile(std::vector<std::vector<Tile*>>* mapNow, std::vector<std::vector<Tile*>>* mapNext,
         unsigned int i, unsigned int j, unsigned int xSize, unsigned int ySize, State state):
        mapNow{mapNow}, mapNext{mapNext}, i{i}, j{j}, xSize{xSize}, ySize{ySize}, state{state}{}
    State getState() const;
    void computeState();
private:
    std::vector<std::vector<Tile*>>* mapNow;
    std::vector<std::vector<Tile*>>* mapNext;

    //position
    unsigned int i, j;
    unsigned int xSize, ySize;
    State state;
    void setState(State state);
};
