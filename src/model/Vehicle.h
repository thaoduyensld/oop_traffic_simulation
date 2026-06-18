#ifndef VEHICLE_H
#define VEHICLE_H

#include <vector>

class Intersection;
class Road;

class Vehicle {
protected:
    int id;
    double baseSpeed;
    Intersection* spawnPoint; // The intersection where the vehicle starts its journey
    Intersection* destination; 
    Road* currentRoad;
    double progressOnCurrentRoad; 
    std::vector<Road*> currentRoute;
    int currentRouteIndex;
    std::vector<Road*> travelHistory;

public:
    Vehicle(int id, double speed, Intersection* start, Intersection* dest);
    
    virtual ~Vehicle() = default;

    virtual double calculateCurrentSpeed() const = 0;
    virtual void update(double dt);

    // Getters
    int getId() const { return id; }
    Intersection* getSpawnPoint() const { return spawnPoint; }
    Intersection* getDestination() const { return destination; }
    double getBaseSpeed() const { return baseSpeed; }
    Road* getCurrentRoad() const { return currentRoad; }
    bool hasReachedDestination() const {
        return (currentRoad == nullptr
            && !currentRoute.empty()
            && currentRouteIndex >= (int)currentRoute.size());
    }
    double getProgressRatio() const;


    // Setters / Update methods (Cơ bản)
    void setRoute(const std::vector<Road*>& route);
    void addTravelHistory(Road* road) { travelHistory.push_back(road); }
    const std::vector<Road*>& getTravelHistory() const { return travelHistory; }

};

#endif