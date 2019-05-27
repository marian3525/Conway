#ifndef OBSERVED_HPP
#define OBSERVED_HPP
#include <vector>
#include "observer.hpp"

class Observed
{
public:
    void notifyObservers() const;
    void registerObserver(Observer* observer);
private:
    std::vector<Observer*> observers;
};

#endif // OBSERVED_HPP
