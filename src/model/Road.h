#ifndef ROAD_H
#define ROAD_H

#include <string>

class Intersection;

class Road {
private:
    int id;
    Intersection* start;
    Intersection* end;
    double distance;
    double speedLimit;
    double congestionLevel;
    bool blocked; // accident status

public:
    Road(int id, Intersection* start, Intersection* end, 
         double distance, 
         double speedLimit, 
         double congestionLevel = 1.0);

    //getters
    int getId() const;
    Intersection* getStart() const;
    Intersection* getEnd() const;
    double getDistance() const;
    double getSpeedLimit() const;
    double getCongestionLevel() const;
    bool isBlocked() const;

    double getTravelCost() const;
    double getTravelTime() const;        
    
    void updateCongestionLevel(double newLevel);
    void blockRoad();
    void unblockRoad();


    std::string toString() const;

    ~Road();
};

#endif