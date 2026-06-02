#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include <string>   

class Road;  

class Intersection {
private:
    int id;
    double x;
    double y;
    std::vector<Road*> connectedRoads; //list of roads that connect with this intersection

public:
    Intersection(int id, double x = 0.0, double y = 0.0);

    int getId() const;
    double getX() const;
    double getY() const;
    std::vector<Road*> getConnectedRoads() const;

    void addConnectedRoad(Road* road);
    std::vector<Road*> getIncomingRoads() const; 
    std::vector<Road*> getOutgoingRoads() const; 
    std::string toString() const;  

    ~Intersection(); 
};

#endif