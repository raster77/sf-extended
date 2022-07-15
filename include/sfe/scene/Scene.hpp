#ifndef SFE_SCENE_SCENE_HPP_
#define SFE_SCENE_SCENE_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <memory>
#include <string>

namespace sfe {

  class Scene {
    public:

      Scene()
        : mTitle("")
        , mMousePos({0.f, 0.f})
        , mWindow(nullptr)
        , enableMouseEvent(true)
        , mRunning(false) {
      }

      Scene(sf::RenderWindow* window)
        : mTitle("")
        , mMousePos({0.f, 0.f})
        , mWindow(window)
        , enableMouseEvent(true)
        , mRunning(false) {
      }

      virtual ~Scene() {
      }

      virtual void update(const float dt) = 0;
      virtual void draw() = 0;
      virtual void handleEvent(sf::Event& event) = 0;

      virtual void load() {
        mRunning = true;
        if(!mTitle.empty()) {
          mWindow->setTitle(mTitle);
        }
      }

      const bool isRunning() {
        return mRunning;
      }

      void setWindow(sf::RenderWindow* window) {
        this->mWindow = window;
      }

      const std::string& getTitle() const {
        return mTitle;
      }

      void setTitle(const std::string& title) {
        mTitle = title;
      }

      typedef std::unique_ptr<Scene> ScenePtr;

    protected:
      std::string mTitle;
      sf::Vector2f mMousePos;
      sf::RenderWindow* mWindow;
      bool enableMouseEvent;
      bool mRunning;

      const sf::Vector2f getWindowCenter() const {
        return static_cast<sf::Vector2f>(mWindow->getSize()) * 0.5f;
      }

      const sf::Vector2f getWindowSize() const {
        return static_cast<sf::Vector2f>(mWindow->getSize());
      }

      const float getWindowWidth() const {
        return static_cast<float>(mWindow->getSize().x);
      }

      const float getWindowHeight() const {
        return static_cast<float>(mWindow->getSize().y);
      }

      const float getWindowRatio() const {
        return getWindowWidth() / getWindowHeight();
      }

      const sf::Vector2f getMousePosition() const {
        return static_cast<sf::Vector2f>(sf::Mouse::getPosition(*mWindow));
      }

  };

}

#endif // SFE_SCENE_SCENE_HPP_
