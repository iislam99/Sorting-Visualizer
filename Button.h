#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button
{
private:
    short unsigned buttonState;
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;
    sf::Color idleColor, hoverColor, activeColor;

public:
    Button(float x, float y, float width, float height,
        std::string text, float size, sf::Font,
        sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

    void checkClick(const sf::Vector2f mousePos);
    const bool isPressed() const;
    void render(sf::RenderTarget* target);
};