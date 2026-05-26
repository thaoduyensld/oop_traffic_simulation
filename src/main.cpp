#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Urban Traffic Simulator");
    window.setFramerateLimit(60);

    std::cout << "Starting Urban Traffic Simulator..." << std::endl;

    // Start the main loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Clear screen
        window.clear(sf::Color::Black);

        // Display the window contents
        window.display();
    }

    std::cout << "Exiting Urban Traffic Simulator." << std::endl;
    return 0;
}
