#ifndef LAB02_RGBCIRCLE_H
#define LAB02_RGBCIRCLE_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Circle.h"

class RGBCircle : public Circle {
public:
    RGBCircle(float radius) : Circle(radius) {}

private:
    sf::Color calc(float phi, float r, float percent) override {
        auto red = static_cast<sf::Uint8>(r * 255);
        auto green = static_cast<sf::Uint8>(phi * 255);
        auto blue = static_cast<sf::Uint8>(percent * 255);
        return sf::Color{red, green, blue};
    }
};


#endif //LAB02_RGBCIRCLE_H
