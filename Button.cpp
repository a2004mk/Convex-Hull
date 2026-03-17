#include "Button.h"

Button::Button(const sf::Font& font, const sf::String& buttonText,
    const sf::Vector2f& position, const sf::Vector2f& size,
    const std::string& buttonAction)
    : text(font, buttonText, 20), isPressed(false), isHovered(false), action(buttonAction) {

    shape.setSize(size);
    shape.setPosition(position);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::White);

    normalColor = sf::Color(60, 70, 80);
    hoverColor = sf::Color(80, 95, 115);
    pressedColor = sf::Color(40, 50, 60);

    shape.setFillColor(normalColor);
    text.setFillColor(sf::Color(220, 230, 240));

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin({ textBounds.size.x / 2, textBounds.size.y / 2 });
    text.setPosition({ position.x + size.x / 2, position.y + size.y / 2 });
}

void Button::handleEvent(const sf::Event::MouseMoved& mouseMoved) {
    sf::Vector2f mousePos(static_cast<float>(mouseMoved.position.x),
        static_cast<float>(mouseMoved.position.y));
    bool contains = shape.getGlobalBounds().contains(mousePos);

    if (contains && !isHovered) {
        isHovered = true;
        shape.setFillColor(hoverColor);
    }
    else if (!contains && isHovered) {
        isHovered = false;
        shape.setFillColor(normalColor);
    }
}

bool Button::handleEvent(const sf::Event::MouseButtonPressed& mousePressed) {
    if (mousePressed.button != sf::Mouse::Button::Left) return false;
    sf::Vector2f mousePos(static_cast<float>(mousePressed.position.x),
        static_cast<float>(mousePressed.position.y));
    if (shape.getGlobalBounds().contains(mousePos)) {
        isPressed = true;
        shape.setFillColor(pressedColor);
        return true;
    }
    return false;
}

bool Button::handleEvent(const sf::Event::MouseButtonReleased& mouseReleased) {
    if (mouseReleased.button != sf::Mouse::Button::Left) return false;
    if (isPressed) {
        isPressed = false;
        shape.setFillColor(isHovered ? hoverColor : normalColor);

        sf::Vector2f mousePos(static_cast<float>(mouseReleased.position.x),
            static_cast<float>(mouseReleased.position.y));
        if (shape.getGlobalBounds().contains(mousePos)) {
            return true;
        }
    }
    return false;
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    window.draw(text);
}

const std::string& Button::getAction() const { return action; }

void Button::setText(const sf::String& newText) {
    //text.setFont(font);
    text.setString(newText);

    // Пересчитываем центрирование текста (как в конструкторе)
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin({ textBounds.size.x / 2, textBounds.size.y / 2 });

    // Позиция текста = центр кнопки (берём из shape)
    sf::Vector2f shapePos = shape.getPosition();
    sf::Vector2f shapeSize = shape.getSize();
    text.setPosition({
        shapePos.x + shapeSize.x / 2,
        shapePos.y + shapeSize.y / 2
        });
}