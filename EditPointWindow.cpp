// EditPointWindow.cpp
#include "EditPointWindow.h"
#include "ConvexHull.h"

EditPointWindow::EditPointWindow(const sf::Font& font)
    : title(font, L"Редактор точки", 20)
    , inputX(font, "X (50-1150):", { 520, 350 }, { 150, 30 }, true)
    , inputY(font, "Y (150-750):", { 520, 410 }, { 150, 30 }, false)
    , saveButton(font, L"Сохранить", { 480, 465 }, { 100, 30 }, "save")
    , cancelButton(font, L"Отмена", { 600, 465 }, { 100, 30 }, "cancel")
    , errorText(font, L"", 14)
    , isVisible(false)
    , currentPoint(nullptr)
    , hasError(false) {

    background.setSize({ 260, 220 });
    background.setPosition({ 460, 290 });
    background.setFillColor(sf::Color(30, 30, 40));
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color(220, 230, 240));

    title.setFillColor(sf::Color(220, 230, 240));
    title.setPosition({ 515, 300 });

    errorText.setFillColor(sf::Color::Red);
    errorText.setPosition({ 500, 445 });
}

void EditPointWindow::show(Point& point) {
    currentPoint = &point;
    originalPoint = point;
    inputX.setValue(point.x);
    inputY.setValue(point.y);
    hasError = false;
    errorText.setString(L"");
    isVisible = true;
}

void EditPointWindow::hide() {
    isVisible = false;
    currentPoint = nullptr;
}

bool EditPointWindow::isShown() const { return isVisible; }

void EditPointWindow::handleEvent(const sf::Event& event, std::vector<Point>& points, std::vector<Point>& hull) {
    if (!isVisible) return;

    inputX.handleEvent(event);
    inputY.handleEvent(event);

    if (event.is<sf::Event::MouseButtonReleased>()) {
        const sf::Event::MouseButtonReleased* mouseReleased = event.getIf<sf::Event::MouseButtonReleased>();
        if (mouseReleased) {
            if (saveButton.handleEvent(*mouseReleased)) {
                bool xValid = inputX.isValidValue();
                bool yValid = inputY.isValidValue();

                if (xValid && yValid) {
                    if (currentPoint) {
                        currentPoint->x = inputX.getValue();
                        currentPoint->y = inputY.getValue();
                        hull = convexHull(points);
                    }
                    hide();
                }
                else {
                    hasError = true;
                    if (!xValid && !yValid) {
                        errorText.setString(L"X и Y вне допустимых пределов!");
                    }
                    else if (!xValid) {
                        errorText.setString(L"X должен быть от 50 до 1150!");
                    }
                    else {
                        errorText.setString(L"Y должен быть от 150 до 750!");
                    }
                }
            }
            else if (cancelButton.handleEvent(*mouseReleased)) {
                hide();
            }
        }
    }
    else if (event.is<sf::Event::MouseMoved>()) {
        const sf::Event::MouseMoved* mouseMoved = event.getIf<sf::Event::MouseMoved>();
        if (mouseMoved) {
            saveButton.handleEvent(*mouseMoved);
            cancelButton.handleEvent(*mouseMoved);
        }
    }
    else if (event.is<sf::Event::MouseButtonPressed>()) {
        const sf::Event::MouseButtonPressed* mousePressed = event.getIf<sf::Event::MouseButtonPressed>();
        if (mousePressed) {
            saveButton.handleEvent(*mousePressed);
            cancelButton.handleEvent(*mousePressed);
        }
    }
}

void EditPointWindow::update() {
    if (!isVisible) return;
    inputX.update();
    inputY.update();
}

void EditPointWindow::draw(sf::RenderWindow& window, const sf::Font& font) {
    if (!isVisible) return;

    window.draw(background);
    window.draw(title);
    inputX.draw(window, font);
    inputY.draw(window, font);
    saveButton.draw(window);
    cancelButton.draw(window);

    if (hasError) {
        window.draw(errorText);
    }
}