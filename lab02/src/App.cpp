#include "App.h"

App::App() {
    m_window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Lab02",
                                    sf::Style::Titlebar | sf::Style::Close);
    sf::Vector2i pos(sf::VideoMode::getDesktopMode().width / 2 - WIDTH / 2,
                     sf::VideoMode::getDesktopMode().height / 2 - HEIGHT / 2);
    m_window->setPosition(pos);
    m_model = new Model;
    m_view = new View(m_window, m_model);
}

App::~App() {
    delete m_view;
    delete m_model;
    delete m_window;
}

App &App::GetApp() {
    static App instance;
    return instance;
}

void App::run() {
    while (m_window->isOpen()) {
        processEvents();

        m_view->draw();
    }
}

void App::processEvents() {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window->close();
        if (event.type == sf::Event::MouseButtonPressed){
            moving = true;
            m_model->set_line_pos(event.mouseButton.x, event.mouseButton.y);
            m_view->update();
        }
        if (event.type == sf::Event::MouseMoved && moving) {
            m_model->set_line_pos(event.mouseMove.x, event.mouseMove.y);
//            m_view->update();
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            moving = false;
        }
    }
}


