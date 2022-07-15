#ifndef SFAPP_SYSTEM_VECTORMATH_HPP_
#define SFAPP_SYSTEM_VECTORMATH_HPP_

#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace sfe {

  template<typename T>
    inline T dotProduct(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2) {
      return v1.x * v2.x + v1.y * v2.y;
    }

  template<typename T>
    inline T length(const sf::Vector2<T>& v) {
      T val = dotProduct(v, v);
      return std::sqrt(val);
    }

  template<typename T>
    inline T squaredLength(const sf::Vector2<T>& v) {
      return dotProduct(v, v);
    }

  template<typename T>
    inline void rotate(sf::Vector2<T>& v, const T angle) {
      const T h = std::atan2(v.y, v.x) + angle;
      const float l = length(v);
      T cos = std::cos(h) * l;
      T sin = std::sin(h) * l;
      v = sf::Vector2<T>(cos, sin);
    }

  template<typename T>
    inline sf::Vector2<T> normalize(const sf::Vector2<T>& v) {
      const float len = length(v);
      sf::Vector2<T> res(v);
      if(len != 0) {
        res *= (1 / len);
      }
      return res;
    }

  template<typename T>
    inline void setLength(sf::Vector2<T>& v, T newLength) {
        v = normalize(v) * newLength;
    }

  template<typename T>
    inline T angle(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2) {
      return std::atan2(crossProduct(v1, v2), dotProduct(v1, v2));
    }

  template<typename T>
    inline sf::Vector2<T> perpendicular(const sf::Vector2<T>& v) {
      return sf::Vector2<T>(-v.y, v.x);
    }

}

#endif /* SFAPP_SYSTEM_VECTORMATH_HPP_ */
