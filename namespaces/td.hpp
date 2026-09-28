#ifndef TD_HPP
#define TD_HPP
#pragma once
#include "imgs.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

namespace td {
    class Camera {
    public:
        Camera(sf::Vector3f position, sf::Vector3f target, sf::Vector3f up, float fov)
            : position(position), target(target), up(up), fov(fov) {}
    private:
        sf::Vector3f position;
        sf::Vector3f target;
        sf::Vector3f up;
        float fov;
    };
}
#endif
