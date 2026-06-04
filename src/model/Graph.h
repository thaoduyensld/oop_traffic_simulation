#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include "Intersection.h"
#include "Road.h"
#include "Vehicle.h"

class Graph {
private:
    // Sử dụng unordered_map để tra cứu nhanh bằng ID
    std::unordered_map<int, Intersection*> intersections;
    std::unordered_map<int, Road*> roads;
    std::unordered_map<int, Vehicle*> vehicles;

public:
    Graph();
    ~Graph();

    // --- Graph Operations ---
    void addIntersection(Intersection* intersection);
    void removeIntersection(int id);
    
    void addRoad(Road* road);
    void removeRoad(int id);
    
    void updateRoadCondition(int roadId, double congestionLevel, bool blocked);
    std::vector<Road*> getConnectedRoads(int intersectionId) const;

    // --- Vehicle Operations ---
    void addVehicle(Vehicle* vehicle);
    void removeVehicle(int id);

    // --- Getters ---
    Intersection* getIntersection(int id) const;
    Road* getRoad(int id) const;
    Vehicle* getVehicle(int id) const;

    // --- Utility ---
    void clearGraph();
};

#endif