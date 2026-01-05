#include <SFML/Graphics.hpp>

namespace sfml_rgb_canvas::demo::helper
{

    sf::Vector2f centroid(sf::ConvexShape shp);
    sf::Vector2f circleCenter(sf::CircleShape circ);
    float effectiveSize(sf::ConvexShape shp);

} // namespace sfml_rgb_canvas::demo::helper
