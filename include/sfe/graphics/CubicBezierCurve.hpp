#ifndef SFE_GRAPHICS_CUBICBEZIERCURVE_HPP_
#define SFE_GRAPHICS_CUBICBEZIERCURVE_HPP_

#include "BezierCurve.hpp"
#include "../helper/LineHelper.hpp"

namespace sfe {

  class CubicBezierCurve : public BezierCurve {

    public:

      CubicBezierCurve()
        : BezierCurve() {
      }

      CubicBezierCurve(const sf::Vector2f& point0, const sf::Vector2f& point1, const sf::Vector2f& point2, const sf::Vector2f& point3, const std::size_t pointsCount)
        : BezierCurve()
        , mPoint0(point0)
        , mPoint1(point1)
        , mPoint2(point2)
        , mPoint3(point3) {
        mPointsCount = pointsCount;
      }

      ~CubicBezierCurve() {}

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

      const sf::Vector2f& getPoint3() {
        return mPoint3;
      }

      void setPoint3(const sf::Vector2f& point) {
        mPoint3 = point;
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
            sf::Vector2f pointC = getPoint(mPoint2, mPoint3, p);

            sf::Vector2f pointD = getPoint(pointA, pointB, p);
            sf::Vector2f pointE = getPoint(pointB, pointC, p);

            mPoints.emplace_back(getPoint(pointD, pointE, p));
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
      sf::Vector2f mPoint3;

      void addLineToVertices(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint) {
        std::array<sf::Vertex, 4> buffer = sfe::computeLine(startPoint, endPoint, mTickness, mColor);
        mVertices.insert(mVertices.end(), buffer.begin(), buffer.end());
      }

  };

}


#endif /* SFE_GRAPHICS_CUBICBEZIERCURVE_HPP_ */
