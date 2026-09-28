#include <SFML/Graphics.hpp>
#include <algorithm>
#include <string>
#include <vector>
#ifndef UI_HPP
#define UI_HPP
#pragma once

namespace ui {
    class Button {
    public:
        Button(const std::string& label, sf::Vector2f position) { text.setString(label);shape.setPosition(position);text.setPosition(position); }
        void draw(sf::RenderWindow& window) { window.draw(shape);window.draw(text); }
        bool isHovered(sf::Vector2f p) { return shape.getGlobalBounds().contains(p); }
        bool isClicked(sf::Vector2f p,bool pressed) { return pressed&&isHovered(p); }
    private: sf::Text text;sf::RectangleShape shape;
    };
    class Slider {
    public:
        Slider(sf::Vector2f position,float length) { track.setPosition(position);thumb.setPosition(position);track.setSize({length,20});thumb.setSize({20,20});value=0; }
        void draw(sf::RenderWindow& window) { window.draw(track);window.draw(thumb); }
        float getValue() const { return value; }
        void setValue(float next) { value=std::clamp(next,0.f,1.f); }
        float changeValue(float delta) { setValue(value+delta);return value; }
    private: sf::RectangleShape track,thumb;float value{};
    };
    class MeasureBar {
    public:
        MeasureBar(sf::Vector2f position,float length) { track.setPosition(position);fill.setPosition(position);track.setSize({length,20});fill.setSize({0,20}); }
        void draw(sf::RenderWindow& window) { window.draw(track);fill.setSize({value*track.getSize().x,20});window.draw(fill); }
        void setValue(float next) { value=std::clamp(next,0.f,1.f); }
    private: sf::RectangleShape track,fill;float value{};
    };
    class Window {
    public:
        Window(const std::string& title,sf::Vector2f size):renderWindow(sf::VideoMode((unsigned)size.x,(unsigned)size.y),title){}
        void draw(sf::RenderWindow&) {}
    private: sf::RenderWindow renderWindow;
    };
    class InformationPanel {
    public:
        InformationPanel(sf::Vector2f position,sf::Vector2f size) { shape.setPosition(position);shape.setSize(size); }
        void draw(sf::RenderWindow& window) { window.draw(shape);window.draw(name);for(auto& s:sliders)s.draw(window);for(auto& b:measureBars)b.draw(window);for(auto& b:buttons)b.draw(window); }
        void setText(const std::string& value) { name.setString(value); }
    private: sf::RectangleShape shape;sf::Text name;std::vector<Slider> sliders;std::vector<MeasureBar> measureBars;std::vector<Button> buttons;std::vector<sf::Vector2f> order;
    };
}
#endif
