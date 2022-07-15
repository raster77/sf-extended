#ifndef SFE_SYSTEM_EVENTMANAGER_HPP_
#define SFE_SYSTEM_EVENTMANAGER_HPP_

#include <SFML/Window/Event.hpp>
#include <functional>
#include <unordered_map>

namespace sfe {

  using EventCallback = std::function<void(const sf::Event& event)>;

  class EventManager {

    public:

      EventManager() {
      }

      ~EventManager() {
      }

      void registerEvent(const sf::Event& event, EventCallback eventCallback) {
        mEventsMap[event.type] = eventCallback;
      }

      void registerKeyPressEvent(const sf::Keyboard::Key& key, EventCallback eventCallback) {
        mKeyPressedEventsMap[key] = eventCallback;
      }

      void registerKeyReleaseEvent(const sf::Keyboard::Key& key, EventCallback eventCallback) {
        mKeyReleasedEventsMap[key] = eventCallback;
      }

      void registerMousePressEvent(const sf::Mouse::Button& button, EventCallback eventCallback) {
        mMouseButtonPressedEventsMap[button] = eventCallback;
      }

      void registerMouseReleaseEvent(const sf::Mouse::Button& button, EventCallback eventCallback) {
        mMouseButtonReleasedEventsMap[button] = eventCallback;
      }

      void registerMouseWheelEvent(const sf::Mouse::Wheel wheel, EventCallback eventCallback) {
        mMouseButtonWheelEventsMap[wheel] = eventCallback;
      }


      void processEvent(const sf::Event& event) {

        switch (event.type) {
          case sf::Event::EventType::KeyPressed:
            processKeyEvent(mKeyPressedEventsMap, event);
            break;
          case sf::Event::EventType::KeyReleased:
            processKeyEvent(mKeyReleasedEventsMap, event);
            break;

          case sf::Event::EventType::MouseButtonPressed:
            processMouseButtonEvent(mMouseButtonPressedEventsMap, event);
            break;
          case sf::Event::EventType::MouseButtonReleased:
            processMouseButtonEvent(mMouseButtonReleasedEventsMap, event);
            break;
          case sf::Event::EventType::MouseWheelScrolled:
            processMouseWheelEvent(mMouseButtonWheelEventsMap, event);
            break;

          default:
            auto it = mEventsMap.find(event.type);
            if (it != mEventsMap.end()) {
              it->second(event);
            }
        }

      }

    private:
      std::unordered_map<sf::Event::EventType, EventCallback> mEventsMap;
      std::unordered_map<sf::Keyboard::Key, EventCallback> mKeyPressedEventsMap;
      std::unordered_map<sf::Keyboard::Key, EventCallback> mKeyReleasedEventsMap;
      std::unordered_map<sf::Mouse::Button, EventCallback> mMouseButtonPressedEventsMap;
      std::unordered_map<sf::Mouse::Button, EventCallback> mMouseButtonReleasedEventsMap;
      std::unordered_map<sf::Mouse::Wheel, EventCallback> mMouseButtonWheelEventsMap;

      void processKeyEvent(const std::unordered_map<sf::Keyboard::Key, EventCallback>& eventMap, const sf::Event& event) {
        auto it = eventMap.find(event.key.code);
        if (it != eventMap.end()) {
          it->second(event);
        }
      }

      void processMouseButtonEvent(const std::unordered_map<sf::Mouse::Button, EventCallback>& eventMap, const sf::Event& event) {
        auto it = eventMap.find(event.mouseButton.button);
        if (it != eventMap.end()) {
          it->second(event);
        }
      }

      void processMouseWheelEvent(const std::unordered_map<sf::Mouse::Wheel, EventCallback>& eventMap, const sf::Event& event) {
        auto it = eventMap.find(event.mouseWheelScroll.wheel);
        if (it != eventMap.end()) {
          it->second(event);
        }
      }
  };

}

#endif /* SFE_SYSTEM_EVENTMANAGER_HPP_ */
