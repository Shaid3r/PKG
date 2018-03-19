#ifndef LAB02_MODEL_H
#define LAB02_MODEL_H

#include <SFML/System/Clock.hpp>

class Model {
public:
    Model() : m_line_pos(185), m_percent(0.5f) {};

    void set_line_pos(int x, int y) {
        if (x >= 678 && x <= 732 && y >= 50 && y <= 320) {
            m_line_pos = y;
            m_percent = (y - 50) / (320.f - 50);
        }
    }

    int line_pos() const {
        return m_line_pos;
    }

    float bar_percent() const {
        return m_percent;
    }
private:
    int m_line_pos;
    float m_percent;
};

#endif //LAB02_MODEL_H
