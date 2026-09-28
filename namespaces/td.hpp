#include "imgs.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <bool>

namespace td {
    class Camera {
    public:
        Camera(sf::Vector3f position, sf::Vector3f target, sf::Vector3f up, float fov) {
            this->position = position;
            this->target = target;
            this->up = up;
            this->fov = fov;
        }
    private:
        sf::Vector3f position;
        sf::Vector3f target;
        sf::Vector3f up;
        float fov;
    }
}