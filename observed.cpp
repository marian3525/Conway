#include "observed.hpp"
#include <algorithm>

void Observed::notifyObservers() const {
    //for_each(observers.begin(), observers.end(), [this] (Observer* observer) {observer->onChange();});
    for(Observer* observer : observers)
        observer->onChange();
}

void Observed::registerObserver(Observer *observer) {
    observers.push_back(observer);
}
