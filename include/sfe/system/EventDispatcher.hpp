#ifndef SFE_SYSTEM_EVENTDISPATCHER_HPP_
#define SFE_SYSTEM_EVENTDISPATCHER_HPP_

#include "EventObserver.hpp"
#include <vector>

namespace sfe {

  class EventDispatcher {

    public:

      EventDispatcher() {}
      ~EventDispatcher() {}

      void dispatch(const sf::Event& e) {
        for(auto& o : mObservers) {
          o->notify(e);
        }
      }

      void add(EventObserver* o) {
        mObservers.emplace_back(o);
      }

      void clear() {
        mObservers.clear();
      }

    private:
      std::vector<EventObserver*> mObservers;

  };

}

#endif /* SFE_SYSTEM_EVENTDISPATCHER_HPP_ */
