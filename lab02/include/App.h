#ifndef LAB02_APP_H
#define LAB02_APP_H

#include <SFML/Graphics.hpp>
#include "View.h"
#include "Model.h"

class App {
public:
    static App &GetApp();
    App(const App &) = delete;
    App &operator=(const App &) = delete;
    ~App();

    void run();
private:
    App();

    static const int WIDTH = 800;
    static const int HEIGHT = 650;

    void processEvents();

    Model *m_model;
    View *m_view;
    sf::RenderWindow *m_window;
    bool moving = false;
};


#endif //LAB02_APP_H
