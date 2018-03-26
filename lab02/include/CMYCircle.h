#ifndef LAB02_CMYCIRCLE_H
#define LAB02_CMYCIRCLE_H

#include <cmath>
#include "Circle.h"

class CMYCircle : public Circle {
public:
    CMYCircle(float radius, PolarCoord* data) : Circle(radius, data) {}

private:
    sf::Color calc(float phi, float r, float percent) override {
        auto red = static_cast<sf::Uint8>((1 - r) * 255);
        auto green = static_cast<sf::Uint8>((1 - phi) * 255);
        auto blue = static_cast<sf::Uint8>((1 - percent) * 255);

        return sf::Color{red, green, blue};
    }
};


#endif //LAB02_CMYCIRCLE_H
