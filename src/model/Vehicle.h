#ifndef VEHICLE_H
#define VEHICLE_H

#include <vector>

class Intersection;
class Road;

class Vehicle {
private:
    int id;
    Intersection* currentPosition;
    Intersection* destination;
    std::vector<Road*> currentRoute;
    double movementSpeed;
    std::vector<Road*> travelHistory;

public:
    Vehicle(int id, Intersection* start, Intersection* dest, double speed)
        : id(id), currentPosition(start), destination(dest), movementSpeed(speed) {}

    // Getters
    int getId() const { return id; }
    Intersection* getCurrentPosition() const { return currentPosition; }
    Intersection* getDestination() const { return destination; }
    double getMovementSpeed() const { return movementSpeed; }

    // Setters / Update methods (Cơ bản)
    void setCurrentPosition(Intersection* pos) { currentPosition = pos; }
    void setRoute(const std::vector<Road*>& route) { currentRoute = route; }
    void addTravelHistory(Road* road) { travelHistory.push_back(road); }

    ~Vehicle() {}
};

#endif