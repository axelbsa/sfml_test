#include<stdio.h>
#include<math.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>

#include "main.hpp"


sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Test");
sf::Texture      texture;
sf::Sprite       sprite;

sf::Time thetime;
sf::Clock sf_clock;
sf::Text text;
sf::Font font;





int main()
{
    char c[100];

    texture.create(WIDTH, HEIGTH);
    font.loadFromFile("FSEX300.ttf");

    int xarrow = 0;
    int yarrow = 0;

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                // move left...
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                // move right...
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
        }

        // clear the window with black color
        //window.clear(sf::Color::Black);
        clearcolor();
        if (xarrow % 799 == 0)
            xarrow = 0;

        if (yarrow % 599 == 0)
            yarrow = 0;

        line(400, 300, 799, yarrow++);
        line(400, 300, xarrow++, 599);

        sprintf(c, "Hello");
        text.setFont(font);
        text.setString(std::string(c));
        text.setFillColor(sf::Color(2,125,240));
        text.setPosition(700, 550);

        texture.update(pixels);
        sprite.setTexture(texture);
        window.draw(sprite);
        window.draw(text);

        // end the current frame
        window.display();
    }

    return 0;
}
