#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "config.hpp"
#include "sim/headers/solver.hpp"
#include "renderer.hpp"
#include "rng/rng.hpp"

#define M_PI 3.14159265359

void spawnDoublePendulum(Solver &solver, const Vector2f &objectSpawnPosition, const float objectRadius);

using namespace sf;
using namespace std;

static sf::Color getRainbow(float t)
{
    const float r = sin(t);
    const float g = sin(t + 0.33f * 2.0f * M_PI);
    const float b = sin(t + 0.66f * 2.0f * M_PI);
    return {static_cast<uint8_t>(255.0f * r * r),
            static_cast<uint8_t>(255.0f * g * g),
            static_cast<uint8_t>(255.0f * b * b)};
}

int main() {
    RenderWindow window(VideoMode(config::windowWidth, config::windowHeight),
                        "Verlet Simulation", Style::Default, ContextSettings(0, 0, 8));
    window.setFramerateLimit(config::fps);

    Solver solver;
    Renderer renderer(window);

    const float constraintRadius = 200.0f;
    solver.setConstraint({(float) config::windowWidth / 2, (float) config::windowHeight / 2}, constraintRadius);
//    solver.setGravity({(float) config::windowWidth / 2, (float) config::windowHeight / 2}, 30.0f);
    solver.setSubSteps(8);
    solver.setSimulationUpdateRate(config::fps);

    // Set simulation attributes
    const sf::Vector2f objectSpawnPosition = {(float) config::windowWidth / 2 + constraintRadius, 200.0f};
    const float        objectRadius     = 1.0f;

    spawnDoublePendulum(solver, objectSpawnPosition, objectRadius);


    // Main loop
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        solver.update();
        window.clear(Color(80, 80 , 80));
        renderer.render(solver);
		window.display();
    }

    return 0;
}

void spawnDoublePendulum(Solver &solver, const Vector2f &objectSpawnPosition, const float objectRadius) {
    int64_t objectId = solver.addObject(objectSpawnPosition, 0);
    solver.addObject({(float) config::windowWidth / 2, (float) config::windowHeight / 2}, objectRadius, objectId,
                     true);
}
