#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "config.hpp"
#include "sim/headers/solver.hpp"
#include "renderer.hpp"

void spawnDoublePendulum(Solver &solver, Vector2<double> firstBallPos, Vector2<double> secondBallPos,
                         double objectRadius, int i);

Vector2<double> calculateObjectSpawnPositionBasedOnAngle(double angle, Vector2<double> vector2, double radius);

using namespace sf;
using namespace std;

static sf::Color getRainbow(double t) {
    const double r = sin(t);
    const double g = sin(t + 0.33f * 2.0f * M_PI);
    const double b = sin(t + 0.66f * 2.0f * M_PI);
    return {static_cast<uint8_t>(255.0f * r * r),
            static_cast<uint8_t>(255.0f * g * g),
            static_cast<uint8_t>(255.0f * b * b)};
}

static sf::Color getGreenToBlue(double t) {
    // t should be between 0 and 1
    const double g = sin(t * M_PI); // Green goes from 0 to 1 to 0
    const double b = cos(t * M_PI); // Blue goes from 1 to 0 to 1
    return {static_cast<uint8_t>(73),
            static_cast<uint8_t>(255.0f * g * g),
            static_cast<uint8_t>(219)};
}

static sf::Color getRainbowByIndex(int index, int total) {
    double t = static_cast<double>(index) / total;
    return getRainbow(t * 2.0 * M_PI);
}

static sf::Color getGreenToBlueByIndex(int index, int total) {
    double t = static_cast<double>(index) / total;
    return getGreenToBlue(t);
}

// Set simulation attributes
const double objectRadius = 2.0f;
const int objectCount = 50;

int main() {
    RenderWindow window(VideoMode(config::windowWidth, config::windowHeight),
                        "Verlet Simulation", Style::Default, ContextSettings(0, 0, 8));
    window.setFramerateLimit(config::fps);

    Solver solver;
    Renderer renderer(window);

    const double constraintRadius = 200.0f;
    Vector2<double> constraintCenter = {config::windowWidth / 2, config::windowHeight / 2};
    solver.setConstraint(constraintCenter, constraintRadius);
//    solver.setGravity({(float) config::windowWidth / 2, (float) config::windowHeight / 2}, 30.0f);
    solver.setSubSteps(8);
    solver.setSimulationUpdateRate(config::fps);
    double angle = M_PI / 2;



    Vector2<double> firstBallPos;
    Vector2<double> secondBallPos;
    int i = 0;
    while (i < objectCount) {
        angle += 1e-10;
        firstBallPos = calculateObjectSpawnPositionBasedOnAngle(angle, constraintCenter, constraintRadius);
        secondBallPos = calculateObjectSpawnPositionBasedOnAngle(angle, constraintCenter, constraintRadius * 2);
        spawnDoublePendulum(solver, firstBallPos, secondBallPos, objectRadius, i);
        i++;
    }
    // Main loop
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        solver.update();
        window.clear(Color(30, 30, 30));
        renderer.render(solver);
		window.display();
    }

    return 0;
}

Vector2<double> calculateObjectSpawnPositionBasedOnAngle(double angle, Vector2<double> vector2, const double radius) {
    return {vector2.x + radius * cos(angle), vector2.y - radius * sin(angle)};
}

void spawnDoublePendulum(Solver &solver, const Vector2<double> firstBallPos, const Vector2<double> secondBallPos,
                         const double objectRadius, int i) {
    int64_t objectId = solver.addObject(firstBallPos, 0);
    solver.addObject(secondBallPos, objectRadius, objectId,
                     true, getGreenToBlueByIndex(i, objectCount));
}
