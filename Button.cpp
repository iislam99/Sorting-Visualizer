#include "Button.h"

enum buttonStates { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

Button::Button(float x, float y, float width, float height,
    std::string text, float size, sf::Font font,
    sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
    // Default button state
    this->buttonState = BTN_IDLE;

    // Button size and position
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));

    // Button color
    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    // Button text
    this->font = font;
    this->text.setFont(this->font);
    this->text.setString(text);
    this->text.setCharacterSize(size);
    this->text.setFillColor(sf::Color::White);
    this->text.setPosition(
        this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2 - this->text.getGlobalBounds().width / 2,
        this->shape.getPosition().y + this->shape.getGlobalBounds().height / 3 - this->text.getGlobalBounds().height / 2
    );
}

void Button::checkClick(const sf::Vector2f mousePos)
{
    this->buttonState = BTN_IDLE;
    if (this->shape.getGlobalBounds().contains(mousePos))
    {
        this->buttonState = BTN_HOVER;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            this->buttonState = BTN_ACTIVE;
    }
    switch (this->buttonState)
    {
    case BTN_IDLE:
        this->shape.setFillColor(this->idleColor);
        break;

    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        break;

    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        break;

    default:
        this->shape.setFillColor(this->idleColor);
        break;
    }
}

const bool Button::isPressed() const
{
    if (this->buttonState == BTN_ACTIVE)
        return true;
    return false;
}

void Button::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
    target->draw(this->text);
}