#include<stdio.h>
#include<math.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>

#include "graphics.hpp"

#define MIDDLE_X WIDTH/2
#define MIDDLE_Y HEIGTH/2

sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Test");
sf::Texture      texture;
sf::Sprite       sprite;

sf::Time thetime;
sf::Clock sf_clock;
sf::Text text;
sf::Font font;

Vector2 foo;
Vector3 points[8];

Matrix_3x3 projection = {0};

Matrix_3x3 rotationX = {0};
Matrix_3x3 rotationY = {0};
Matrix_3x3 rotationZ = {0};

int main()
{
    char c[100];
    float angle = -0.2;

    // Projection Matrix Rows
    projection.m0 = 1; projection.m3 = 0; projection.m6 = 0;
    projection.m1 = 0; projection.m4 = 1; projection.m7 = 0;
    projection.m2 = 0; projection.m5 = 0; projection.m8 = 0;

    rotationX.m0 = 1;  rotationX.m3 = 0;           rotationX.m6 = 0;
    rotationX.m1 = 0;  rotationX.m4 =  cos(angle); rotationX.m7 = -sin(angle);
    rotationX.m2 = 0;  rotationX.m5 =  sin(angle); rotationX.m8 = cos(angle);

    rotationY.m0 = cos(angle);  rotationY.m3 = 0; rotationY.m6 = sin(angle);
    rotationY.m1 = 0;           rotationY.m4 = 1; rotationY.m7 = 0;
    rotationY.m2 = -sin(angle); rotationY.m5 = 0; rotationY.m8 = cos(angle);

    rotationZ.m0 = cos(angle);  rotationZ.m2 = -sin(angle); rotationZ.m3 = 0;
    rotationZ.m1 = sin(angle);  rotationZ.m3 =  cos(angle); rotationZ.m5 = 0;
    rotationZ.m2 = 0;           rotationZ.m5 =  0;          rotationZ.m8 = 1;

    texture.create(WIDTH, HEIGTH);
    font.loadFromFile("FSEX300.ttf");

    Vector2 line1_p1 = {WIDTH/2, HEIGTH/2};
    Vector2 line1_p2 = {300, 100};

    Vector2 line2_p1 = {WIDTH/2, HEIGTH/2};
    Vector2 line2_p2 = {600, (HEIGTH/2) + 120};

    Vector2 circleCenter = {400, 300};

    //points[0] = {MIDDLE_X - 50, MIDDLE_Y - 50, -50};
    //points[1] = {MIDDLE_X + 50, MIDDLE_Y - 50, -50};
    //points[2] = {MIDDLE_X + 50, MIDDLE_Y + 50, -50};
    //points[3] = {MIDDLE_X - 50, MIDDLE_Y + 50, -50};

    //points[4] = {MIDDLE_X - 50, MIDDLE_Y - 50, 50};
    //points[5] = {MIDDLE_X + 50, MIDDLE_Y - 50, 50};
    //points[6] = {MIDDLE_X + 50, MIDDLE_Y + 50, 50};
    //points[7] = {MIDDLE_X - 50, MIDDLE_Y + 50, 50};

    points[0] = { -50, -50, -50};
    points[1] = {  50, -50, -50};
    points[2] = {  50,  50, -50};
    points[3] = { -50,  50, -50};

    points[4] = { -50, -50, 50};
    points[5] = {  50, -50, 50};
    points[6] = {  50,  50, 50};
    points[7] = { -50,  50, 50};

    int radius = 250;

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

        rotationX.m0 = 1;  rotationX.m3 = 0;           rotationX.m6 = 0;
        rotationX.m1 = 0;  rotationX.m4 =  cos(angle); rotationX.m7 = -sin(angle);
        rotationX.m2 = 0;  rotationX.m5 =  sin(angle); rotationX.m8 = cos(angle);

        rotationY.m0 = cos(angle);  rotationY.m3 = 0; rotationY.m6 = sin(angle);
        rotationY.m1 = 0;           rotationY.m4 = 1; rotationY.m7 = 0;
        rotationY.m2 = -sin(angle); rotationY.m5 = 0; rotationY.m8 = cos(angle);

        rotationZ.m0 = cos(angle);  rotationZ.m2 = -sin(angle); rotationZ.m3 = 0;
        rotationZ.m1 = sin(angle);  rotationZ.m3 =  cos(angle); rotationZ.m5 = 0;
        rotationZ.m2 = 0;           rotationZ.m5 =  0;          rotationZ.m8 = 1;
        //rotation.m0 = cos(angle);  rotation.m2 = -sin(angle); rotation.m3 = 0;
        //rotation.m1 = sin(angle);  rotation.m3 =  cos(angle); rotation.m5 = 0;

        // clear the window with black color
        //window.clear(sf::Color::Black);
        clearcolor();

        //line(line1_p1, line1_p2);
        //line(line2_p1, line2_p2);
        circle(circleCenter, radius);

        //sprintf(c, "Hei, Nora");
        //text.setFont(font);
        //text.setString(std::string(c));
        //text.setFillColor(sf::Color(2,125,240));
        //text.setPosition(10, 10);

        //window.draw(text);

        //define a circle with radius = 200
        //sf::CircleShape circleShape(200);
        //circleShape.setRadius(240);
        //circleShape.setPointCount(100);
        //circleShape.setPosition(160, 60);
        //circleShape.setFillColor(sf::Color(150, 50, 250, 0));
        //circleShape.setOutlineColor(sf::Color(250, 150, 100));
        //circleShape.setOutlineThickness(1);
        //window.draw(circleShape);

        for (int k = 0; k < 8; k++) {
            //printf("Points: ");
            Vector3 rotatedX = MatrixMultiply(rotationX, points[k]);
            Vector3 rotatedXY = MatrixMultiply(rotationY, rotatedX);
            Vector3 projecte2d = MatrixMultiply(projection, rotatedXY);
            projecte2d.x = MIDDLE_X + projecte2d.x;
            projecte2d.y = MIDDLE_Y + projecte2d.y;
            //printf("Projected coords[%d]: X:%f Y:%f\n", k, projecte2d.x, projecte2d.y);
            circle(projecte2d, 6);
        }

        // end the current frame
        texture.update(pixels);     // Send stuff to GPU
        sprite.setTexture(texture); // Create sprite from texture
        window.draw(sprite);        // Draw sprite

        window.display();           // Blit (copy from backbuffer?)

        angle += 0.005;
    }
    return 0;
}
