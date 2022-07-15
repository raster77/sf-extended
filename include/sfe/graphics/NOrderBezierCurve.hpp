#ifndef SFE_GRAPHICS_NORDERBEZIERCURVE_HPP_
#define SFE_GRAPHICS_NORDERBEZIERCURVE_HPP_

#include "BezierCurve.hpp"
#include "../helper/LineHelper.hpp"

namespace sfe {

  class NOrderBezierCurve : public BezierCurve {

    public:

      NOrderBezierCurve ()
        : BezierCurve() {
      }

      NOrderBezierCurve (const std::size_t pointsCount)
        : BezierCurve() {
        mPointsCount = pointsCount;
      }

      ~NOrderBezierCurve () {}

      void addControlPoint(const sf::Vector2f& controlPoint) {
        mControlPoints.emplace_back(controlPoint);
      }

      void setControlPoint(const std::size_t index, const sf::Vector2f& controlPoint) {
        if(index < mControlPoints.size()) {
          mControlPoints[index] = controlPoint;
          update();
        }
      }

      const sf::Vector2f& getControlPoint(const std::size_t index) {
        return mControlPoints[index];
      }

      void clearControlPoints() {
        mControlPoints.clear();
        mVertices.clear();
      }

      void resize(const std::size_t size) {
        mControlPoints.clear();
        mControlPoints.resize(size);
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

          mPoints.emplace_back(mControlPoints.front());

          for (std::size_t i = 0; i < mPointsCount; i++) {

            std::pair<sf::Vector2f, sf::Vector2f> points = reducePoints(p);
            mPoints.emplace_back(getPoint(points.first, points.second, p));

            if(i > 0) {
              addLineToVertices(mPoints[i-1], mPoints[i]);
            }

            p += q;
          }
          addLineToVertices(mPoints[mPoints.size() - 2], mPoints[mPoints.size() - 1]);
        }
      }

    private:
      std::vector<sf::Vector2f> mControlPoints;

      std::pair<sf::Vector2f, sf::Vector2f> reducePoints(const float p) {
        std::vector<sf::Vector2f> buffer;
        std::vector<sf::Vector2f> tempBuf;

        buffer = mControlPoints;

        while(buffer.size() != 2) {
          for(std::size_t i = 1; i < buffer.size(); ++i) {
            tempBuf.emplace_back(getPoint(buffer[i - 1], buffer[i], p));
          }
          buffer = tempBuf;
          if(buffer.size() == 2) {
            break;
          }
          tempBuf.clear();
          tempBuf.reserve(buffer.size() - 1);
        }

        return std::make_pair(buffer[0], buffer[1]);

      }

      void addLineToVertices(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint) {
        std::array<sf::Vertex, 4> buffer = sfe::computeLine(startPoint, endPoint, mTickness, mColor);
        mVertices.insert(mVertices.end(), buffer.begin(), buffer.end());
      }

  };

}

#endif /* SFE_GRAPHICS_NORDERBEZIERCURVE_HPP_ */
