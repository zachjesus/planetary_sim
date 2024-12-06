#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <iostream>
#include "../include/planet.h"
#include "../include/physics.h"
#include "../include/guiHelper.h"

int main() {
    PlanetGroup group;
    
    sf::RenderWindow mainWindow(sf::VideoMode(1800, 1000), "Gravity Simulation", sf::Style::Close, sf::ContextSettings(0, 0, 8));
    sf::View mainView(sf::FloatRect(0, 0, 1200, 1000));
    mainWindow.setView(mainView);
    mainWindow.setFramerateLimit(60);
    mainWindow.setVerticalSyncEnabled(true);
    mainWindow.setPosition(sf::Vector2i(0,0));

    sf::Cursor defaultCursor;
    sf::Cursor crossCursor;
    defaultCursor.loadFromSystem(sf::Cursor::Hand);
    crossCursor.loadFromSystem(sf::Cursor::Cross);


    enum class CursorType { Default, Cross };
    CursorType currentCursor = CursorType::Default;
    mainWindow.setMouseCursor(defaultCursor);


    GuiHelper gui = GuiHelper(mainWindow, group);
    gui.createPanel();

    while(mainWindow.isOpen()) {        
        sf::Event event;
        sf::Vector2i mousePos = sf::Mouse::getPosition(mainWindow);
        sf::Vector2f worldPos = mainWindow.mapPixelToCoords(mousePos, mainView);

        while (mainWindow.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                mainWindow.close();
            }
            if(mousePos.x < 1200 && event.type == sf::Event::MouseButtonPressed) {
                std::cout << "("<< worldPos.x << ", "<< worldPos.y << ")" << std::endl;
                gui.addPlanet(worldPos);
            }
            if(mousePos.x < 1200) {
                if (currentCursor != CursorType::Cross) {
                    mainWindow.setMouseCursor(crossCursor);
                    currentCursor = CursorType::Cross;
                }
            }
            else if(mousePos.x >= 1200) {
                if (currentCursor != CursorType::Default) {
                    mainWindow.setMouseCursor(defaultCursor);
                    currentCursor = CursorType::Default;
                }
            }
            gui.guiHandleEvent(event);
        }        

        nextPosition(1000, group);
        
        for(auto& planet : group.planets) {
            mainWindow.draw(planet.shape);
        }

        mainWindow.display();
        gui.draw();
    }
}
