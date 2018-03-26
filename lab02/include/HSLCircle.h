#ifndef LAB02_HSLCIRCLE_H
#define LAB02_HSLCIRCLE_H

#include <cmath>
#include "Circle.h"

class HSLCircle : public Circle {
public:
    HSLCircle(float radius, PolarCoord* data) : Circle(radius, data) {}

private:
    sf::Color calc(float phi, float r, float percent) override {
        return hsl2rgb(phi, r, percent);
    }

    static sf::Color hsl2rgb(float hue, float S, float L) {
        unsigned char r = 0;
        unsigned char g = 0;
        unsigned char b = 0;

        float v1, v2;

        v2 = (L < 0.5) ? (L * (1 + S)) : ((L + S) - (L * S));
        v1 = 2 * L - v2;

        r = (unsigned char) (255 * HueToRGB(v1, v2, hue + (1.0f / 3)));
        g = (unsigned char) (255 * HueToRGB(v1, v2, hue));
        b = (unsigned char) (255 * HueToRGB(v1, v2, hue - (1.0f / 3)));

        return sf::Color{r, g, b};
    }

    static float HueToRGB(float v1, float v2, float vH) {
        if (vH < 0)
            vH += 1;

        if (vH > 1)
            vH -= 1;

        if ((6 * vH) < 1)
            return (v1 + (v2 - v1) * 6 * vH);

        if ((2 * vH) < 1)
            return v2;

        if ((3 * vH) < 2)
            return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);

        return v1;
    }
};


#endif //LAB02_HSLCIRCLE_H
