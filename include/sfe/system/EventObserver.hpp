#ifndef SFAPP_SYSTEM_EVENTOBSERVER_HPP_
#define SFAPP_SYSTEM_EVENTOBSERVER_HPP_

#include <SFML/Window/Event.hpp>

namespace sfe {

  class EventObserver {

    public:

      EventObserver() {}
      virtual ~EventObserver() {}

      virtual void notify(const sf::Event& e) = 0;

  };

}

#endif /* SFAPP_SYSTEM_EVENTOBSERVER_HPP_ */
