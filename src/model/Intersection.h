#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include <string>   

class Road;  

// attributes
class Intersection {
private:
    int id;
    double x;
    double y;
    
    std::vector<Road*> incomingRoads; 
    std::vector<Road*> outgoingRoads;

public:
    Intersection(int id, double x = 0.0, double y = 0.0);

    int getId() const;
    double getX() const;
    double getY() const;

    std::vector<Road*> getIncomingRoads() const; 
    std::vector<Road*> getOutgoingRoads() const; 

    //methods
    void addIncomingRoad(Road* road);
    void addOutgoingRoad(Road* road);
    void removeIncomingRoad(Road* road);
    void removeOutgoingRoad(Road* road);
    
    std::string toString() const;  

    ~Intersection(); 
};

#endif