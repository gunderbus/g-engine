#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <boolean>
#ifndef IMGS_HPP
#define IMGS_HPP
#pragma once

namespace imgs{
    std::vector<sf::Texture> textures;
    std::vector<sf::Sprite> sprites;
    
    class Image
    {
    public:
        Image(const std::string& filename){
            loadTexture(filename);
        }
        void loadTexture(const std::string& filename){
            texture.loadFromFile(filename);
        }
        void loadSprite(const std::string& filename){
            texture.loadFromFile(filename);
            sprite.setTexture(texture);
        }
        void draw(sf::RenderWindow& window, sf::Vector2f position){
            sprite.setPosition(position);
            window.draw(sprite);
        }

        void drawImgScale(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f scale){
            sprite.setPosition(position);
            sprite.setScale(scale);
            window.draw(sprite);
        }

        // fix
        void drawImgQuaterion(sf::RenderWindow& window, sf::Vector2f position,
                              sf::Vector2f scaleTopLeft, sf::Vector2f scaleBottomRight) {
            const sf::Vector2u size = texture.getSize();
            if (size.x == 0 || size.y == 0) {
                return;
            }

            const float width = static_cast<float>(size.x);
            const float height = static_cast<float>(size.y);

            sf::VertexArray quad(sf::Quads, 4);
            quad[0].position = position;
            quad[1].position = position + sf::Vector2f(width * scaleTopLeft.x, 0.f);
            quad[2].position = position + sf::Vector2f(
                width * scaleBottomRight.x, height * scaleBottomRight.y);
            quad[3].position = position + sf::Vector2f(0.f, height * scaleBottomRight.y);

            quad[0].texCoords = sf::Vector2f(0.f, 0.f);
            quad[1].texCoords = sf::Vector2f(width, 0.f);
            quad[2].texCoords = sf::Vector2f(width, height);
            quad[3].texCoords = sf::Vector2f(0.f, height);

            sf::RenderStates states;
            states.texture = &texture;
            window.draw(quad, states);
        }
    private:
        sf::Texture texture;
        sf::Sprite sprite;
    };

    class Animation
    {
    public:
        Animation(const std::string& filename);
        void loadFrames(const std::vector<std::string>& filenames){
            for (const auto& filename : filenames) {
                sf::Image frame;
                frame.loadFromFile(filename);
                frames.push_back(frame);
            }
        }

        void drawFrame(sf::RenderWindow& window, size_t frameIndex, sf::Vector2f position){
            if (frameIndex < frames.size()) {
                sf::Sprite sprite;
                sprite.setTexture(frames[frameIndex]);
                sprite.setPosition(position);
                window.draw(sprite);
            }
        }

        void drawAnimation(sf::RenderWindow& window, size_t frameIndex, sf::Vector2f position, float globalTime, float frameDuration){
            size_t frame = globalTime / frameDuration;
            frame = frame % frames.size();
            drawFrame(window, frame, position);
        }
    private:
        std::vector<sf::Image> frames;
    };
};

#endif // IMGS_HPP
