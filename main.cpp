#include<stdio.h>
#include<math.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>

#include "main.hpp"

#define WIDTH  800
#define HEIGTH 600
#define RED sf::Color::Red

sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Test");
sf::Texture      texture;
sf::Sprite       sprite;
sf::Uint8        *pixels  = new sf::Uint8[800 * 600 * 4];

sf::Time thetime;
sf::Clock sf_clock;
sf::Text text;
sf::Font font;

void clearcolor()
{
    for(int x = 0; x < WIDTH; x++)
    {
        for(int y = 0; y < HEIGTH; y++)
        {
            pixels[4 * ((y * WIDTH) + x) + 0]    = 25; // R?
            pixels[4 * ((y * WIDTH) + x) + 1]    = 25; // G?
            pixels[4 * ((y * WIDTH) + x) + 2]    = 25; // B?
            pixels[4 * ((y * WIDTH) + x) + 3]    = 255; // A?
        }
    }
}

void putpixel(int x, int y, sf::Color)
{
    pixels[4 * ((y * WIDTH) + x) + 0]    = 255; // R?
    pixels[4 * ((y * WIDTH) + x) + 1]    = 0;   // G?
    pixels[4 * ((y * WIDTH) + x) + 2]    = 0;   // B?
    pixels[4 * ((y * WIDTH) + x) + 3]    = 255; // A?
}

void line(int xa, int ya, int xb, int yb)
{
    int dx, dy; // Destination coordinates
    int x, y;   // Coordinates for drawing, starting at xa,ya and goes to xb,yb
    int p;
    int i;
    int signx, signy;

    dx = xb - xa;
    dy = yb - ya;
    x = xa;
    y = ya;

    signx = dx >= 0 ? 1 : -1;
    signy = dy >= 0 ? 1 : -1;

    if (abs(dy) < abs(dx))
    {
        p = (2 * dy * signy) - (dx * signx);
        for (i = 0; i <= dx * signx; i++) 
        {
                putpixel(floor(x),floor(y),RED);
                if (p < 0)
                {
                    x = x + signx;
                    y = y;
                    p = p + (2 * dy * signy);
                }
                else
                {
                    x = x + signx;
                    y = y + signy;
                    p = p + (2 * dy * signy) - (2 * dx * signx);
                }
            }
    }
    else
    {
        p = (2 * dx * signx - dy * signy);
        for( i = 0; i <= dy * signy; i++)
        {
            putpixel(floor(x),floor(y),RED);
            if (p < 0)
            {
                x = x;
                y = y + signy;
                p = p + 2 * dx * signx;
            }
            else
            {
                x=x+signx;
                y=y+signy;
                p=p+(2*dx*signx) - (2*dy* signy);
            }
        }
    }
}


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
