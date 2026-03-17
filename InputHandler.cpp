// InputHandler.cpp
#include "InputHandler.h"
#include "ConvexHull.h"

InputHandler::InputHandler(std::vector<Button>& btns, GameState& state,
    EditPointWindow& editWnd, sf::Font& fnt)
    : buttons(btns), gameState(state), editWindow(editWnd), font(fnt) {
}

void InputHandler::handleKeyPressed(const sf::Event::KeyPressed& keyPressed) {
    if (keyPressed.scancode == sf::Keyboard::Scancode::Escape) {
        // в main
    }
    else if (keyPressed.scancode == sf::Keyboard::Scancode::Space) {
        gameState.generateRandomPoints(20);
    }
}

void InputHandler::handleMouseMoved(const sf::Event::MouseMoved& mouseMoved) {
    gameState.mousePos = sf::Vector2f(static_cast<float>(mouseMoved.position.x),
        static_cast<float>(mouseMoved.position.y));

    for (std::vector<Button>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
        it->handleEvent(mouseMoved);
    }
}

void InputHandler::handleMousePressed(const sf::Event::MouseButtonPressed& mousePressed) {
    if (mousePressed.button != sf::Mouse::Button::Left) return;

    bool buttonPressed = false;
    for (std::vector<Button>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
        if (it->handleEvent(mousePressed)) {
            buttonPressed = true;
            break;
        }
    }

    if (!buttonPressed) {
        sf::Vector2f clickPos(static_cast<float>(mousePressed.position.x),
            static_cast<float>(mousePressed.position.y));

        if (gameState.addMode) {
            gameState.tryAddPoint(clickPos);
        }
        else if (gameState.editMode && !editWindow.isShown()) {
            int index = gameState.findPointNear(clickPos, 20.0f);
            if (index >= 0) {
                gameState.selectedPointIndex = index;
                editWindow.show(gameState.points[index]);
            }
        }
    }
}

void InputHandler::handleButtonAction(const std::string& action) {
    if (action == "random20") {
        gameState.generateRandomPoints(20);
    }
    else if (action == "random50") {
        gameState.generateRandomPoints(50);
    }
    else if (action == "clear") {
        gameState.clearAll();
    }
    else if (action == "toggle_add") {
        gameState.addMode = !gameState.addMode;
        gameState.editMode = false;
        buttons[3].setText(gameState.addMode ? L"Добавление: ВКЛ" : L"Добавление: ВЫКЛ");
    }
    else if (action == "edit") {
        gameState.editMode = !gameState.editMode;
        gameState.addMode = false;
        gameState.selectedPointIndex = -1;
    }
    else if (action == "remove_last") {
        gameState.removeLastPoint();
    }
    else if (action == "exit") {
        //выход в main
    }
}

void InputHandler::handleMouseReleased(const sf::Event::MouseButtonReleased& mouseReleased) {
    if (mouseReleased.button != sf::Mouse::Button::Left) return;

    for (std::vector<Button>::iterator it = buttons.begin(); it != buttons.end(); ++it) {
        if (it->handleEvent(mouseReleased)) {
            handleButtonAction(it->getAction());
            break;
        }
    }
}

void InputHandler::handleEvent(const sf::Event& event) {
    if (event.is<sf::Event::KeyPressed>()) {
        const sf::Event::KeyPressed* keyPressed = event.getIf<sf::Event::KeyPressed>();
        if (keyPressed) handleKeyPressed(*keyPressed);
    }
    else if (event.is<sf::Event::MouseMoved>()) {
        const sf::Event::MouseMoved* mouseMoved = event.getIf<sf::Event::MouseMoved>();
        if (mouseMoved) handleMouseMoved(*mouseMoved);
    }
    else if (event.is<sf::Event::MouseButtonPressed>()) {
        const sf::Event::MouseButtonPressed* mousePressed = event.getIf<sf::Event::MouseButtonPressed>();
        if (mousePressed) handleMousePressed(*mousePressed);
    }
    else if (event.is<sf::Event::MouseButtonReleased>()) {
        const sf::Event::MouseButtonReleased* mouseReleased = event.getIf<sf::Event::MouseButtonReleased>();
        if (mouseReleased) handleMouseReleased(*mouseReleased);
    }
}