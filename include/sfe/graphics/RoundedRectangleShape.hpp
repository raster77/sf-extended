#ifndef SFE_GRAPHICS_ROUNDEDRECTANGLESHAPE_HPP_
#define SFE_GRAPHICS_ROUNDEDRECTANGLESHAPE_HPP_

#include <SFML/Graphics/Shape.hpp>

namespace sfe {

  class RoundedRectangleShape : public sf::Shape {

    public:
      explicit RoundedRectangleShape(const sf::Vector2f& size = sf::Vector2f(0, 0), const float radius = 0, const std::size_t cornerPointCount = 4)
        : mSize(size)
        , mRadius(radius)
        , mCornerPointCount(cornerPointCount) {
        update();
      }

      void setSize(const sf::Vector2f& size) {
        mSize = size;
        update();
      }

      const sf::Vector2f& getSize() const {
        return mSize;
      }

      void setCornersRadius(float radius) {
        mRadius = radius;
        update();
      }

      float getCornersRadius() const {
        return mRadius;
      }

      void setCornerPointCount(unsigned int count) {
        mCornerPointCount = count;
        update();
      }

      std::size_t getPointCount() const {
        return mCornerPointCount * 4;
      }

      sf::Vector2f getPoint(std::size_t index) const {
        if (index >= mCornerPointCount * 4)
          return sf::Vector2f(0, 0);

        float deltaAngle = 90.0f / (mCornerPointCount - 1);
        sf::Vector2f center;
        unsigned int centerIndex = index / mCornerPointCount;
        static const float pi = 3.141592654f;

        switch (centerIndex) {
          case 0:
            center.x = mSize.x - mRadius;
            center.y = mRadius;
            break;
          case 1:
            center.x = mRadius;
            center.y = mRadius;
            break;
          case 2:
            center.x = mRadius;
            center.y = mSize.y - mRadius;
            break;
          case 3:
            center.x = mSize.x - mRadius;
            center.y = mSize.y - mRadius;
            break;
        }

        return sf::Vector2f(
            mRadius * std::cos(deltaAngle * (index - centerIndex) * pi / 180) + center.x,
            -mRadius * std::sin(deltaAngle * (index - centerIndex) * pi / 180) + center.y);
      }

    private:
      sf::Vector2f mSize;
      float mRadius;
      std::size_t mCornerPointCount;

  };

}

#endif /* SFE_GRAPHICS_ROUNDEDRECTANGLESHAPE_HPP_ */
