#include <string>
#include <SFML/Graphics.hpp>

#include "helper/demo_helper.hpp"

#define WINDOW_WIDTH 640u
#define WINDOW_HEIGHT 480u
#define MAX_FRAME_RATE 30.

#define CIRCLE_RADIUS 25.f
#define BOUNCE_BUFFER 50.f

namespace sfml_rgb_canvas::demo
{

    int run_demo()
    {
        auto window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Testing SFML");
        window.setFramerateLimit(MAX_FRAME_RATE);

        sf::CircleShape circle(CIRCLE_RADIUS);
        circle.setFillColor(sf::Color::Cyan);
        circle.setPosition(sf::Vector2f(160., 200.));
        // circle.setOrigin(circleCenter(circle));   // This doesn't work like you expect

        sf::ConvexShape triangle;
        triangle.setPointCount(3);
        triangle.setPoint(0, {0.f, 0.f});
        triangle.setPoint(1, {40.f, 5.f});
        triangle.setPoint(2, {10.f, 50.f});
        triangle.setFillColor(sf::Color::Red);
        triangle.setOrigin(helper::centroid(triangle));

        sf::Font font("fonts/Carlito-Regular.ttf");

        sf::Text triangleText(font);
        triangleText.setCharacterSize(40);
        triangleText.setFillColor(sf::Color::White);

        sf::Text circleText(font);
        circleText.setCharacterSize(40);
        circleText.setFillColor(sf::Color::Yellow);
        circleText.setPosition(sf::Vector2f(0., 50.));

        char triangleTextStr[100] = "";
        char circleTextStr[100] = "";

        bool triangleXPosVel = true;
        bool triangleYPosVel = true;

        bool circleXPosVel = true;
        bool circleYPosVel = false;

        float triangleVel = 5.;
        float circleVel = 7.5;

        while (window.isOpen())
        {
            // HALT IF WINDOW CLOSE EVENT RECEIVED

            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                }
            }

            // TRIANGLE MOVEMENT

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
            {
                triangle.rotate(sf::degrees(5));
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left))
            {
                triangle.rotate(sf::degrees(-5));
            }

            if (triangleXPosVel)
            {
                if (triangleYPosVel)
                {
                    triangle.move(sf::Vector2f(triangleVel, triangleVel));
                }
                else
                {
                    triangle.move(sf::Vector2f(triangleVel, -1 * triangleVel));
                }
            }
            else
            {
                if (triangleYPosVel)
                {
                    triangle.move(sf::Vector2f(-1 * triangleVel, triangleVel));
                }
                else
                {
                    triangle.move(sf::Vector2f(-1 * triangleVel, -1 * triangleVel));
                }
            }

            if (helper::centroid(triangle).x > (WINDOW_WIDTH - (helper::effectiveSize(triangle) / 2) - BOUNCE_BUFFER))
            {
                triangleXPosVel = false;
            }

            if (helper::centroid(triangle).x < BOUNCE_BUFFER + (helper::effectiveSize(triangle) / 2))
            {
                triangleXPosVel = true;
            }

            if (helper::centroid(triangle).y > (WINDOW_HEIGHT - (helper::effectiveSize(triangle) / 2) - BOUNCE_BUFFER))
            {
                triangleYPosVel = false;
            }

            if (helper::centroid(triangle).y < BOUNCE_BUFFER + (helper::effectiveSize(triangle) / 2))
            {
                triangleYPosVel = true;
            }

            // CIRCLE MOVEMENT

            if (circleXPosVel)
            {
                if (circleYPosVel)
                {
                    circle.move(sf::Vector2f(circleVel, circleVel));
                }
                else
                {
                    circle.move(sf::Vector2f(circleVel, -1 * circleVel));
                }
            }
            else
            {
                if (circleYPosVel)
                {
                    circle.move(sf::Vector2f(-1 * circleVel, circleVel));
                }
                else
                {
                    circle.move(sf::Vector2f(-1 * circleVel, -1 * circleVel));
                }
            }

            if (circle.getPosition().x > (WINDOW_WIDTH - 2 * CIRCLE_RADIUS - BOUNCE_BUFFER))
            {
                circleXPosVel = false;
            }

            if (circle.getPosition().x < BOUNCE_BUFFER)
            {
                circleXPosVel = true;
            }

            if (circle.getPosition().y > (WINDOW_HEIGHT - 2 * CIRCLE_RADIUS - BOUNCE_BUFFER))
            {
                circleYPosVel = false;
            }

            if (circle.getPosition().y < BOUNCE_BUFFER)
            {
                circleYPosVel = true;
            }

            // TEXT UPDATES

            sprintf(circleTextStr, "Circle: (%.0f, %.0f)", helper::circleCenter(circle).x, helper::circleCenter(circle).y);
            sprintf(triangleTextStr, "Triangle: (%.0f, %.0f)", helper::centroid(triangle).x, helper::centroid(triangle).y);

            triangleText.setString(triangleTextStr);
            circleText.setString(circleTextStr);

            // WINDOW UPDATES

            window.clear();
            window.draw(triangle);
            window.draw(circle);
            window.draw(triangleText);
            window.draw(circleText);
            window.display();
        }

        return 0;
    }

} // namespace sfml_rgb_canvas::demo

// Actual entrypoint

int main()
{
    sfml_rgb_canvas::demo::run_demo();
}
