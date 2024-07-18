//
// Created by oscar on 14/07/2024.
//

#ifndef VERLETSIMULATION_CONFIG_HPP
#define VERLETSIMULATION_CONFIG_HPP

#include <SFML/Graphics.hpp>
using namespace sf;

namespace config {
    const Vector2<double> gravity = {0.0f, 1000.0f};
    constexpr double windowWidth = 1000;
    constexpr double windowHeight = 900;
    constexpr uint32_t fps = 144;
}

#endif //VERLETSIMULATION_CONFIG_HPP
