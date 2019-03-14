#ifndef  _MAIN_HPP
#define  _MAIN_HPP

#include <immintrin.h>

#define WIDTH  800
#define HEIGTH 600
#define RED sf::Color::Red

sf::Uint8        *pixels  = new sf::Uint8[800 * 600 * 4];

__m256 evens = _mm256_set_ps(2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0);
__m256 odds  = _mm256_set_ps(1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0);

void putpixel(int x, int y, sf::Color)
{
    pixels[4 * ((y * WIDTH) + x) + 0]    = 255; // R?
    pixels[4 * ((y * WIDTH) + x) + 1]    = 0;   // G?
    pixels[4 * ((y * WIDTH) + x) + 2]    = 0;   // B?
    pixels[4 * ((y * WIDTH) + x) + 3]    = 255; // A?
}

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

#endif
