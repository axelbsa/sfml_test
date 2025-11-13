#include<stdio.h>
#include<math.h>
#include <sys/time.h>

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
Vector3 points[8];
Vector3 screenView;

float z = 1;
const float distance = 1.2f;
Matrix_3x3 projection = {0};

Matrix_3x3 rotationX = {0};
Matrix_3x3 rotationY = {0};
Matrix_3x3 rotationZ = {0};

void debugPrintVector(Vector3 point)
{
    fprintf(stderr, ".X=%f \t .Y=%f \t .Z=%f\n", point.x, point.y, point.z);
}


double get_time()
{
#ifndef WIN32
    struct timeval tv;
    gettimeofday(&tv, 0);
    return tv.tv_sec + tv.tv_usec * 1.0e-6;
#else
    return GetTickCount() / 1000.0;
#endif
}

int main()
{
    char c[100];
    //float angle = -0.2;
    float angle = 0.0f;

    int fps = 0;
    int fps_counter = 0;

    double current_time;
    double target_time;
    double previous_time = 0.0;
    double last_game_time = 0.0;

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

    points[0] = { -0.5, -0.5, -0.5};
    points[1] = {  0.5, -0.5, -0.5};
    points[2] = {  0.5,  0.5, -0.5};
    points[3] = { -0.5,  0.5, -0.5};

    points[4] = { -0.5, -0.5, 0.5};
    points[5] = {  0.5, -0.5, 0.5};
    points[6] = {  0.5,  0.5, 0.5};
    points[7] = { -0.5,  0.5, 0.5};

    int radius = 250;

    double start_time = get_time();

    for (int i = 0; i < 8; i++ )
    {
        debugPrintVector(points[i]);
    }

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

        current_time = get_time();
        target_time = current_time - start_time;

        //rotationX.m0 = 1;  rotationX.m3 = 0;           rotationX.m6 = 0;
        //rotationX.m1 = 0;  rotationX.m4 =  cos(angle); rotationX.m7 = -sin(angle);
        //rotationX.m2 = 0;  rotationX.m5 =  sin(angle); rotationX.m8 = cos(angle);

        rotationX.m0 = 1;  rotationX.m3 = 0;           rotationX.m6 = 0;
        rotationX.m1 = 0;  rotationX.m4 = 1;           rotationX.m7 = 0;
        rotationX.m2 = 0;  rotationX.m5 = 0;           rotationX.m8 = 1;

        //rotationY.m0 = cos(angle);  rotationY.m3 = 0; rotationY.m6 = sin(angle);
        //rotationY.m1 = 0;           rotationY.m4 = 1; rotationY.m7 = 0;
        //rotationY.m2 = -sin(angle); rotationY.m5 = 0; rotationY.m8 = cos(angle);

        rotationY.m0 = 1; rotationY.m3 = 0; rotationY.m6 = 0;
        rotationY.m1 = 0; rotationY.m4 = 1; rotationY.m7 = 0;
        rotationY.m2 = 0; rotationY.m5 = 0; rotationY.m8 = 1;

        rotationZ.m0 = cos(angle);  rotationZ.m2 = -sin(angle); rotationZ.m3 = 0;
        rotationZ.m1 = sin(angle);  rotationZ.m3 =  cos(angle); rotationZ.m5 = 0;
        rotationZ.m2 = 0;           rotationZ.m5 =  0;          rotationZ.m8 = 1;

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

        Vector3 projected[8] = { 0 };
        for (int k = 0; k < 8; k++) {
            //printf("Points: ");
            Vector3 rotated = MatrixMultiply(rotationX, points[k]);
            rotated = MatrixMultiply(rotationY, rotated);
            
            // Update projection matrix with Z values
            z = 1 / (distance - rotated.z);
            projection.m0 = z;
            projection.m4 = z; 
            projection.m8 = z;

            Vector3 projecte2d = MatrixMultiply(projection, rotated);
            printf("Projected coords[%d]: X:%f Y:%f\n", k, projecte2d.x, projecte2d.y);
            //projecte2d = Vector3Scale(projecte2d, sin(2.14) * 300) ;
            printf("\tScale coords[%d]: X:%f Y:%f\n", k, projecte2d.x, projecte2d.y);
            projecte2d = Vector3Add(projecte2d, screenView);
            printf("\tScreen view coords[%d]: X:%f Y:%f\n", k, projecte2d.x, projecte2d.y);
            projected[k] = projecte2d;

        }
        printf("\n");

        for (int i = 0; i < 8; i++) 
        {
            circle(projected[i], 6);
        }

        for (int i = 0; i < 4; i++) 
        {
            connect(i + 0, ((i+1) % 4) + 0, projected);
            connect(i + 4, ((i+1) % 4) + 4, projected);
            connect(i + 0, i + 4,           projected);
        }

        // end the current frame
        texture.update(pixels);     // Send stuff to GPU
        sprite.setTexture(texture); // Create sprite from texture
        window.draw(sprite);        // Draw sprite
        window.display();           // Blit (copy from backbuffer?)
        angle += 0.005;

        last_game_time = target_time;
        if ( (target_time - previous_time) >= 1.0)
        {
            fps = fps_counter;
            fps_counter = 0;
            previous_time = target_time;
            fprintf(stderr, "fps:\t%d\n", fps);
        }

        fps_counter += 1;

    }

    return 0;
}


void connect(int i, int j, Vector3 *points)
{
    Vector3 a = points[i];
    Vector3 b = points[j];
    line(a, b);
}
