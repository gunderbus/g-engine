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
