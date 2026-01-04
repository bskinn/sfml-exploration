#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 640u
#define WINDOW_HEIGHT 480u

#define CIRCLE_RADIUS 25.f
#define BOUNCE_BUFFER 50.f

sf::Vector2f centroid(sf::ConvexShape shp);
sf::Vector2f circleCenter(sf::CircleShape circ);
float effectiveSize(sf::ConvexShape shp);
std::vector<std::uint8_t> unpackPixels(std::vector<std::vector<std::uint32_t>> pxArr);

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Testing SFML");
    window.setFramerateLimit(30);

    sf::CircleShape circle(CIRCLE_RADIUS);
    circle.setFillColor(sf::Color::Cyan);
    circle.setPosition(sf::Vector2f(160., 200.));
    // circle.setOrigin(circleCenter(circle));   // This doesn't work like you'd expect

    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, {0.f, 0.f});
    triangle.setPoint(1, {40.f, 5.f});
    triangle.setPoint(2, {10.f, 50.f});
    triangle.setFillColor(sf::Color::Red);
    triangle.setOrigin(centroid(triangle));

    sf::Texture texture(sf::Vector2u(100, 50));
    // std::vector<>

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

        triangle.rotate(sf::degrees(5));

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

        if (centroid(triangle).x > (WINDOW_WIDTH - (effectiveSize(triangle) / 2) - BOUNCE_BUFFER))
        {
            triangleXPosVel = false;
        }

        if (centroid(triangle).x < BOUNCE_BUFFER + (effectiveSize(triangle) / 2))
        {
            triangleXPosVel = true;
        }

        if (centroid(triangle).y > (WINDOW_HEIGHT - (effectiveSize(triangle) / 2) - BOUNCE_BUFFER))
        {
            triangleYPosVel = false;
        }

        if (centroid(triangle).y < BOUNCE_BUFFER + (effectiveSize(triangle) / 2))
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

        sprintf(circleTextStr, "Circle: (%.0f, %.0f)", circleCenter(circle).x, circleCenter(circle).y);
        sprintf(triangleTextStr, "Triangle: (%.0f, %.0f)", centroid(triangle).x, centroid(triangle).y);

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
}

sf::Vector2f circleCenter(sf::CircleShape circ)
{
    return circ.getPosition() + sf::Vector2f(circ.getRadius(), circ.getRadius());
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

std::vector<std::uint8_t> unpackPixels(std::vector<std::vector<std::uint32_t>> pxArr)
{
    std::vector<std::uint8_t> outVec = {};
    outVec.reserve(4 * pxArr.size() * pxArr[0].size()); // Assume rectangular

    std::vector<std::uint32_t> row;

    uint32_t val;

    for (int rowIdx = 0; rowIdx < pxArr.size(); rowIdx++)
    {
        row = pxArr[rowIdx];
        for (int colIdx = 0; colIdx < row.size(); colIdx++)
        {
            val = row[colIdx];

            outVec.push_back(uint8_t(val / (256 * 256 * 256)));   // Red
            outVec.push_back(uint8_t((val / (256 * 256)) % 256)); // Green
            outVec.push_back(uint8_t((val / 256) % 256));         // Blue
            outVec.push_back(uint8_t(val % 256));                 // Alpha
        }
    }
}
