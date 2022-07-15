#ifndef SFE_HELPER_LINEHELPER_HPP_
#define SFE_HELPER_LINEHELPER_HPP_

#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <array>

namespace sfe {

  inline std::array<sf::Vertex, 4> computeLineStrip(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, const float tickness, const sf::Color& color) {
    const sf::Vector2f direction = endPoint - startPoint;
    const sf::Vector2f unitDirection = direction / direction.length();
    const sf::Vector2f unitPerpendicular(-unitDirection.y,unitDirection.x);

    const sf::Vector2f offset = tickness * 0.5f * unitPerpendicular;

    std::array<sf::Vertex, 4> buffer;

    buffer[0].position = startPoint + offset;
    buffer[0].color = color;
    buffer[1].position = startPoint - offset;
    buffer[1].color = color;
    buffer[2].position = endPoint + offset;
    buffer[2].color = color;
    buffer[3].position = endPoint - offset;
    buffer[3].color = color;

    return buffer;
  }

  inline std::array<sf::Vertex, 6> computeLine(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, const float tickness, const sf::Color& color) {
    const sf::Vector2f direction = endPoint - startPoint;
    const sf::Vector2f unitDirection = direction / direction.length();
    const sf::Vector2f unitPerpendicular(-unitDirection.y,unitDirection.x);

    const sf::Vector2f offset = tickness * 0.5f * unitPerpendicular;

    std::array<sf::Vertex, 6> buffer;

    buffer[0].position = startPoint - offset;
    buffer[0].color = color;
    buffer[1].position = startPoint + offset;
    buffer[1].color = color;
    buffer[2].position = endPoint + offset;
    buffer[2].color = color;
    buffer[3].position = endPoint + offset;
    buffer[3].color = color;
    buffer[4].position = endPoint - offset;
    buffer[4].color = color;
    buffer[5].position = startPoint - offset;
    buffer[5].color = color;
    return buffer;
  }

}

#endif /* SFE_HELPER_LINEHELPER_HPP_ */
