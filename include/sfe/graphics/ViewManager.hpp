#ifndef SFE_GRAPHICS_VIEWMANAGER_HPP_
#define SFE_GRAPHICS_VIEWMANAGER_HPP_

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>
#include <limits>

namespace sfe {

  class ViewManager {

    public:

      enum class MoveMode { DragDrop, PointClick };

      ViewManager()
        : mZoomFactor(1.f)
        , mAngle(0.f)
        , mZoomOnMousePos(false)
        , mDestination( { 0.f, 0.f })
        , mVelocity(0.f)
        , mSpeed(10.f)
        , mDragStart({0.f, 0.f})
        , mDrag(false)
        , mMoveMode(MoveMode::DragDrop)
        , mWindowPtr(nullptr){
      }

      ViewManager(const sf::Vector2f& center, const sf::Vector2f& size, sf::RenderWindow* windowPtr)
        : mView(center, size)
        , mCenter(center)
        , mSize(size)
        , mZoomFactor(1.f)
        , mAngle(0.f)
        , mZoomOnMousePos(false)
        , mDestination( { 0.f, 0.f })
        , mVelocity(0.f)
        , mSpeed(10.f)
        , mDragStart({0.f, 0.f})
        , mDrag(false)
        , mMoveMode(MoveMode::DragDrop)
        , mWindowPtr(windowPtr) {
      }

      ~ViewManager() {
      }

      void setWindow(sf::RenderWindow* renderWindowPtr) {
        mWindowPtr = renderWindowPtr;
      }

      const float getSpeed() const {
        return mSpeed;
      }

      void setSpeed(const float speed) {
        mSpeed = speed;
      }

      void move(const sf::Vector2f& offset) {
        if (mVelocity == 0.f) {
          mView.move(offset);
        }
      }

      const sf::Vector2f& getCenter() {
        return mView.getCenter();
      }

      void setCenter(const sf::Vector2f& center) {
        mView.setCenter(center);
      }

      const sf::Vector2f& getSize() {
        return mView.getSize();
      }

      void setSize(const sf::Vector2f& size) {
        mView.setSize(size);
      }

      const bool isZoomingOnMousePosition() {
        return mZoomOnMousePos;
      }

      void zoomingOnMousePosition(const bool b) {
        mZoomOnMousePos = b;
      }

      void zoom(const float zoom) {
        mZoomFactor = 1.f + zoom * 0.1f;
        mView.zoom(mZoomFactor);
        if(mZoomOnMousePos) {
          moveTo(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*mWindowPtr)));
        }
      }

      void reset() {
        mAngle = 0.f;
        mZoomFactor = 1.f;
        mView.setCenter(mCenter);
        mView.setSize(mSize);
        mView.zoom(1.f);
        mView.setRotation(sf::degrees(mAngle));
      }

      const sf::View& getView() {
        return mView;
      }

      void moveTo(const sf::Vector2f& destination) {
        if(mMoveMode == MoveMode::PointClick) {
          mDestination = mView.getCenter() + (destination - (static_cast<sf::Vector2f>(mWindowPtr->getSize()) * 0.5f));
          mVelocity = mSpeed;
        }
      }

      void update(const float dt) {
        if(mWindowPtr->hasFocus()) {
          if(mMoveMode == MoveMode::DragDrop) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !mDrag) {
              mDrag = true;
              mDragStart = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*mWindowPtr));
            }
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mDrag) {
              mDrag = false;
              mDestination = mView.getCenter() + static_cast<sf::Vector2f>(sf::Mouse::getPosition(*mWindowPtr)) - mDragStart;
              mVelocity = mSpeed;
            }
          }

          if (mVelocity > 0.f) {
            float d = distance(mView.getCenter(), mDestination);
            if (d < std::numeric_limits<float>::epsilon()) {
              mVelocity = 0.f;
              mView.setCenter(mDestination);
            }
            else {
              sf::Vector2f diff = mDestination - mView.getCenter();
              diff *= mVelocity * dt;
              mView.move(diff);
            }
          }
        }
      }

    private:
      sf::View mView;
      sf::Vector2f mCenter;
      sf::Vector2f mSize;
      float mZoomFactor;
      float mAngle;
      bool mZoomOnMousePos;
      sf::Vector2f mDestination;
      float mVelocity;
      float mSpeed;
      sf::Vector2f mDragStart;
      bool mDrag;
      MoveMode mMoveMode;
      sf::RenderWindow* mWindowPtr;

      void update() {
        mView.zoom(1.f / mZoomFactor);
        mView.setRotation(sf::degrees(mAngle));
      }

      float distance(const sf::Vector2f& v1, const sf::Vector2f& v2) {
        sf::Vector2f diff = v2 - v1;
        return diff.x * diff.x + diff.y * diff.y;
      }
  };

}

#endif /* SFE_GRAPHICS_VIEWMANAGER_HPP_ */
