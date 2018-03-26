#ifndef LAB02_CIRCLE_H
#define LAB02_CIRCLE_H

#include <SFML/Graphics.hpp>
#include "View.h"
#include <cmath>

struct PolarCoord {
    float radius;
    float phi;
};

class Circle {
public:
    Circle(float radius, PolarCoord *data)
            : m_radius(radius),
              m_width(static_cast<const unsigned int>(radius * 2)),
              m_height(static_cast<const unsigned int>(radius * 2)),
              m_data(data) {
        m_texture.create(m_width, m_height);
        m_sprite.setTexture(m_texture);

        pixels = new sf::Uint8[m_width * m_height * 4];
    }

    virtual ~Circle() {
        delete[] pixels;
    }

    void setPosition(int x, int y) {
        m_sprite.setPosition(x, y);
    }

    void update(float percent) {
        for (unsigned i = 0; i < m_width * m_height; ++i) {
            if (!std::isnan(m_data[i].radius)) {
                sf::Color color = calc(m_data[i].phi, m_data[i].radius,
                                       percent);
                color_pixel(i, color.r, color.g, color.b);
            }
        }

        m_texture.update(pixels);
    }

    static void initializeData(PolarCoord *pCoord, size_t size) {
        float radius = size / 2.f;
        for (unsigned int x = 0; x < size; ++x) {
            for (unsigned int y = 0; y < size; ++y) {
                float x2 = x - size / 2.0f;
                float y2 = y - size / 2.0f;
                float r = sqrtf(x2 * x2 + y2 * y2);

                if (r <= radius) {
                    pCoord[y * size + x].radius = r / radius;
                    pCoord[y * size + x].phi =
                            std::atan2(y2, -x2) * 0.5f / M_PI + 0.5f;
                } else {
                    pCoord[y * size +
                           x].radius = nanf("");
                }
            }
        }
    };

    void draw(sf::RenderTarget &target) const {
        target.draw(m_sprite);
    }

protected:
    virtual sf::Color calc(float phi, float r, float percent) = 0;

    void
    color_pixel(unsigned int i, sf::Uint8 r, sf::Uint8 g,
                sf::Uint8 b) {
        pixels[4 * i + 0] = r;
        pixels[4 * i + 1] = g;
        pixels[4 * i + 2] = b;
        pixels[4 * i + 3] = 255;
    }

    const float m_radius;
    const unsigned int m_width;
    const unsigned int m_height;
    sf::Uint8 *pixels;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    PolarCoord *m_data;
};

#endif //LAB02_CIRCLE_H
