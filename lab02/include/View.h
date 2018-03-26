#ifndef LAB02_VIEW_H
#define LAB02_VIEW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Model.h"
#include "HSLCircle.h"
#include "HSVCircle.h"
#include "CMYCircle.h"
#include "RGBCircle.h"
#include "font.h"

class View {
public:

    View(sf::RenderWindow *window, Model *model)
            : m_window(window), m_model(model), m_updated(false) {
        font.loadFromMemory(font_data, font_data_size);
        text.setFont(font);
        text.setCharacterSize(14);
        text.setFillColor(sf::Color::Black);

        create_switcher();
        create_switcher_outline();
        create_switcher_line();

        create_circles();
        update();

        clock.restart().asMilliseconds();
    }


    ~View() {
        if (m_precalculatedData) delete[] m_precalculatedData;
        for (int i = 0; i < NUM_OF_CIRCLES; ++i)
            delete m_circles[i];
    }

    void draw() {
        ++m_frame_counter;
        if (m_updated) {
            m_updated = false;
            m_window->clear(sf::Color::White);

            m_window->draw(switcher_outline);
            m_window->draw(switcher);
            m_window->draw(switcher_line);

            print_text();

            for (int i = 0; i < NUM_OF_CIRCLES; ++i)
                m_circles[i]->draw(*m_window);

            m_window->display();
        }

        if (clock.getElapsedTime().asSeconds() >= 1.0f) {
            m_fps = static_cast<unsigned int>(
                    static_cast<float>(m_frame_counter) /
                    clock.getElapsedTime().asSeconds());
            clock.restart();
            m_frame_counter = 0;
            m_updated = true;
        }
    }

    void update() {
        m_updated = true;
        move_line(m_model->line_pos());
        for (int i = 0; i < NUM_OF_CIRCLES; ++i)
            m_circles[i]->update(m_model->bar_percent());
    }

private:
    void create_circles() {
        float radius = m_window->getSize().x * 0.16f;
        float padding = 45;

        // Optymalisation
        auto size = static_cast<size_t>(radius * 2);
        m_precalculatedData = new PolarCoord[size * size];
        Circle::initializeData(m_precalculatedData, size);

        m_circles[0] = new HSLCircle(radius, m_precalculatedData);
        m_circles[0]->setPosition(padding, padding);
        m_circles[1] = new HSVCircle(radius, m_precalculatedData);
        m_circles[1]->setPosition(2 * (radius + padding), padding);
        m_circles[2] = new CMYCircle(radius, m_precalculatedData);
        m_circles[2]->setPosition(padding, 2 * (radius + padding));
        m_circles[3] = new RGBCircle(radius, m_precalculatedData);
        m_circles[3]->setPosition(2 * (radius + padding),
                                  2 * (radius + padding));

    }

    void create_switcher() {
        sf::Vertex tl(sf::Vector2f(680, 50), sf::Color::Black);
        sf::Vertex tr(sf::Vector2f(730, 50), sf::Color::Black);
        sf::Vertex br(sf::Vector2f(730, 320), sf::Color::White);
        sf::Vertex bl(sf::Vector2f(680, 320), sf::Color::White);
        switcher.append(tl);
        switcher.append(tr);
        switcher.append(br);
        switcher.append(bl);
        switcher.setPrimitiveType(sf::Quads);
    }

    void create_switcher_outline() {
        sf::Vertex bl(sf::Vector2f(678, 320), sf::Color::Black);
        sf::Vertex tl(sf::Vector2f(678, 50), sf::Color::Black);
        sf::Vertex tr(sf::Vector2f(732, 50), sf::Color::Black);
        sf::Vertex br(sf::Vector2f(732, 320), sf::Color::Black);
        switcher_outline.append(bl);
        switcher_outline.append(tl);
        switcher_outline.append(tr);
        switcher_outline.append(br);
        switcher_outline.setPrimitiveType(sf::LineStrip);
    }

    void create_switcher_line() {
        sf::Vertex l(sf::Vector2f(670, 320), sf::Color::Black);
        sf::Vertex r(sf::Vector2f(740, 320), sf::Color::Black);
        switcher_line.append(l);
        switcher_line.append(r);
        switcher_line.setPrimitiveType(sf::LineStrip);
    }

    void move_line(int y) {
        switcher_line[0].position = sf::Vector2f(670, y);
        switcher_line[1].position = sf::Vector2f(740, y);
    }

    void print_text() {
        float percent = m_model->bar_percent();
        std::ostringstream out;
        out.setf(std::ios::fixed, std::ios::floatfield);
        out << std::setprecision(3);

        outtextxy(55, 40, "HSL");
        out << "L=" << percent;
        outtextxy(270, 285, out.str());

        outtextxy(340, 40, "HSV");
        out.str("");
        out << "V=" << percent;
        outtextxy(570, 285, out.str());

        outtextxy(55, 350, "CMY");
        out.str("");
        out << "Y=" << static_cast<int>(percent * 100) << "%";
        outtextxy(270, 600, out.str());

        outtextxy(340, 350, "RGB");
        out.str("");
        out << "B=" << static_cast<int>(percent * 255);
        outtextxy(570, 600, out.str());

        outtextxy(675, 330, std::to_string(m_fps) + " FPS");
    }

    void outtextxy(unsigned int x, unsigned int y, const std::string &s) {
        text.setPosition(x, y);
        text.setString(s);
        m_window->draw(text);
    }

    enum Config { NUM_OF_CIRCLES = 4 };
    Circle *m_circles[NUM_OF_CIRCLES];
    sf::VertexArray switcher;
    sf::VertexArray switcher_outline;
    sf::VertexArray switcher_line;

    sf::Clock clock;
    sf::Font font;
    sf::Text text;
    sf::RenderWindow *m_window;
    Model *m_model;
    PolarCoord *m_precalculatedData;
    unsigned int m_fps = 0, m_frame_counter = 0;
    bool m_updated;
};

#endif //LAB02_VIEW_H
