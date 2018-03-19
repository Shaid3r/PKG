#include <iostream>
#include "App.h"

App::App() {
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Paint",
                                  sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);

    sf::Vector2i pos(sf::VideoMode::getDesktopMode().width / 2 - WIDTH / 2,
                     sf::VideoMode::getDesktopMode().height / 2 - HEIGHT / 2);
    window->setPosition(pos);

    menu = new Menu();
    canvas = new Canvas(menu);
}

App::~App() {
    delete canvas;
    delete menu;
    delete window;
}

App &App::GetApp() {
    static App instance;
    return instance;
}

void App::run() {
    while (window->isOpen()) {
        processEvents();
        render();
    }
}

void App::render() {
    window->clear(sf::Color::Black);
    window->draw(*canvas);
    window->draw(*menu);
    window->display();
}

void App::processEvents() {
    sf::Event event; // NOLINT
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();
        if (event.type == sf::Event::MouseButtonPressed)
            canvas->lock(event.mouseButton);
        if (event.type == sf::Event::MouseButtonReleased)
            canvas->unlock(event.mouseButton);
        if (event.type == sf::Event::MouseMoved)
            canvas->update(event.mouseMove);
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Escape:
                    window->close();
                    break;
                case sf::Keyboard::F:
                    setTool(Tool::FOREGROUND, 'f');
                    break;
                case sf::Keyboard::B:
                    setTool(Tool::BACKGROUND, 'b');
                    break;
                case sf::Keyboard::L:
                    setTool(Tool::LINE, 'l');
                    break;
                case sf::Keyboard::R:
                    setTool(Tool::RECT, 'r');
                    break;
                case sf::Keyboard::A:
                    setTool(Tool::RECTFULL, 'a');
                    break;
                case sf::Keyboard::C:
                    setTool(Tool::CIRCLE, 'c');
                    break;
                case sf::Keyboard::W:
                    canvas->save();
                    break;
                case sf::Keyboard::O:
                    canvas->load();
                    break;
                default:
                    break;
            }
        }
    }
}

void App::setTool(Tool t, const char c) {
    if (!canvas->paintModeOn()) {
        canvas->setTool(t);
        menu->setActiveToolStr(c);
    }
}



