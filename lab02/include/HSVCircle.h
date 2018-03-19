#ifndef LAB02_HSVCIRCLE_H
#define LAB02_HSVCIRCLE_H

#include "Circle.h"
#include <cmath>

class HSVCircle : public Circle {
public:
    HSVCircle(float radius = 0) : Circle(radius) {}

private:
    sf::Color calc(float phi, float r, float percent) override {
        return hsv2rgb(phi, r, percent);
    }

    static sf::Color hsv2rgb(float H, float S, float V) {
        float var_r = 0;
        float var_g = 0;
        float var_b = 0;

        float var_h = H * 6;
        if (var_h == 6) var_h = 0;
        float var_i = int(var_h);
        float var_1 = V * (1 - S);
        float var_2 = V * (1 - S * (var_h - var_i));
        float var_3 = V * (1 - S * (1 - (var_h - var_i)));

        if (var_i == 0) {
            var_r = V;
            var_g = var_3;
            var_b = var_1;
        } else if (var_i == 1) {
            var_r = var_2;
            var_g = V;
            var_b = var_1;
        } else if (var_i == 2) {
            var_r = var_1;
            var_g = V;
            var_b = var_3;
        } else if (var_i == 3) {
            var_r = var_1;
            var_g = var_2;
            var_b = V;
        } else if (var_i == 4) {
            var_r = var_3;
            var_g = var_1;
            var_b = V;
        } else {
            var_r = V;
            var_g = var_1;
            var_b = var_2;
        }

        return sf::Color{static_cast<sf::Uint8>(var_r * 255),
                         static_cast<sf::Uint8>(var_g * 255),
                         static_cast<sf::Uint8>(var_b * 255)};
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


#endif //LAB02_HSVCIRCLE_H
