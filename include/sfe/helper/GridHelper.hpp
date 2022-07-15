#ifndef SFE_HELPER_GRIDHELPER_HPP_
#define SFE_HELPER_GRIDHELPER_HPP_

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <vector>

namespace sfe {

  inline std::vector<sf::Vertex> gridHelper(const std::size_t cellSize, const sf::Vector2u& screenSize, const sf::Color& color) {
    std::vector<sf::Vertex> gridVertices;
    std::size_t startX = 0;
    std::size_t startY = 0;

    while(startX <= screenSize.x || startY <= screenSize.y) {
      if(startX <= screenSize.x) {
        gridVertices.emplace_back(sf::Vertex(sf::Vector2f(startX, 0), color));
        gridVertices.emplace_back(sf::Vertex(sf::Vector2f(startX, screenSize.y), color));
        startX += cellSize;
      }

      if(startY <= screenSize.y) {
        gridVertices.emplace_back(sf::Vertex(sf::Vector2f(0, startY), color));
        gridVertices.emplace_back(sf::Vertex(sf::Vector2f(screenSize.x, startY), color));
        startY += cellSize;
      }
    }

    return gridVertices;
  }

}



#endif /* SFE_HELPER_GRIDHELPER_HPP_ */
