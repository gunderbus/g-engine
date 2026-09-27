#include <SFML/Graphics.hpp>
#include <string>
#include <vector>


namespace ui{
    class Button
    {
    public:
        Button(const std::string& text, sf::Vector2f position);
        void draw(sf::RenderWindow& window);
        bool isClicked(sf::Vector2f mousePosition);
    private:
        sf::Text text;
        sf::RectangleShape shape;
    };

    class Slider
    {
    public:
        Slider(sf::Vector2f position, float length){
            track.setPosition(position);
            thumb.setPosition(position);
            track.setSize(sf::Vector2f(length, 20));
            thumb.setSize(sf::Vector2f(20, 20));
            value = 0.0f;
        }
        void draw(sf::RenderWindow& window){
            window.draw(track);
            window.draw(thumb);
        }
        float getValue(){
            return value;
        }
        void setValue(float newValue){
            value = newValue;
        }
        float changeValue(float delta){
            value += delta;
            if(value < 0.0f) value = 0.0f;
            if(value > 1.0f) value = 1.0f;
            return value;
        }
    private:
        sf::RectangleShape track;
        sf::RectangleShape thumb;
        float value;
    };

    class MeasureBar
    {
    public:
        MeasureBar(sf::Vector2f position, float length){
            track.setPosition(position);
            fill.setPosition(position);
            track.setSize(sf::Vector2f(length, 20));
            fill.setSize(sf::Vector2f(0, 20));
            value = 0.0f;
        }
        void draw(sf::RenderWindow& window){
            window.draw(track);
            fill.setSize(sf::Vector2f(value * track.getSize().x, 20));
            window.draw(fill);
        }
        void setValue(float values){
            value = values;
        }
    private:
        sf::RectangleShape track;
        sf::RectangleShape fill;
        float value;
    };

    class Window
    {
    public:
        Window(const std::string& title, sf::Vector2f size);
        void draw(sf::RenderWindow& window);
    private:
        sf::RenderWindow renderWindow;
    };

    class InformationPanel
    {
    public:
        InformationPanel(sf::Vector2f position, sf::Vector2f size);
        void draw(sf::RenderWindow& window);
        void setText(const std::string& text);
    private:
        sf::RectangleShape shape;
        sf::Text name;
        std::vector<Slider> sliders;
        std::vector<MeasureBar> measureBars;
        std::vector<Button> buttons;
        std::vector<sf::Vector2f> order; // order will be placed by (type, index) with slider being 0 and measureBar being 1 and button being 2
    };
};
