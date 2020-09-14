#include <SFML/Graphics.hpp>
#include "user_interface.h"

int main()
{
    unsigned int screenHeight = 600;
    unsigned int screenWidth = screenHeight * 1.5;
    sf::RenderWindow win(sf::VideoMode(screenWidth, screenHeight), "Sorting Visualizer");

    // Font
    sf::Font font;
    font.loadFromFile("Fonts/ArialTh.ttf");

    user_interface UI(&win, screenWidth, screenHeight, &font);
    
    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    win.close();
                    break;
                }
                default:
                    break;
            }
        }

        /*win.clear(sf::Color(255, 255, 255, 255));
        win.draw(toolbar);*/
        
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(win));
        UI.checkButtonClick(mousePos, &win);
        UI.render();
    }

    return 0;
}