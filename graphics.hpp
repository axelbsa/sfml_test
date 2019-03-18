#ifndef  _GRAPHICS_HPP
#define  _GRAPHICS_HPP 1

#include <immintrin.h>
#include "graphicsmath.hpp"

#define WIDTH  800
#define HEIGTH 600
#define RED sf::Color::Red
#define CYAN sf::Color::Cyan

sf::Uint8        *pixels  = new sf::Uint8[800 * 600 * 4];

__m256 evens = _mm256_set_ps(2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0);
__m256 odds  = _mm256_set_ps(1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0);

extern void line(Vector2 p1, Vector2 p2);
extern void putpixel(int x, int y, sf::Color);
extern void clearcolor();

void putpixel(int x, int y, sf::Color color)
{
    //fprintf(stderr, "Putting pixel at: X:%d, Y:%d\n", x, y);
    pixels[4 * ((y * WIDTH) + x) + 0]    = color.r; // R?
    pixels[4 * ((y * WIDTH) + x) + 1]    = color.g;   // G?
    pixels[4 * ((y * WIDTH) + x) + 2]    = color.b;   // B?
    pixels[4 * ((y * WIDTH) + x) + 3]    = 255; // A?
}

inline void clearcolor()
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

void circle(Vector2 centerPosition, int R)
{
    int p; // Decision parameter
    Vector2 curr_pos;

    curr_pos.x = 0;
    curr_pos.y = R;

    p = 1 - R;

    for (int i = 0; curr_pos.x <= curr_pos.y; i++)
    {
        putpixel((curr_pos.x + centerPosition.x), (curr_pos.y + centerPosition.y), CYAN);
        if(p < 0)
        {
            curr_pos.x = curr_pos.x + 1;
            curr_pos.y = curr_pos.y;
            p = p + 2 * curr_pos.x + 3;
        }
        else
        {
            curr_pos.x = curr_pos.x + 1;
            curr_pos.y = curr_pos.y - 1;
            p = p + 2 * curr_pos.x - 2 * curr_pos.y + 5;
        }

        putpixel((curr_pos.x + centerPosition.x), (-curr_pos.y + centerPosition.y), CYAN);
        putpixel((-curr_pos.x + centerPosition.x), (curr_pos.y + centerPosition.y), CYAN);
        putpixel((-curr_pos.x + centerPosition.x), (-curr_pos.y + centerPosition.y), CYAN);
        putpixel((curr_pos.y + centerPosition.x), (curr_pos.x + centerPosition.y), CYAN);
        putpixel((curr_pos.y + centerPosition.x), (-curr_pos.x + centerPosition.y), CYAN);
        putpixel((-curr_pos.y + centerPosition.x), (curr_pos.x + centerPosition.y), CYAN);
        putpixel((-curr_pos.y + centerPosition.x), (-curr_pos.x + centerPosition.y), CYAN);
    }

}

void circle(Vector3 centerPosition, int R)
{
    int p; // Decision parameter
    Vector2 curr_pos;

    curr_pos.x = 0;
    curr_pos.y = R;

    p = 1 - R;

    for (int i = 0; curr_pos.x <= curr_pos.y; i++)
    {
        putpixel((curr_pos.x + centerPosition.x), (curr_pos.y + centerPosition.y), CYAN);
        if(p < 0)
        {
            curr_pos.x = curr_pos.x + 1;
            curr_pos.y = curr_pos.y;
            p = p + 2 * curr_pos.x + 3;
        }
        else
        {
            curr_pos.x = curr_pos.x + 1;
            curr_pos.y = curr_pos.y - 1;
            p = p + 2 * curr_pos.x - 2 * curr_pos.y + 5;
        }

        putpixel((curr_pos.x + centerPosition.x), (-curr_pos.y + centerPosition.y), CYAN);
        putpixel((-curr_pos.x + centerPosition.x), (curr_pos.y + centerPosition.y), CYAN);
        putpixel((-curr_pos.x + centerPosition.x), (-curr_pos.y + centerPosition.y), CYAN);
        putpixel((curr_pos.y + centerPosition.x), (curr_pos.x + centerPosition.y), CYAN);
        putpixel((curr_pos.y + centerPosition.x), (-curr_pos.x + centerPosition.y), CYAN);
        putpixel((-curr_pos.y + centerPosition.x), (curr_pos.x + centerPosition.y), CYAN);
        putpixel((-curr_pos.y + centerPosition.x), (-curr_pos.x + centerPosition.y), CYAN);
    }

}

//void line(int xa, int ya, int xb, int yb)
void line(Vector2 p1, Vector2 p2)
{
    int p;
    int i;
    int signx, signy;

    Vector2 dest;       // Destination vector?
    Vector2 curr_point; // Coordinates for drawing, starting at xa,ya and goes to xb,yb

    dest = Vector2Subtract(p2, p1);
    
    curr_point.x = p1.x;
    curr_point.y = p1.y;

    signx = dest.x >= 0 ? 1 : -1; // Used to dertimene negative values on a spehere
    signy = dest.y >= 0 ? 1 : -1;

    if (abs(dest.y) < abs(dest.x))
    {
        p = (2 * dest.y * signy) - (dest.x * signx);
        for (i = 0; i <= dest.x * signx; i++) 
        {
                putpixel(floor(curr_point.x),floor(curr_point.y),RED);
                if (p < 0)
                {
                    curr_point.x = curr_point.x + signx;
                    curr_point.y = curr_point.y;
                    p = p + (2 * dest.y * signy);
                }
                else
                {
                    curr_point.x = curr_point.x + signx;
                    curr_point.y = curr_point.y + signy;
                    p = p + (2 * dest.y * signy) - (2 * dest.x * signx);
                }
            }
    }
    else
    {
        p = (2 * dest.x * signx - dest.y * signy);
        for( i = 0; i <= dest.y * signy; i++)
        {
            putpixel(floor(curr_point.x),floor(curr_point.y),RED);
            if (p < 0)
            {
                curr_point.x = curr_point.x;
                curr_point.y = curr_point.y + signy;
                p = p + 2 * dest.x * signx;
            }
            else
            {
                curr_point.x = curr_point.x + signx;
                curr_point.y = curr_point.y + signy;
                p = p + (2 * dest.x * signx) - (2 * dest.y * signy);
            }
        }
    }
}

#endif
