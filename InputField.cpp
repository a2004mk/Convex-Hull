// InputField.cpp
#include "InputField.h"
#include "Point.h"
#include <sstream>

InputField::InputField(const sf::Font& font, const std::string& fieldLabel,
    const sf::Vector2f& position, const sf::Vector2f& size, bool xCoord)
    : text(font), isSelected(false), isHovered(false), label(fieldLabel), value(0),
    isX(xCoord), showCursor(false), justSelected(false) {

    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color(50, 50, 50));
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color(100, 100, 100));

    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    text.setPosition({ position.x + 5, position.y + 5 });
    text.setString("0");
    input = "0";

    cursor.setSize({ 2, 20 });
    cursor.setFillColor(sf::Color::White);
    updateCursorPosition();
}

void InputField::updateCursorPosition() {
    float textWidth = text.getGlobalBounds().size.x;
    cursor.setPosition({ shape.getPosition().x + 7 + textWidth, shape.getPosition().y + 5 });
}

void InputField::handleEvent(const sf::Event& event) {
    if (event.is<sf::Event::TextEntered>()) {
        const sf::Event::TextEntered* textEntered = event.getIf<sf::Event::TextEntered>();
        if (isSelected && textEntered) {
            if (textEntered->unicode == '\b') {
                if (!input.isEmpty()) {
                    input.erase(input.getSize() - 1);
                    if (input.isEmpty()) input = "0";
                }
            }
            else if (textEntered->unicode < 128) {
                char c = static_cast<char>(textEntered->unicode);
                if (isdigit(c) || c == '.' || c == '-') {
                    if (justSelected) {
                        input.clear();
                        justSelected = false;
                    }
                    if (input == "0") input.clear();
                    input += c;
                }
            }
            text.setString(input);
            updateCursorPosition();
            cursorClock.restart();
            showCursor = true;
        }
    }
    else if (event.is<sf::Event::MouseButtonPressed>()) {
        const sf::Event::MouseButtonPressed* mousePressed = event.getIf<sf::Event::MouseButtonPressed>();
        if (mousePressed) {
            sf::Vector2f mousePos(static_cast<float>(mousePressed->position.x),
                static_cast<float>(mousePressed->position.y));
            bool wasSelected = isSelected;
            isSelected = shape.getGlobalBounds().contains(mousePos);

            if (isSelected) {
                shape.setOutlineColor(sf::Color::Green);
                cursorClock.restart();
                showCursor = true;
                if (!wasSelected) {
                    justSelected = true;
                }
            }
            else {
                shape.setOutlineColor(sf::Color(100, 100, 100));
                showCursor = false;
                justSelected = false;
            }
        }
    }
    else if (event.is<sf::Event::MouseMoved>()) {
        const sf::Event::MouseMoved* mouseMoved = event.getIf<sf::Event::MouseMoved>();
        if (mouseMoved) {
            sf::Vector2f mousePos(static_cast<float>(mouseMoved->position.x),
                static_cast<float>(mouseMoved->position.y));
            bool contains = shape.getGlobalBounds().contains(mousePos);

            if (contains && !isHovered) {
                isHovered = true;
                if (!isSelected) {
                    shape.setOutlineColor(sf::Color(150, 150, 150));
                }
            }
            else if (!contains && isHovered && !isSelected) {
                isHovered = false;
                shape.setOutlineColor(sf::Color(100, 100, 100));
            }
        }
    }
}

void InputField::update() {
    if (isSelected) {
        if (cursorClock.getElapsedTime().asMilliseconds() > 500) {
            showCursor = !showCursor;
            cursorClock.restart();
        }
    }
    else {
        showCursor = false;
    }
}

void InputField::setValue(float val) {
    value = val;
    std::stringstream ss;
    ss << val;
    input = ss.str();
    text.setString(input);
    updateCursorPosition();
}

float InputField::getValue() const {
    if (input.isEmpty()) return 0;
    try {
        return std::stof(input.toAnsiString());
    }
    catch (...) {
        return 0;
    }
}

bool InputField::isValidValue() const {
    float val = getValue();
    if (isX) {
        return val >= WORK_AREA_MIN_X && val <= WORK_AREA_MAX_X;
    }
    else {
        return val >= WORK_AREA_MIN_Y && val <= WORK_AREA_MAX_Y;
    }
}

void InputField::draw(sf::RenderWindow& window, const sf::Font& font) {
    window.draw(shape);

    sf::Text labelText(font, label, 14);
    labelText.setFillColor(sf::Color(180, 180, 180));
    labelText.setPosition({ shape.getPosition().x, shape.getPosition().y - 18 });
    window.draw(labelText);

    window.draw(text);

    if (showCursor && isSelected) {
        window.draw(cursor);
    }
}

void InputField::clear() {
    input = "0";
    text.setString("0");
    updateCursorPosition();
}