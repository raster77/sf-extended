#ifndef SFE_SYSTEM_FPS_HPP_
#define SFE_SYSTEM_FPS_HPP_

#include "Clock.hpp"

namespace sfe {

  class Fps {
    public:
      Fps()
        : frame(0)
        , mFps(0) {
      }

      ~Fps() {
      }

      void update() {
        if (clock.asMilliseconds() >= 1000.f) {
          mFps = frame;
          frame = 0;
          clock.restart();
        }

        ++frame;
      }

      const std::size_t getFPS() const {
        return mFps;
      }

    private:
      std::size_t frame;
      std::size_t mFps;
      Clock clock;
  };

}

#endif // SFE_SYSTEM_FPS_HPP_
