#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 640u
#define WINDOW_HEIGHT 480u

#define CIRCLE_RADIUS 25.f
#define BOUNCE_BUFFER 50.f

sf::Vector2f centroid(sf::ConvexShape shp);
float effectiveSize(sf::ConvexShape shp);

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Testing SFML");
    window.setFramerateLimit(30);

    sf::ConvexShape shape;
    shape.setPointCount(3);
    shape.setPoint(0, {0.f, 0.f});
    shape.setPoint(1, {40.f, 5.f});
    shape.setPoint(2, {10.f, 50.f});
    shape.setFillColor(sf::Color::Red);

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

        shape.rotate(sf::degrees(5));

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

        if (centroid(shape).x > (WINDOW_WIDTH - 2 * effectiveSize(shape) - BOUNCE_BUFFER))
        {
            xPosVel = false;
        }

        if (centroid(shape).x < BOUNCE_BUFFER)
        {
            xPosVel = true;
        }

        if (centroid(shape).y > (WINDOW_HEIGHT - 2 * effectiveSize(shape) - BOUNCE_BUFFER))
        {
            yPosVel = false;
        }

        if (centroid(shape).y < BOUNCE_BUFFER)
        {
            yPosVel = true;
        }

        // textStr = std::format(textStr, "(%f, %f)", centroid(shape).x, centroid(shape).y);
        sprintf(textStr, "(%.0f, %.0f)", centroid(shape).x, centroid(shape).y);

        text.setString(textStr);

        window.clear();
        window.draw(shape);
        window.draw(text);
        window.display();
    }
}

sf::Vector2f centroid(sf::ConvexShape shp)
{
    float xSum = 0;
    float ySum = 0;

    sf::Vector2f pt;
    int numPts = shp.getPointCount();

    for (int i = 0; i < numPts; i++)
    {
        pt = shp.getPoint(i);

        xSum += pt.x;
        ySum += pt.y;
    }

    return shp.getPosition() + sf::Vector2f(xSum / numPts, ySum / numPts);
}

float effectiveSize(sf::ConvexShape shp)
{
    sf::Vector2f boundRectSize = shp.getLocalBounds().size;

    return std::max(boundRectSize.x, boundRectSize.y);
}
