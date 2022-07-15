#ifndef SFE_APP_APPLICATION_HPP_
#define SFE_APP_APPLICATION_HPP_

#include "../scene/SceneManager.hpp"
#include "../system/FrameRateLimit.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <memory>
#include <string>
#include <stdexcept>

namespace sfe {

  class Application {
    public:

      Application(const float framePerSecond = 60.f)
        : FPS_LIMIT(framePerSecond)
        , mWindowPtr(new sf::RenderWindow)
        , mWindowOpened(true)
        , mCurrentScene(nullptr)
        , mNextSceneKey(sf::Keyboard::Unknown)
        , mPrevSceneKey(sf::Keyboard::Unknown) {
      }

      Application(sf::ContextSettings ctx, const float framePerSecond = 60.f)
        : FPS_LIMIT(framePerSecond)
        , mWindowPtr(new sf::RenderWindow)
        , mWindowOpened(true)
        , mCurrentScene(nullptr)
        , mNextSceneKey(sf::Keyboard::Unknown)
        , mPrevSceneKey(sf::Keyboard::Unknown) {
      }

      virtual ~Application() {
      }

      virtual void setup() {
      }

      template<typename T>
      void registerScene(const std::string sceneName) {
        mSceneManager.registerScene<T>(sceneName);
      }

      void setPosition(const int x, const int y) {
        window()->setPosition(sf::Vector2i(x, y));
      }

      void setNextSceneKey(sf::Keyboard::Key k) {
        mNextSceneKey = k;
      }

      void setPrevSceneKey(sf::Keyboard::Key k) {
        mPrevSceneKey = k;
      }

      void run(const sf::VideoMode& videoMode,
               const std::string& title = "",
               sf::ContextSettings* ctx = nullptr,
               const unsigned int style = sf::Style::Close | sf::Style::Resize) {
        init(videoMode, title, style, ctx);
        setup();
        mSceneManager.loadScene(0);
        mCurrentScene = mSceneManager.getScene();
        FrameRateLimit frameRateLimit(FPS_LIMIT);

        while (mWindowPtr.get()->isOpen()) {
          sf::Event event;

          while (mWindowPtr.get()->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
              mWindowOpened = false;
              mWindowPtr.get()->close();
              break;
            }

            if (event.type == sf::Event::KeyPressed && mSceneManager.count() > 1) {
              if (event.key.code == mNextSceneKey) {
                mCurrentScene = mSceneManager.next();
              } else if (event.key.code == mPrevSceneKey) {
                mCurrentScene = mSceneManager.previous();
              }
            }

            if (mWindowOpened) {
              mCurrentScene->handleEvent(event);
            }
          }

          frameRateLimit.update();

          mCurrentScene->update(frameRateLimit.getMaxFrameRate());

          mWindowPtr.get()->clear();
          mCurrentScene->draw();

          mWindowPtr.get()->display();
        }
        mWindowPtr.get()->close();
      }

      sf::RenderWindow* window() {
        return mWindowPtr.get();
      }

    protected:
      const float FPS_LIMIT;
      std::unique_ptr<sf::RenderWindow> mWindowPtr;
      bool mWindowOpened;
      SceneManager mSceneManager;
      Scene* mCurrentScene;
      sf::Keyboard::Key mNextSceneKey;
      sf::Keyboard::Key mPrevSceneKey;

    private:
      void init(const sf::VideoMode& videoMode, const std::string& title, const unsigned int style, sf::ContextSettings* ctxPtr) {
        sf::ContextSettings ctx;
        if (ctxPtr != nullptr) {
          ctx = *ctxPtr;
        }

        mWindowPtr.get()->create(videoMode, title, style, ctx);
        mSceneManager.setWindow(mWindowPtr.get());
      }
  };

}

#endif /* SFE_APP_APPLICATION_HPP_ */
