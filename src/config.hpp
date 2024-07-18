//
// Created by oscar on 14/07/2024.
//

#ifndef VERLETSIMULATION_CONFIG_HPP
#define VERLETSIMULATION_CONFIG_HPP

#include <SFML/Graphics.hpp>
using namespace sf;

namespace config {
    const Vector2f gravity = {0.0f, 1000.0f};
    constexpr int32_t windowWidth = 1000;
    constexpr int32_t windowHeight = 800;
    constexpr uint32_t fps = 60;
}

#endif //VERLETSIMULATION_CONFIG_HPP
