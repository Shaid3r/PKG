#ifndef LAB02_CIRCLE_H
#define LAB02_CIRCLE_H

#include <SFML/Graphics.hpp>

class Circle : public sf::Drawable {
public:
    Circle(float radius)
            : m_radius(radius),
              m_width(static_cast<const unsigned int>(radius * 2)),
              m_height(static_cast<const unsigned int>(radius * 2)) {
        m_texture.create(m_width, m_height);
        sprite.setTexture(m_texture);

        pixels = new sf::Uint8[m_width * m_height * 4];
    }

    ~Circle() {
        delete[] pixels;
    }

    void setPosition(int x, int y) {
        sprite.setPosition(x, y);
    }

    void update(float percent) {
        for (unsigned int x = 0; x < m_width; ++x) {
            for (unsigned int y = 0; y < m_height; ++y) {
                float x2 = x - m_width / 2.0f;
                float y2 = y - m_height / 2.0f;
                float r = sqrtf(x2 * x2 + y2 * y2);

                if (r <= m_radius) {
                    double phi = std::atan2(y2, -x2) * 0.5 / M_PI + 0.5;

//                    sf::Color color = calc(phi, r / m_radius, percent);

//                    color_pixel(x, y, color.r, color.g, color.b);
                }
            }
        }

        m_texture.update(pixels);
    }

protected:
    virtual sf::Color calc(float phi, float r, float percent) = 0;

    void
    draw(sf::RenderTarget &target, sf::RenderStates) const override {
        target.draw(sprite);
    }

    void
    color_pixel(unsigned int x, unsigned int y, sf::Uint8 r, sf::Uint8 g,
                sf::Uint8 b) {
        pixels[4 * (y * m_width + x) + 0] = r;
        pixels[4 * (y * m_width + x) + 1] = g;
        pixels[4 * (y * m_width + x) + 2] = b;
        pixels[4 * (y * m_width + x) + 3] = 255;
    }

    const float m_radius;
    const unsigned int m_width;
    const unsigned int m_height;
    sf::Uint8 *pixels;
    sf::Texture m_texture;
    sf::Sprite sprite;
};

#endif //LAB02_CIRCLE_H
