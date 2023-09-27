#include <stdio.h>
#include <math.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>

#include "graphics.hpp"

#define MIDDLE_X WIDTH/2
#define MIDDLE_Y HEIGTH/2

void connect(int i, int j, Vector3* points);

sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Test");
sf::Texture      texture;
sf::Sprite       sprite;

sf::Time thetime;
sf::Clock sf_clock;
sf::Text text;
sf::Font font;

Vector2 foo;
Vector3 points[20];
Vector3 screenView;

float z = 1;
const float distance = 3.3f;
Matrix_3x3 projection = {0};

Matrix_3x3 rotationX = {0};
Matrix_3x3 rotationY = {0};
Matrix_3x3 rotationZ = {0};


int main()
{
    char c[100];
    float angle = -0.2;

    screenView.x = MIDDLE_X;
    screenView.y = MIDDLE_Y;

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

    //Vector2 line1_p1 = {WIDTH/2, HEIGTH/2};
    //Vector2 line1_p2 = {300, 100};

    //Vector2 line2_p1 = {WIDTH/2, HEIGTH/2};
    //Vector2 line2_p2 = {600, (HEIGTH/2) + 120};

    Vector2 circleCenter = {400, 300};

    points[0] = { -1.0, -1.0, -1.0};
    points[1] = {  1.0, -1.0, -1.0};
    points[2] = {  1.0,  1.0, -1.0};
    points[3] = { -1.0,  1.0, -1.0};

    points[4] = { -1.0, -1.0, 1.0};
    points[5] = {  1.0, -1.0, 1.0};
    points[6] = {  1.0,  1.0, 1.0};
    points[7] = { -1.0,  1.0, 1.0};

    points[8] ={0, 1.618033988749895, 0.6180339887498948};
    points[9] ={0, 1.618033988749895, -0.6180339887498948};
    points[10] ={0, -1.618033988749895, 0.6180339887498948};
    points[11] ={0, -1.618033988749895, -0.6180339887498948};
    points[12] ={0.6180339887498948, 0, 1.618033988749895};
    points[13] ={0.6180339887498948, 0, -1.618033988749895};
    points[14] ={-0.6180339887498948, 0, 1.618033988749895};
    points[15] ={-0.6180339887498948, 0, -1.618033988749895};
    points[16] ={1.618033988749895, 0.6180339887498948, 0};
    points[17] ={1.618033988749895, -0.6180339887498948, 0};
    points[18] ={-1.618033988749895, 0.6180339887498948, 0};
    points[19] ={-1.618033988749895, -0.6180339887498948, 0};

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

        // clear the window with black color
        //window.clear(sf::Color::Black);
        clearcolor();

        //line(line1_p1, line1_p2);
        //line(line2_p1, line2_p2);
        circle(circleCenter, radius);

        sprintf(c, "Hei verden: %f", angle);

        Vector3 projected[20] = { 0 };
        for (int k = 0; k < 20; k++) {
            //printf("Points: ");
            Vector3 rotated = MatrixMultiply(rotationX, points[k]);
            rotated = MatrixMultiply(rotationY, rotated);

            // Update projection matrix with Z values
            z = 1 / (distance - rotated.z);
            projection.m0 = z;
            projection.m4 = z;
            projection.m8 = z;

            Vector3 projecte2d = MatrixMultiply(projection, rotated);
            projecte2d = Vector3Scale(projecte2d, sin(angle) * 300) ;
            projecte2d = Vector3Add(projecte2d, screenView);
            projected[k] = projecte2d;

            //printf("Projected coords[%d]: X:%f Y:%f\n", k, projecte2d.x, projecte2d.y);
        }

        for (int i = 0; i < 20; i++)
        {
            circle(projected[i], 3);
        }

        for (int i = 0; i < 4; i++)
        {
            connect(i + 0, ((i+1) % 4) + 0, projected);
            connect(i + 4, ((i+1) % 4) + 4, projected);
            connect(i + 0, i + 4,           projected);
        }

        connect(8, 9,             projected);
        connect(8, 6,             projected);
        connect(9, 5,             projected);


        connect(10, 11,           projected);

        connect(12, 14,           projected);
        connect(13, 15,           projected);

        connect(16, 17,           projected);
        connect(18, 19,           projected);

        // end the current frame
        texture.update(pixels);     // Send stuff to GPU
        sprite.setTexture(texture); // Create sprite from texture
        window.draw(sprite);        // Draw sprite

        text.setFont(font);
        text.setString(std::string(c));
        text.setFillColor(sf::Color(2,125,240));
        text.setPosition(10, 10);
        window.draw(text);

        window.display();           // Blit (copy from backbuffer?)
        if (angle > 50)
        {
            angle=-1.0f;
        }
        angle += 0.005;

    }
    return 0;
}


void connect(int i, int j, Vector3 *points)
{
    Vector3 a = points[i];
    Vector3 b = points[j];
    line(a, b);
}
