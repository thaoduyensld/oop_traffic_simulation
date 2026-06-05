#include "Graph.h"

Graph::Graph() {
}

Graph::~Graph() {
    clearGraph();
}

// --- Utility ---
void Graph::clearGraph() {
    for (auto& pair : roads) {
        delete pair.second;
    }
    roads.clear();

    for (auto& pair : intersections) {
        delete pair.second;
    }
    intersections.clear();
}

// --- Intersection Operations ---
void Graph::addIntersection(Intersection* intersection) {
    if (intersection != nullptr) {
        intersections[intersection->getId()] = intersection;
    }
}

void Graph::removeIntersection(int id) {
    auto it = intersections.find(id);
    if (it != intersections.end()) {
        Intersection* intersection = it->second;
        
// Remove all roads connected to this intersection
        std::vector<int> roadsToRemove;
        for (auto& road_pair : roads) {
            Road* road = road_pair.second;
            if (road->getStart()->getId() == id || road->getEnd()->getId() == id) {
                roadsToRemove.push_back(road->getId());
            }
        }
        
// Remove the roads
        for (int roadId : roadsToRemove) {
            removeRoad(roadId);
        }
        
// Remove the intersection
        intersections.erase(it);
        delete intersection;
    }
}

Intersection* Graph::getIntersection(int id) const {
    auto it = intersections.find(id);
    if (it != intersections.end()) {
        return it->second;
    }
    return nullptr; // Temporarily return nullptr so the code compiles
}

// --- Road Operations ---
void Graph::addRoad(Road* road) {
    if (road != nullptr) {
// Get the start and end intersections
        Intersection* start = road->getStart();
        Intersection* end = road->getEnd();
        
        if (start != nullptr && end != nullptr) {
 // Add road to the roads map
            roads[road->getId()] = road;
            
 // Update the intersections with incoming and outgoing roads
            start->addOutgoingRoad(road);
            end->addIncomingRoad(road);
        }
    }
}

void Graph::removeRoad(int id) {
    auto it = roads.find(id);
    if (it != roads.end()) {
        Road* road = it->second;
        
// Get the start and end intersections
        Intersection* start = road->getStart();
        Intersection* end = road->getEnd();
        
        if (start != nullptr && end != nullptr) {
// Remove road from the intersections
            start->removeOutgoingRoad(road);
            end->removeIncomingRoad(road);
        }
        
// Remove from roads map and delete
        roads.erase(it);
        delete road;
    }
}

Road* Graph::getRoad(int id) const {
    auto it = roads.find(id);
    if (it != roads.end()) {
        return it->second;
    }
    return nullptr; // Temporarily return nullptr so the code compiles
}

// --- Graph Functions ---
void Graph::updateRoadCondition(int roadId, double congestionLevel, bool blocked) {
    Road* road = getRoad(roadId);
    if (road != nullptr) {
        road->updateCongestionLevel(congestionLevel);
        if (blocked) {
            road->blockRoad();
        } else {
            road->unblockRoad();
        }
    }
}

std::vector<Road*> Graph::getConnectedRoads(int intersectionId) const {
    std::vector<Road*> connectedRoads;
    Intersection* intersection = getIntersection(intersectionId);
    
    if (intersection != nullptr) {
// Get all incoming roads
        std::vector<Road*> incoming = intersection->getIncomingRoads();
        connectedRoads.insert(connectedRoads.end(), incoming.begin(), incoming.end());
        
// Get all outgoing roads
        std::vector<Road*> outgoing = intersection->getOutgoingRoads();
        connectedRoads.insert(connectedRoads.end(), outgoing.begin(), outgoing.end());
    }
    
    return connectedRoads;
}
