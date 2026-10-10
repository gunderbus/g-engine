#ifndef UI_HPP
#define UI_HPP

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <string>
#include <vector>

namespace ui {
    class Button {
    public:
        Button(const std::string& label, sf::Vector2f position,
               sf::Vector2f size = {120.f, 36.f}) {
            text.setString(label);
            shape.setPosition(position);
            shape.setSize(size);
            text.setPosition(position);
        }

        void setFont(const sf::Font& font) { text.setFont(font); }
        void setCharacterSize(unsigned int size) { text.setCharacterSize(size); }
        void setFillColor(sf::Color color) { shape.setFillColor(color); }
        void setTextColor(sf::Color color) { text.setFillColor(color); }
        void setPosition(sf::Vector2f position) {
            shape.setPosition(position);
            text.setPosition(position);
        }
        void draw(sf::RenderTarget& target) const {
            target.draw(shape);
            target.draw(text);
        }
        bool isHovered(sf::Vector2f point) const {
            return shape.getGlobalBounds().contains(point);
        }
        bool isClicked(sf::Vector2f point, bool pressed) const {
            return pressed && isHovered(point);
        }

    private:
        sf::Text text;
        sf::RectangleShape shape;
    };

    class Slider {
    public:
        Slider(sf::Vector2f position, float length)
            : position(position), length(std::max(0.f, length)) {
            track.setPosition(position);
            track.setSize({this->length, 20.f});
            thumb.setSize({20.f, 20.f});
            updateThumb();
        }
        void draw(sf::RenderTarget& target) const {
            target.draw(track);
            target.draw(thumb);
        }
        float getValue() const { return value; }
        void setValue(float next) {
            value = std::clamp(next, 0.f, 1.f);
            updateThumb();
        }
        float changeValue(float delta) {
            setValue(value + delta);
            return value;
        }

    private:
        void updateThumb() {
            thumb.setPosition({position.x + value * length, position.y});
        }
        sf::Vector2f position;
        float length;
        float value{};
        sf::RectangleShape track;
        sf::RectangleShape thumb;
    };

    class MeasureBar {
    public:
        MeasureBar(sf::Vector2f position, float length)
            : length(std::max(0.f, length)) {
            track.setPosition(position);
            track.setSize({this->length, 20.f});
            fill.setPosition(position);
            fill.setSize({0.f, 20.f});
        }
        void draw(sf::RenderTarget& target) const {
            target.draw(track);
            target.draw(fill);
        }
        void setValue(float next) {
            value = std::clamp(next, 0.f, 1.f);
            fill.setSize({value * length, 20.f});
        }
        float getValue() const { return value; }

    private:
        float length;
        float value{};
        sf::RectangleShape track;
        sf::RectangleShape fill;
    };

    class Window {
    public:
        Window(const std::string& title, sf::Vector2f size)
            : renderWindow(sf::VideoMode(static_cast<unsigned int>(size.x),
                                         static_cast<unsigned int>(size.y)), title) {}

        bool isOpen() const { return renderWindow.isOpen(); }
        bool pollEvent(sf::Event& event) { return renderWindow.pollEvent(event); }
        void clear(sf::Color color = sf::Color::Black) { renderWindow.clear(color); }
        void draw(const sf::Drawable& drawable,
                  const sf::RenderStates& states = sf::RenderStates::Default) {
            renderWindow.draw(drawable, states);
        }
        void display() { renderWindow.display(); }
        void close() { renderWindow.close(); }
        sf::RenderWindow& nativeWindow() { return renderWindow; }

    private:
        sf::RenderWindow renderWindow;
    };

    class InformationPanel {
    public:
        InformationPanel(sf::Vector2f position, sf::Vector2f size) {
            shape.setPosition(position);
            shape.setSize(size);
        }
        void setFont(const sf::Font& font) { name.setFont(font); }
        void setText(const std::string& value) { name.setString(value); }
        void setTextPosition(sf::Vector2f position) { name.setPosition(position); }
        void addSlider(const Slider& slider) { sliders.push_back(slider); }
        void addMeasureBar(const MeasureBar& bar) { measureBars.push_back(bar); }
        void addButton(const Button& button) { buttons.push_back(button); }
        void draw(sf::RenderTarget& target) const {
            target.draw(shape);
            target.draw(name);
            for (const auto& slider : sliders) slider.draw(target);
            for (const auto& bar : measureBars) bar.draw(target);
            for (const auto& button : buttons) button.draw(target);
        }

    private:
        sf::RectangleShape shape;
        sf::Text name;
        std::vector<Slider> sliders;
        std::vector<MeasureBar> measureBars;
        std::vector<Button> buttons;
    };
}

#endif // UI_HPP
