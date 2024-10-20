#define _USE_MATH_DEFINES
#include <cmath>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cmath>
#include <iostream>

#define BALL_SPEED 1.4142
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 640

float directionX = 1.f;
float directionY = 1.f;

sf::CircleShape createCircle(float radius, sf::Vector2f position, sf::Color color) {
    sf::CircleShape circle;
    circle.setRadius(radius);
    circle.setPosition(position);
    circle.setFillColor(color);
    return circle;
}

// Function to find the value of the circle for X and Y axis so that speed remains constant 
void const_speed(float* valueX, float* valueY) {
    float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float angle = random * 2 * M_PI; // Random angle between 0 and 2*PI

    *valueX = BALL_SPEED * cos(angle);
    *valueY = BALL_SPEED * sin(angle);
}

void collison_check(sf::CircleShape* circle, float* valueX, float* valueY) {
    // For left
    if (circle->getPosition().x <= 0) {
        circle->setPosition(0.f, circle->getPosition().y);
        *valueX = -(*valueX);
    }
    // For right
    else if (circle->getPosition().x + circle->getGlobalBounds().width >= WINDOW_WIDTH) {
        circle->setPosition(WINDOW_WIDTH - circle->getGlobalBounds().width, circle->getPosition().y);
        *valueX = -(*valueX);
    }
    // For top
    if (circle->getPosition().y <= 0) {
        circle->setPosition(circle->getPosition().x, 0.f);
        *valueY = -(*valueY);
    }
    // For bottom
    else if (circle->getPosition().y + circle->getGlobalBounds().height >= WINDOW_HEIGHT) {
        circle->setPosition(circle->getPosition().x, WINDOW_HEIGHT - circle->getGlobalBounds().height);
        *valueY = -(*valueY);
    }
}

int main() {
    srand(static_cast<unsigned int>(time(NULL))); // Seed the random number generator
    auto window = sf::RenderWindow({ WINDOW_WIDTH, WINDOW_HEIGHT }, "Random Motion");
    window.setFramerateLimit(60);
    sf::CircleShape circle = createCircle(5.f, sf::Vector2f(25.f, 25.f), sf::Color::Green);

    sf::Clock clock;
    float valueX = 1.f, valueY = 1.f; // Initialize speed values

    while (window.isOpen()) {
        for (auto event = sf::Event(); window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Check elapsed time
        if (clock.getElapsedTime().asSeconds() >= 3.0) {
            // Update speed values
            const_speed(&valueX, &valueY); // Call your speed update function
            clock.restart(); // Reset clock
        }

        circle.move(valueX, valueY); // Use the values for moving the circle
        collison_check(&circle, &valueX, &valueY); // Check for collisions

        window.clear();
        window.draw(circle);

        window.display();
    }
}
