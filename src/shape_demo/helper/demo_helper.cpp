#include <SFML/Graphics.hpp>

#include "demo_helper.hpp"

namespace sfml_rgb_canvas::demo::shape::helper
{

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

} // namespace sfml_rgb_canvas::demo::shape::helper
