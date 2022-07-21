#ifndef SFE_GRAPHICS_COLOR_HPP_
#define SFE_GRAPHICS_COLOR_HPP_

#include <SFML/Graphics/Color.hpp>
#include <algorithm>
#include <cmath>
#include <vector>

namespace sfe {

  class Color {

    public:

      struct HSV {
          float h;
          float s;
          float v;
          float a;

          HSV()
            : h(0)
            , s(0)
            , v(0)
            , a(1) {
          }

          HSV(const float h, const float s, const float v)
            : h(h)
            , s(s)
            , v(v)
            , a(1) {
          }

          HSV(const float h, const float s, const float v, const float a)
            : h(h)
            , s(s)
            , v(v)
            , a(a) {
          }

      };

      static HSV RGBtoHSV(const sf::Color& color) {
        const float r = color.r / 255.f;
        const float g = color.g / 255.f;
        const float b = color.b / 255.f;

        const float max = std::max( { r, g, b });
        const float min = std::min( { r, g, b });
        const float chroma = max - min;

        float hue = 0.f;
        float saturation = 0.f;
        float value = 0.f;

        if (chroma != 0.f) {
          if (max == r) {
            hue = std::fmod(((g - b) / chroma), 6.f);
          }
          else if (max == g) {
            hue = ((b - r) / chroma) + 2;
          }
          else if (max == b) {
            hue = ((r - g) / chroma) + 4;
          }

          hue *= 60.f;
        }

        if (hue < 0.f) {
          hue += 360.f;
        }

        value = max;

        if (value != 0.f) {
          saturation = chroma / value;
        }

        return HSV(hue, saturation, value);
      }

      static sf::Color HSVtoRGB(const HSV& hsv) {
        const float chroma = hsv.s * hsv.v;
        const float h2 = std::fmod(hsv.h / 60.f, 6.f);
        const float x = chroma * (1.f - std::fabs(std::fmod(h2, 2.f) - 1.f));
        const float m = hsv.v - chroma;

        float r = 0.f;
        float g = 0.f;
        float b = 0.f;

        switch (static_cast<int>(h2)) {
          case 0:
            r = chroma;
            g = x;
            break;
          case 1:
            r = x;
            g = chroma;
            break;
          case 2:
            g = chroma;
            b = x;
            break;
          case 3:
            g = x;
            b = chroma;
            break;
          case 4:
            r = x;
            b = chroma;
            break;
          case 5:
            r = chroma;
            b = x;
            break;
        }

        r += m;
        g += m;
        b += m;

        return sf::Color(static_cast<sf::Uint8>(std::round(r * 255)),
                         static_cast<sf::Uint8>(std::round(g * 255)),
                         static_cast<sf::Uint8>(std::round(b * 255)));
      }

      static std::vector<sf::Color> interpolate(const sf::Color& a, const sf::Color& b, const std::size_t step, const bool alpha = true) {
        std::vector<sf::Color> colors;
        colors.reserve(step);
        const std::size_t maxStep = std::min(step, static_cast<std::size_t>(255));

        for (std::size_t i = 0; i < maxStep; ++i) {
          const float s = static_cast<float>(i) / static_cast<float>(maxStep);
          colors.emplace_back(interpolateRGB(a, b, s, alpha));
        }

        return colors;
      }

      static std::vector<sf::Color> interpolate(const HSV& a, const HSV& b, const std::size_t step, const bool alpha = true) {
        std::vector<sf::Color> colors;
        colors.reserve(step);
        const std::size_t maxStep = std::min(step, static_cast<std::size_t>(255));

        for (std::size_t i = 0; i < maxStep; ++i) {
          const float s = static_cast<float>(i + 1) / static_cast<float>(maxStep);
          sf::Color c = HSVtoRGB(interpolateHSV(a, b, s, alpha));
          colors.emplace_back(c);
        }

        return colors;
      }

      static std::vector<sf::Color> shade(const sf::Color& c, const std::size_t steps) {
        std::vector<sf::Color> colors;
        colors.reserve(steps);
        const std::size_t maxStep = std::min(steps, static_cast<std::size_t>(255));
        const float fSteps = static_cast<float>(maxStep);

        for(std::size_t i = maxStep; i > 0; --i) {
          const float factor = static_cast<float>(i) / fSteps;
          sf::Uint8 r = std::round(c.r * factor);
          sf::Uint8 g = std::round(c.g * factor);
          sf::Uint8 b = std::round(c.b * factor);

          colors.emplace_back(sf::Color(r, g, b));
        }

        return colors;
      }

      static std::vector<sf::Color> tint(const sf::Color& c, const std::size_t steps) {
        std::vector<sf::Color> colors;
        colors.reserve(steps);
        const std::size_t maxStep = std::min(steps, static_cast<std::size_t>(255));
        const float fSteps = static_cast<float>(maxStep);

        for(std::size_t i = maxStep; i > 0; --i) {
          const float factor = static_cast<float>(i) / fSteps;
          sf::Uint8 r = std::round((255 - c.r) * factor);
          sf::Uint8 g = std::round((255 - c.g) * factor);
          sf::Uint8 b = std::round((255 - c.b) * factor);

          colors.emplace_back(sf::Color(r, g, b));
        }

        return colors;
      }

    private:

      Color() {
      }

      ~Color() {
      }

      static sf::Color interpolateRGB(const sf::Color& a, const sf::Color& b, const float t, const bool alpha = true) {
        return sf::Color(a.r + std::round((b.r - a.r) * t),
                         a.g + std::round((b.g - a.g) * t),
                         a.b + std::round((b.b - a.b) * t),
                         alpha ? a.a + std::round((b.a - a.a) * t) : 255);
      }

      static HSV interpolateHSV(const HSV& a, const HSV& b, const float t, const bool alpha = true) {
        HSV hsv(a.h + std::round((b.h - a.h) * t),
                a.s + std::round((b.s - a.s) * t),
                a.v + std::round((b.v - a.v) * t),
                alpha ? a.a + std::round((b.a - a.a) * t) : 1);
        return hsv;
      }

  };

}

#endif /* SFE_GRAPHICS_COLOR_HPP_ */
