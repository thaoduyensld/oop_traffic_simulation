#ifndef ROAD_H
#define ROAD_H

#include <string>

class Intersection;

class Road {
private:
    Intersection* start;
    Intersection* end;
    double distance;
    double speedLimit;
    double congestionLevel;
    double travelCost;          

public:
    Road(Intersection* start, Intersection* end, 
         double distance, 
         double speedLimit = 60.0, 
         double congestionLevel = 1.0);

    Intersection* getStart() const;
    Intersection* getEnd() const;
    double getDistance() const;
    double getSpeedLimit() const;
    double getCongestionLevel() const;
    double getTravelCost() const;

    double getTravelTime() const;        
    void updateCongestion(double level);
    void updateTravelCost(double cost);  

    std::string toString() const;

    ~Road();
};

#endif