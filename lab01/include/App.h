#ifndef PAINT_APP_H
#define PAINT_APP_H


#include <SFML/Graphics.hpp>
#include <memory>
#include "Menu.h"
#include "Canvas.h"
#include "Tool.h"

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

    void setTool(Tool t, const char c);

    void processEvents();
    void render();

    sf::RenderWindow *window;
    Menu *menu;
    Canvas *canvas;
};


#endif //PAINT_APP_H
