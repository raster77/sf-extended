#ifndef SFE_GRAPHICS_LINE_HPP_
#define SFE_GRAPHICS_LINE_HPP_

#include "../helper/LineHelper.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <array>

namespace sfe {

  class Line : public sf::Drawable {

    public:

      Line()
        : mPosition({0, 0})
        , mStartPoint({0, 0})
        , mEndPoint({0, 0})
        , mColor(sf::Color::White)
        , mRotation(sf::Angle::Zero)
        , mScale(1.f)
        , mTickness (2.f) {
      }

      Line(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, const float tickness = 2.f)
        : mPosition({0, 0})
        , mStartPoint(startPoint)
        , mEndPoint(endPoint)
        , mColor(sf::Color::White)
        , mRotation(sf::Angle::Zero)
        , mScale(1.f)
        , mTickness(tickness) {
      }

      ~Line() {}

      const sf::Vector2f& getPosition() {
        return mPosition;
      }

      void setPosition(const sf::Vector2f& position) {
        mPosition = position;
        update();
      }

      const sf::Vector2f& getStartPoint() {
        return mStartPoint;
      }

      void setStartPoint(const sf::Vector2f& startPoint) {
        mStartPoint = startPoint;
        update();
      }

      const sf::Vector2f& getEndPoint() {
        return mEndPoint;
      }

      void setEndPoint(const sf::Vector2f& endPoint) {
        mEndPoint = endPoint;
        update();
      }

      const sf::Angle& getRotation() {
        return mRotation;
      }

      void setRotation(const sf::Angle& angle) {
        mRotation = angle;
        update();
      }

      const float getScale() {
        return mScale;
      }

      void setScale(const float scale) {
        mScale = scale;
        update();
      }

      const float getTickness() {
        return mTickness;
      }

      void setTickness(const float tickness) {
        mTickness = tickness;
        update();
      }

      void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override {
        target.draw(mVertices.data(), mVertices.size(), sf::TriangleStrip, states);
      }

    private:
      sf::Vector2f mPosition;
      sf::Vector2f mStartPoint;
      sf::Vector2f mEndPoint;
      sf::Color mColor;
      sf::Angle mRotation;
      float mScale;
      float mTickness;
      std::array<sf::Vertex, 4> mVertices;

      void update() {
        sf::Transform t;
        t.translate(mPosition);
        t.rotate(mRotation);
        t.scale(sf::Vector2f(mScale, mScale));

        mVertices = sfe::computeLine(mStartPoint, mEndPoint, mTickness, mColor);

        for(auto& v : mVertices) {
          v.position = t.transformPoint(v.position);
        }

      }
  };

}

#endif /* SFE_GRAPHICS_LINE_HPP_ */
