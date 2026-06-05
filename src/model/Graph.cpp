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
    
}

void Graph::removeIntersection(int id) {
    
}

Intersection* Graph::getIntersection(int id) const {

    return nullptr; // Temporarily return nullptr so the code compiles
}

// --- Road Operations ---
void Graph::addRoad(Road* road) {

}

void Graph::removeRoad(int id) {

}

Road* Graph::getRoad(int id) const {

    return nullptr; // Temporarily return nullptr so the code compiles
}

// --- Graph Functions ---
void Graph::updateRoadCondition(int roadId, double congestionLevel, bool blocked) {

}

std::vector<Road*> Graph::getConnectedRoads(int intersectionId) const {

    return std::vector<Road*>(); // Temporarily return an empty vector
}