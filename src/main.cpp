#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "config.hpp"
#include "sim/headers/solver.hpp"
#include "renderer.hpp"
#include "rng/rng.hpp"

#define M_PI 3.14159265359

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

    const float constraintRadius = min(config::windowWidth, config::windowHeight) * 0.8f / 2;
    solver.setConstraint({(float) config::windowWidth / 2, (float) config::windowHeight / 2}, constraintRadius);
//    solver.setGravity({(float) config::windowWidth / 2, (float) config::windowHeight / 2}, 30.0f);
    solver.setSubSteps(8);
    solver.setSimulationUpdateRate(config::fps);

    // Set simulation attributes
    const float        object_spawn_delay    = 0.025f;
    const float        object_spawn_speed    = 1200.0f;
    const sf::Vector2f object_spawn_position = {500.0f, 200.0f};
    const float        object_min_radius     = 2.0f;
    const float        object_max_radius     = 10.0f;
    const uint32_t     max_objects_count     = 1000;
    const float        max_angle             = 1.0f;

    sf::Clock clock;
    // Main loop
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        if (solver.getObjectsCount() < max_objects_count && clock.getElapsedTime().asSeconds() >= object_spawn_delay) {
            clock.restart();
            auto&       object = solver.addObject(object_spawn_position,
                                                  RNG::randomFloatBetween(object_min_radius, object_max_radius));
            const float t      = solver.getTime();
            const float angle  = max_angle * sin(t) + M_PI * 0.5f;
            solver.setObjectVelocity(object, object_spawn_speed * sf::Vector2f{cos(angle), sin(angle)});
            object.color = getRainbow(t);
        }

        solver.update();
        window.clear(Color(80, 80 , 80));
        renderer.render(solver);
		window.display();
    }

    return 0;
}
