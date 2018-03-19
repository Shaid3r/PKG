#ifndef LAB02_CMYCIRCLE_H
#define LAB02_CMYCIRCLE_H

#include "Circle.h"
#include <cmath>

class CMYCircle : public Circle {
public:
    CMYCircle(float radius = 0) : Circle(radius) {}

private:
    sf::Color calc(float phi, float r, float percent) override {
        auto red = static_cast<sf::Uint8>((1 - r) * 255);
        auto green = static_cast<sf::Uint8>((1 - phi) * 255);
        auto blue = static_cast<sf::Uint8>((1 - percent) * 255);

        return sf::Color{red, green, blue};
    }
};


#endif //LAB02_CMYCIRCLE_H
