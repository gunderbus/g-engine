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
        Slider(sf::Vector2f position, float length);
        void draw(sf::RenderWindow& window);
        float getValue();
    private:
        sf::RectangleShape track;
        sf::RectangleShape thumb;
    };

    class MeasureBar
    {
    public:
        MeasureBar(sf::Vector2f position, float length);
        void draw(sf::RenderWindow& window);
        void setValue(float value);
    private:
        sf::RectangleShape track;
        sf::RectangleShape fill;
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
    };
};
