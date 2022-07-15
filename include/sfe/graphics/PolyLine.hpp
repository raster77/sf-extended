#ifndef SFE_GRAPHICS_POLYLINE_HPP_
#define SFE_GRAPHICS_POLYLINE_HPP_

#include "../helper/LineHelper.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <array>
#include <vector>

namespace sfe {

  class PolyLine : public sf::Drawable {

    public:

      PolyLine()
        : mPosition({0, 0})
        , mStartPoint({0, 0})
        , mColor(sf::Color::White)
        , mRotation(sf::Angle::Zero)
        , mScale(1.f)
        , mTickness (2.f) {}

      PolyLine(const std::size_t linesCount)
        : mPosition({0, 0})
        , mStartPoint({0, 0})
        , mColor(sf::Color::White)
        , mRotation(sf::Angle::Zero)
        , mScale(1.f)
        , mTickness (2.f) {
        mPoints.reserve((linesCount + 1) * 4 );
      }

      ~PolyLine() {}

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

      void addPoint(const sf::Vector2f& point, const bool build = false) {
        mPoints.emplace_back(point);

        if(build) {
          update();
        }
      }

      void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override {
        target.draw(mVertices.data(), mVertices.size(), sf::TriangleStrip, states);
      }

    private:
      sf::Vector2f mPosition;
      sf::Vector2f mStartPoint;
      sf::Color mColor;
      sf::Angle mRotation;
      float mScale;
      float mTickness;
      std::vector<sf::Vertex> mVertices;
      std::vector<sf::Vector2f> mPoints;

      void update() {
        mVertices.clear();
        mVertices.reserve((mPoints.size() * 4));

        sf::Vector2f startPoint = mStartPoint;

        for(auto& p : mPoints) {
          addLineToVertices(startPoint, p);
          startPoint = p;
        }

      }

      void addLineToVertices(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint) {

        sf::Transform t;
        t.translate(mPosition);
        t.rotate(mRotation);
        t.scale(sf::Vector2f(mScale, mScale));

        std::array<sf::Vertex, 4> buffer = sfe::computeLine(startPoint, endPoint, mTickness, mColor);

        for(auto& v : buffer) {
          v.position = t.transformPoint(v.position);
        }

        mVertices.insert(mVertices.end(), buffer.begin(), buffer.end());
      }
  };

}

#endif /* SFE_GRAPHICS_POLYLINE_HPP_ */
