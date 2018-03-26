#ifndef PAINT_CANVAS_H
#define PAINT_CANVAS_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Tool.h"

class Canvas : public sf::Drawable {
public:
    Canvas(Menu *menu) {
        this->menu = menu;
        tx2.create(795, 594);
        tx2.clear(sf::Color::Black);
        tx2.display();
        sprite.setTexture(tx2.getTexture());
    }

    void draw(sf::RenderTarget &target, sf::RenderStates) const override {
        target.draw(sprite);
    }

    void lock(sf::Event::MouseButtonEvent pos) {
        paintMode = true;
        backup = tx2.getTexture().copyToImage();
        startMousePos = sf::Event::MouseMoveEvent{pos.x, pos.y};
    }

    void unlock(sf::Event::MouseButtonEvent pos) {
        paintMode = false;
        curMousePos = sf::Event::MouseMoveEvent{pos.x, pos.y};
        useTool();
    }

    void update(sf::Event::MouseMoveEvent moveEvent) {
        if (paintMode) {
            curMousePos = moveEvent;
            texture.loadFromImage(backup);
            sprite.setTexture(texture);
            tx2.draw(sprite);
            useTool(); // Draw on tx2
            sprite.setTexture(tx2.getTexture());
        }
    }

    void save() {
        tx2.getTexture().copyToImage().saveToFile(filename);
    }

    void load() {
        if (!paintMode && texture.loadFromFile(filename)) {
            sprite.setTexture(texture);
            tx2.draw(sprite);
        }
    }

    bool paintModeOn() const {
        return paintMode;
    }

    void setTool(Tool tool) {
        this->tool = tool;
    }


    double distance() const {
        return sqrt(pow(curMousePos.x - startMousePos.x, 2) +
                    pow(curMousePos.y - startMousePos.y, 2));
    }

private:
    void drawLine() {
        sf::VertexArray line(sf::LinesStrip, 2);
        line[0].position = sf::Vector2f(startMousePos.x, startMousePos.y);
        line[0].color = fColor;
        line[1].position = sf::Vector2f(curMousePos.x, curMousePos.y);
        line[1].color = bColor;
        tx2.draw(line);
    }

    void drawCircle() {
        float r = distance() / 2;
        float move = (r * sqrt(2) - r) / sqrt(2);
        float angle = atan2f(curMousePos.y - startMousePos.y,
                             curMousePos.x - startMousePos.x) * 180 / M_PIf32;
        sf::CircleShape circleShape(r);
        circleShape.setPosition(startMousePos.x, startMousePos.y);
        circleShape.setOutlineColor(fColor);
        circleShape.setOutlineThickness(2);
        circleShape.setFillColor(sf::Color::Transparent);
        circleShape.setRotation(angle - 45);
        circleShape.setOrigin(move, move);
        tx2.draw(circleShape);
    }

    void drawRect(bool fill = false) {
        sf::RectangleShape rect(sf::Vector2f(curMousePos.x - startMousePos.x,
                                             curMousePos.y - startMousePos.y));
        if (fill)
            rect.setFillColor(bColor);
        else
            rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(fColor);
        rect.setOutlineThickness(2);
        rect.setPosition(sf::Vector2f(startMousePos.x, startMousePos.y));
        tx2.draw(rect);
    }

    void useTool() {
        switch (tool) {
            case Tool::FOREGROUND: {
                sf::Color c = menu->getPixelColor(startMousePos.x,
                                                  startMousePos.y);
                if (c != sf::Color::Transparent) {
                    fColor = c;
                    menu->setForeground(fColor);
                }
                break;
            }
            case Tool::BACKGROUND: {
                sf::Color c = menu->getPixelColor(startMousePos.x,
                                                  startMousePos.y);
                if (c != sf::Color::Transparent) {
                    bColor = c;
                    menu->setBackground(bColor);
                }
                break;
            }
            case Tool::LINE:
                drawLine();
                break;
            case Tool::CIRCLE:
                drawCircle();
                break;
            case Tool::RECTFULL:
                drawRect(true);
                break;
            case Tool::RECT:
                drawRect();
                break;
        }
    }

    const char *filename = "out.png";
    bool paintMode = false;
    sf::Color bColor, fColor;
    sf::Event::MouseMoveEvent startMousePos, curMousePos;
    sf::RenderTexture tx2;
    sf::Texture texture;
    sf::Sprite sprite;
    Tool tool;
    Menu *menu;
    sf::Image backup;
};


#endif //PAINT_CANVAS_H
