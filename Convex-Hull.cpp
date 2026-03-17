// main.cpp
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include "Point.h"
#include "GameState.h"
#include "Button.h"
#include "EditPointWindow.h"
#include "InputHandler.h"
#include "Renderer.h"

bool loadFont(sf::Font& font) {
    const std::vector<std::string> paths = {
        "resources/arial.ttf",
        "../resources/arial.ttf",
        "C:/Windows/Fonts/arial.ttf"
    };

    for (const std::string& path : paths) {
        if (font.openFromFile(path)) {
            std::cout << "Font loaded from: " << path << std::endl;
            return true;
        }
    }
    std::cerr << "Failed to load font from any path!" << std::endl;
    return false;
}

int main() {
    sf::RenderWindow window(sf::VideoMode({ 1200, 800 }), L"Convex Hull Visualization");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!loadFont(font)) {
        std::cerr << "Failed to load font! Try placing arial.ttf in 'resources/' folder." << std::endl;
        return -1;
    }

    // Инициализация компонентов
    GameState gameState;

    std::vector<Button> buttons;
    for (int i = 0; i < GameConfig::BUTTON_COUNT; i++) {
        buttons.emplace_back(font, GameConfig::BUTTON_TEXTS[i],
            GameConfig::BUTTON_POSITIONS[i], GameConfig::BUTTON_SIZES[i],
            GameConfig::BUTTON_ACTIONS[i]);
    }

    EditPointWindow editWindow(font);
    InputHandler inputHandler(buttons, gameState, editWindow, font);
    Renderer renderer(window, font, gameState, buttons);

    while (window.isOpen()) {
        // Обработка событий
        while (true) {
            std::optional<sf::Event> event = window.pollEvent();
            if (!event.has_value()) break;

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (event->is<sf::Event::KeyPressed>()) {
                const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
                if (keyPressed && keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                }
            }

            inputHandler.handleEvent(*event);

            if (editWindow.isShown()) {
                editWindow.handleEvent(*event, gameState.points, gameState.hull);
            }
        }

        // Обновление
        editWindow.update();

        // Отрисовка
        renderer.render(editWindow);
    }

    return 0;
}