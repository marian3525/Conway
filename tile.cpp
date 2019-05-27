#include "tile.hpp"

void Tile::computeState() {
    //return;
    //get neighbour count
    int count=0;
    State state=this->state;
    if(i==0) {
        if(j==0) {
            //top left corner
            count = (*mapNow)[i][j+1]->getState() + (*mapNow)[i+1][j+1]->getState() + (*mapNow)[i+1][j]->getState();
        }
        else if(j==xSize-1) {
            // top right corner
            count = (*mapNow)[i][j-1]->getState() + (*mapNow)[i+1][j]->getState() + (*mapNow)[i+1][j-1]->getState();
        }
        else {
            // top row, not in any corners
            count = (*mapNow)[i][j-1]->getState() +
                    (*mapNow)[i][j+1]->getState() +
                    (*mapNow)[i+1][j-1]->getState()+
                    (*mapNow)[i+1][j]->getState() +
                    (*mapNow)[i+1][j+1]->getState();
        }
    }
    else if(i==ySize-1) {
        if(j==0) {
            //bottom left corner
            count = (*mapNow)[i-1][j]->getState() + (*mapNow)[i-1][j+1]->getState() + (*mapNow)[i][j+1]->getState();
        }
        else if(j==xSize-1) {
            // bottom right corner
            count = (*mapNow)[i-1][j]->getState() + (*mapNow)[i-1][j-1]->getState() + (*mapNow)[i][j-1]->getState();
        }
        else {
            // bottom row, not in any corners
            count = (*mapNow)[i][j-1]->getState() + (*mapNow)[i][j+1]->getState() + (*mapNow)[i-1][j-1]->getState()+
                    (*mapNow)[i-1][j]->getState() + (*mapNow)[i-1][j+1]->getState();
        }
    }
    else if(i>0 and i<ySize-1) {
        if(j==0) {
            // row at the middle, first element
            count = (*mapNow)[i-1][j]->getState() + (*mapNow)[i-1][j+1]->getState() +
                    (*mapNow)[i][j+1]->getState() +
                    (*mapNow)[i+1][j]->getState() + (*mapNow)[i][j+1]->getState();
        }
        else if(j==xSize-1) {
            // row at the middle, last element
            count = (*mapNow)[i-1][j]->getState() + (*mapNow)[i-1][j-1]->getState() +
                    (*mapNow)[i][j-1]->getState() +
                    (*mapNow)[i+1][j]->getState() + (*mapNow)[i][j-1]->getState();
        }
        else {
            // easy case, inside the border of the table
            count = (*mapNow)[i-1][j-1]->getState()+ (*mapNow)[i-1][j]->getState() + (*mapNow)[i-1][j+1]->getState() +
                    (*mapNow)[i][j-1]->getState() + (*mapNow)[i][j+1]->getState() +
                    (*mapNow)[i+1][j-1]->getState()+ (*mapNow)[i+1][j]->getState() + (*mapNow)[i+1][j+1]->getState();
        }
    }
    if(state==alive)
        switch(count) {
            case(0):
                state = dead;
            break;
            case(1):
                state=dead;
            break;
            case(2):
                state=alive;
            break;
            case(3):
                state=alive;
            break;
            default:
                state=dead;
            break;
    }
    else if (state==dead and count == 3) {
        state = alive;
    }
    (*mapNext)[i][j] = this;
    (*mapNext)[i][j]->setState(state);
}

State Tile::getState() const {
    return state;
}

void Tile::setState(State state) {
    this->state = state;
}
