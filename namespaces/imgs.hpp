#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#ifndef IMGS_HPP
#define IMGS_HPP
#pragma once

namespace imgs {
    class Image {
    public:
        Image() = default;
        explicit Image(const std::string& filename) { loadTexture(filename); }
        bool loadTexture(const std::string& filename) { return texture.loadFromFile(filename); }
        bool loadSprite(const std::string& filename) { if (!texture.loadFromFile(filename)) return false; sprite.setTexture(texture); return true; }
        void draw(sf::RenderWindow& window, sf::Vector2f position) { sprite.setPosition(position); window.draw(sprite); }
        void drawImgScale(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f scale) { sprite.setPosition(position); sprite.setScale(scale); window.draw(sprite); }
        void drawImgQuaterion(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f scaleTopLeft, sf::Vector2f scaleBottomRight) {
            const auto size=texture.getSize(); if(!size.x||!size.y)return;
            const float w=float(size.x),h=float(size.y);sf::VertexArray quad(sf::Quads,4);
            quad[0].position=position;quad[1].position=position+sf::Vector2f(w*scaleTopLeft.x,0);quad[2].position=position+sf::Vector2f(w*scaleBottomRight.x,h*scaleBottomRight.y);quad[3].position=position+sf::Vector2f(0,h*scaleBottomRight.y);
            quad[0].texCoords={0,0};quad[1].texCoords={w,0};quad[2].texCoords={w,h};quad[3].texCoords={0,h};sf::RenderStates states;states.texture=&texture;window.draw(quad,states);
        }
    private: sf::Texture texture;sf::Sprite sprite;
    };
    class Animation {
    public:
        explicit Animation(const std::string&) {}
        void loadFrames(const std::vector<std::string>& filenames) { for(const auto& f:filenames){sf::Texture frame;if(frame.loadFromFile(f))frames.push_back(std::move(frame));} }
        void drawFrame(sf::RenderWindow& window,size_t index,sf::Vector2f position) { if(index<frames.size()){sf::Sprite s(frames[index]);s.setPosition(position);window.draw(s);} }
        void drawAnimation(sf::RenderWindow& window,size_t frameIndex,sf::Vector2f position,float globalTime,float frameDuration) { if(frames.empty()||frameDuration<=0)return;auto frame=(frameIndex+size_t(globalTime/frameDuration))%frames.size();drawFrame(window,frame,position); }
    private: std::vector<sf::Texture> frames;
    };
}
#endif
