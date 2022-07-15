#ifndef SFE_SYSTEM_CLOCK_HPP_
#define SFE_SYSTEM_CLOCK_HPP_

#include <chrono>

namespace sfe {

  class Clock {
    public:
      Clock()
          : mStart(std::chrono::steady_clock::now()) {
      }

      ~Clock() {
      }

      float asMilliseconds() {
        auto duration = std::chrono::duration<float, std::milli>(std::chrono::steady_clock::now() - mStart);
        return duration.count();
      }

      float asMicroseconds() {
        auto duration = std::chrono::duration<float, std::micro>(std::chrono::steady_clock::now() - mStart);
        return duration.count();
      }

      float asSeconds() {
        auto duration = std::chrono::duration<float, std::ratio<1>>(std::chrono::steady_clock::now() - mStart);
        return duration.count();
      }

      void restart() {
        mStart = std::chrono::steady_clock::now();
      }

    private:
      std::chrono::time_point<std::chrono::steady_clock> mStart;

  };

}

#endif /* SFE_SYSTEM_CLOCK_HPP_ */
