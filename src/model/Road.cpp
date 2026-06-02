#include "Road.h"
#include "Intersection.h" 
#include <limits>

Road::Road(int id, Intersection* start, Intersection* end, 
           double distance, double speedLimit, double congestionLevel) {
    this->id = id;
    this->start = start;
    this->end = end;
    this->distance = distance;
    this->speedLimit = speedLimit;
    if (congestionLevel < 1.0) {
        this->congestionLevel = 1.0; 
    } else {
        this->congestionLevel = congestionLevel;
    }    
    this->blocked = false; 
}


int Road::getId() const { return id; }
Intersection* Road::getStart() const { return start; }
Intersection* Road::getEnd() const { return end; }
double Road::getDistance() const { return distance; }
double Road::getSpeedLimit() const { return speedLimit; }
double Road::getCongestionLevel() const { return congestionLevel; }
bool Road::isBlocked() const { return blocked; }


double Road::getTravelTime() const {
    if (blocked) {
        return std::numeric_limits<double>::infinity(); 
    }
    return distance / (speedLimit / congestionLevel); 
}

double Road::getTravelCost() const {
    return getTravelTime();
}

void Road::updateCongestionLevel(double newLevel) {
    if (newLevel < 1.0) {
        this->congestionLevel = 1.0;
    } else {
        this->congestionLevel = newLevel;
    }
}

void Road::blockRoad() {
    this->blocked = true;
}

void Road::unblockRoad() {
    this->blocked = false;
}

std::string Road::toString() const {
    std::string blockStatus = blocked ? "true" : "false";
    
    return "Road[ID: " + std::to_string(id) + 
           ", Start ID: " + std::to_string(start->getId()) + 
           ", End ID: " + std::to_string(end->getId()) + 
           ", Distance: " + std::to_string(distance) + 
           ", SpeedLimit: " + std::to_string(speedLimit) + 
           ", Congestion: " + std::to_string(congestionLevel) + 
           ", Blocked: " + blockStatus + "]";
}


Road::~Road() {
}