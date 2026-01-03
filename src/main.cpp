#include <string>
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 640u
#define WINDOW_HEIGHT 480u

#define CIRCLE_RADIUS 25.f
#define BOUNCE_BUFFER 50.f

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Testing SFML");
    window.setFramerateLimit(30);

    sf::CircleShape shape(CIRCLE_RADIUS);
    shape.setFillColor(sf::Color::Cyan);

    sf::Font font("fonts/Carlito-Regular.ttf");
    sf::Text text(font);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);

    // std::string textStr = "";
    char textStr[100] = "";

    bool xPosVel = true;
    bool yPosVel = true;

    float vel = 5.;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        if (xPosVel)
        {
            if (yPosVel)
            {
                shape.move(sf::Vector2f(vel, vel));
            }
            else
            {
                shape.move(sf::Vector2f(vel, -1 * vel));
            }
        }
        else
        {
            if (yPosVel)
            {
                shape.move(sf::Vector2f(-1 * vel, vel));
            }
            else
            {
                shape.move(sf::Vector2f(-1 * vel, -1 * vel));
            }
        }

        if (shape.getPosition().x > (WINDOW_WIDTH - 2 * CIRCLE_RADIUS - BOUNCE_BUFFER))
        {
            xPosVel = false;
        }

        if (shape.getPosition().x < BOUNCE_BUFFER)
        {
            xPosVel = true;
        }

        if (shape.getPosition().y > (WINDOW_HEIGHT - 2 * CIRCLE_RADIUS - BOUNCE_BUFFER))
        {
            yPosVel = false;
        }

        if (shape.getPosition().y < BOUNCE_BUFFER)
        {
            yPosVel = true;
        }

        // textStr = std::format(textStr, "(%f, %f)", shape.getPosition().x, shape.getPosition().y);
        sprintf(textStr, "(%.0f, %.0f)", shape.getPosition().x, shape.getPosition().y);

        text.setString(textStr);

        window.clear();
        window.draw(shape);
        window.draw(text);
        window.display();
    }
}
