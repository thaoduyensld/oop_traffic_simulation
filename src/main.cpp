#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <algorithm>

#include "mapload.h"
#include "model/Graph.h"
#include "model/Intersection.h"
#include "model/Road.h"

int main(int argc, char** argv)
{
    const unsigned int windowW = 800;
    const unsigned int windowH = 600;
    std::string path;
    if (argc > 1) {
        path = argv[1];
    } else {
        std::cout << "Enter path to JSON map (leave blank to skip): ";
        std::getline(std::cin, path);
    }

    Graph graph;
    std::string error;

    // Allow retrying until user provides empty input or loading succeeds
    while (!path.empty()) {
        if (MapLoad::loadGraphFromJsonFile(path, graph, &error)) {
            std::cout << "Loaded map: " << path << std::endl;
            break;
        }
        std::cerr << "Failed to load map '" << path << "': " << error << std::endl;
        std::cout << "Enter another path (leave blank to skip): ";
        std::getline(std::cin, path);
    }

    sf::RenderWindow window(sf::VideoMode(windowW, windowH), "Urban Traffic Simulator - Map Test");
    window.setFramerateLimit(60);

    // Prepare drawable data
    auto intersections = graph.getAllIntersections();
    auto roads = graph.getAllRoads();

    double minX = 0, minY = 0, maxX = 0, maxY = 0;
    if (!intersections.empty()) {
        minX = maxX = intersections[0]->getX();
        minY = maxY = intersections[0]->getY();
        for (auto* it : intersections) {
            double x = it->getX();
            double y = it->getY();
            if (x < minX) minX = x;
            if (x > maxX) maxX = x;
            if (y < minY) minY = y;
            if (y > maxY) maxY = y;
        }
    }

    const float margin = 20.0f;
    double rangeX = (maxX - minX);
    double rangeY = (maxY - minY);
    double scaleX = (rangeX > 0.0) ? (windowW - 2*margin) / rangeX : 1.0;
    double scaleY = (rangeY > 0.0) ? (windowH - 2*margin) / rangeY : 1.0;
    double scale = std::min(scaleX, scaleY);

    auto worldToScreen = [&](double x, double y) -> sf::Vector2f {
        float sx = static_cast<float>(margin + (x - minX) * scale);
        // invert Y so larger world Y is up on screen
        float sy = static_cast<float>(windowH - margin - (y - minY) * scale);
        return { sx, sy };
    };

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
        }

        window.clear(sf::Color(30,30,30));

        // Draw roads
        for (auto* road : roads) {
            Intersection* s = road->getStart();
            Intersection* e = road->getEnd();
            if (!s || !e) continue;
            sf::Vector2f a = worldToScreen(s->getX(), s->getY());
            sf::Vector2f b = worldToScreen(e->getX(), e->getY());
            sf::Vertex line[] = {
                sf::Vertex(a, road->isBlocked() ? sf::Color::Red : sf::Color::White),
                sf::Vertex(b, road->isBlocked() ? sf::Color::Red : sf::Color::White)
            };
            window.draw(line, 2, sf::Lines);
        }

        // Draw intersections
        const float radius = 5.0f;
        for (auto* it : intersections) {
            sf::Vector2f p = worldToScreen(it->getX(), it->getY());
            sf::CircleShape circle(radius);
            circle.setOrigin(radius, radius);
            circle.setPosition(p);
            circle.setFillColor(sf::Color::Green);
            window.draw(circle);
        }

        window.display();
    }

    return 0;
}
