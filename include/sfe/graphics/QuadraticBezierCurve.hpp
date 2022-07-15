#ifndef SFE_GRAPHICS_QUADRATICBEZIERCURVE_HPP_
#define SFE_GRAPHICS_QUADRATICBEZIERCURVE_HPP_

#include "BezierCurve.hpp"
#include "../helper/LineHelper.hpp"

namespace sfe {

  class QuadraticBezierCurve : public BezierCurve {

    public:

      QuadraticBezierCurve()
        : BezierCurve() {
      }

      QuadraticBezierCurve(const sf::Vector2f& point0, const sf::Vector2f& point1, const sf::Vector2f& point2, const std::size_t pointsCount)
        : BezierCurve()
        , mPoint0(point0)
        , mPoint1(point1)
        , mPoint2(point2) {
        mPointsCount = pointsCount;
      }

      ~QuadraticBezierCurve() {}

      const sf::Vector2f& getPoint0() {
        return mPoint0;
      }

      void setPoint0(const sf::Vector2f& point) {
        mPoint0 = point;
        update();
      }

      const sf::Vector2f& getPoint1() {
        return mPoint1;
      }

      void setPoint1(const sf::Vector2f& point) {
        mPoint1 = point;
        update();
      }

      const sf::Vector2f& getPoint2() {
        return mPoint2;
      }

      void setPoint2(const sf::Vector2f& point) {
        mPoint2 = point;
        update();
      }

    protected:

      void update() override {

        if (mPointsCount > 0) {

          mVertices.clear();
          mPoints.clear();
          mPoints.reserve(mPointsCount + 1);
          mVertices.reserve((mPointsCount + 1) * 4);

          float p = 1.f / mPointsCount;
          const float q = p;

          mPoints.emplace_back(mPoint0);

          for (std::size_t i = 0; i < mPointsCount; i++) {
            sf::Vector2f pointA = getPoint(mPoint0, mPoint1, p);
            sf::Vector2f pointB = getPoint(mPoint1, mPoint2, p);
            mPoints.emplace_back(getPoint(pointA, pointB, p));
            if(i > 0) {
              addLineToVertices(mPoints[i-1], mPoints[i]);
            }
            p += q;
          }
          addLineToVertices(mPoints[mPoints.size() - 2], mPoints[mPoints.size() - 1]);
        }
      }

    private:
      sf::Vector2f mPoint0;
      sf::Vector2f mPoint1;
      sf::Vector2f mPoint2;

      void addLineToVertices(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint) {
        std::array<sf::Vertex, 4> buffer = sfe::computeLine(startPoint, endPoint, mTickness, mColor);
        mVertices.insert(mVertices.end(), buffer.begin(), buffer.end());
      }

  };

}

#endif /* SFE_GRAPHICS_QUADRATICBEZIERCURVE_HPP_ */
