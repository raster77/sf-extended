#ifndef SFE_GRAPHICS_BEZIERCURVE_HPP_
#define SFE_GRAPHICS_BEZIERCURVE_HPP_

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

namespace sfe {

  class BezierCurve : public sf::Drawable {

    public:

      BezierCurve()
        : mColor(sf::Color::White)
        , mTickness (2.f)
        , mPointsCount(0)
      {}

      virtual ~BezierCurve() {}

      const float getTickness() {
        return mTickness;
      }

      void setTickness(const float tickness) {
        mTickness = tickness;
        update();
      }

      const std::size_t getPointsCount() {
        return mPointsCount;
      }

      void setPointsCount(const std::size_t pointsCount) {
        mPointsCount = pointsCount;
        update();
      }

      const sf::Color& getColor() {
        return mColor;
      }

      void setColor(const sf::Color& color) {
        mColor = color;
      }

      void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override {
        target.draw(mVertices.data(), mVertices.size(), sf::TriangleStrip, states);
      }

    protected:
      sf::Color mColor;
      float mTickness;
      std::size_t mPointsCount;
      std::vector<sf::Vector2f> mPoints;
      std::vector<sf::Vertex> mVertices;

      sf::Vector2f getPoint(const sf::Vector2f& point1, const sf::Vector2f& point2, const float q) {
        sf::Vector2f diff = point2 - point1;
        return point1 + (diff * q);
      }

      virtual void update() = 0;

  };

}

#endif /* SFE_GRAPHICS_BEZIERCURVE_HPP_ */
