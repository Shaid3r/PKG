#ifndef LAB02_MODEL_H
#define LAB02_MODEL_H

class Model {
public:
    Model() : m_line_pos(185), m_percent(0.5f) {};

    void set_line_pos(int y) {
        if (y != prev_pos) {
            changed = true;
            prev_pos = y;
            m_line_pos = y;
            m_percent = (y - 50) / (320.f - 50);
            return;
        }
        changed = false;
    }

    int line_pos() const {
        return m_line_pos;
    }

    float bar_percent() const {
        return m_percent;
    }

    bool isChanged() const {
        return changed;
    }

private:
    bool changed;
    int prev_pos;
    int m_line_pos;
    float m_percent;
};

#endif //LAB02_MODEL_H
