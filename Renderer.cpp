#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow& wnd, sf::Font& fnt,
    GameState& state, const std::vector<Button>& btns)
    : window(wnd), font(fnt), gameState(state), buttons(btns) {
}

void Renderer::drawWorkArea() {
    sf::RectangleShape workAreaBackground(sf::Vector2f(
        WORK_AREA_MAX_X - WORK_AREA_MIN_X + 50,
        WORK_AREA_MAX_Y - WORK_AREA_MIN_Y + 50));
    workAreaBackground.setPosition({ WORK_AREA_MIN_X - 25, WORK_AREA_MIN_Y - 25 });
    workAreaBackground.setFillColor(sf::Color(20, 25, 30));
    workAreaBackground.setOutlineThickness(1);
    workAreaBackground.setOutlineColor(sf::Color(100, 100, 100));
    window.draw(workAreaBackground);

    sf::RectangleShape separator(sf::Vector2f(1200, 2));
    separator.setPosition({ 0, WORK_AREA_MIN_Y - 10 });
    separator.setFillColor(sf::Color::White);
    window.draw(separator);

    sf::RectangleShape topArea(sf::Vector2f(1200, WORK_AREA_MIN_Y - 10));
    topArea.setPosition({ 0, 0 });
    topArea.setFillColor(sf::Color(15, 20, 25));
    window.draw(topArea);
}

void Renderer::drawPoints() {
    for (size_t i = 0; i < gameState.points.size(); i++) {
        if (gameState.editMode && static_cast<int>(i) == gameState.selectedPointIndex) {
            sf::CircleShape& shape = gameState.selectedPointShape;
            shape.setPosition({ gameState.points[i].x, gameState.points[i].y });
            window.draw(shape);
        }
        else {
            sf::CircleShape& shape = gameState.pointShape;
            shape.setPosition({ gameState.points[i].x, gameState.points[i].y });
            window.draw(shape);
        }
    }
}

void Renderer::drawHull() {
    for (std::vector<Point>::const_iterator it = gameState.hull.begin();
        it != gameState.hull.end(); ++it) {
        sf::CircleShape& shape = gameState.hullPointShape;
        shape.setPosition({ it->x, it->y });
        window.draw(shape);
    }

    if (gameState.hull.size() >= 3) {
        sf::VertexArray hullLines;
        hullLines.setPrimitiveType(sf::PrimitiveType::LineStrip);

        for (std::vector<Point>::const_iterator it = gameState.hull.begin();
            it != gameState.hull.end(); ++it) {
            sf::Vertex vertex;
            vertex.position = sf::Vector2f(it->x, it->y);
            vertex.color = sf::Color::Green;
            hullLines.append(vertex);
        }

        sf::Vertex firstVertex;
        firstVertex.position = sf::Vector2f(gameState.hull[0].x, gameState.hull[0].y);
        firstVertex.color = sf::Color::Green;
        hullLines.append(firstVertex);

        window.draw(hullLines);
    }
}

void Renderer::drawPreview() {
    if (gameState.addMode &&
        gameState.mousePos.y > WORK_AREA_MIN_Y && gameState.mousePos.y < WORK_AREA_MAX_Y &&
        gameState.mousePos.x > WORK_AREA_MIN_X && gameState.mousePos.x < WORK_AREA_MAX_X) {
        sf::CircleShape& shape = gameState.tempPointShape;
        shape.setPosition(gameState.mousePos);
        window.draw(shape);
    }
}

void Renderer::drawUI() {
    // Инструкции
    sf::Text instructions(font, L"Нажмите пробел для генерации 20 случайных точек или используйте кнопки", 18);
    instructions.setFillColor(sf::Color(220, 230, 240));
    instructions.setPosition(GameConfig::INSTRUCTION_POS);
    window.draw(instructions);

    // Счетчик точек
    sf::Text pointsCountText(font,
        L"Точек: " + std::to_wstring(gameState.points.size()) +
        L" | В оболочке: " + std::to_wstring(gameState.hull.size()), 18);
    pointsCountText.setFillColor(sf::Color(220, 230, 240));
    pointsCountText.setPosition(GameConfig::COUNTER_POS);
    window.draw(pointsCountText);

    // Границы области
    sf::Text boundsText(font, L"Рабочая область: X(50-1150), Y(150-750)", 14);
    boundsText.setFillColor(sf::Color(180, 180, 180));
    boundsText.setPosition(GameConfig::BOUNDS_POS);
    window.draw(boundsText);

    // Текст режима
    sf::Text modeText(font,
        gameState.editMode ? L"Режим: ИЗМЕНЕНИЕ (нажмите на точку)" :
        (gameState.addMode ? L"Режим: ДОБАВЛЕНИЕ" : L"Режим: ПРОСМОТР"), 18);
    modeText.setFillColor(gameState.editMode ? sf::Color::Red :
        (gameState.addMode ? sf::Color::Green : sf::Color(220, 230, 240)));
    modeText.setPosition(GameConfig::MODE_TEXT_POS);
    window.draw(modeText);

    // Кнопки
    for (std::vector<Button>::const_iterator it = buttons.begin(); it != buttons.end(); ++it) {
        it->draw(window);
    }
}

void Renderer::drawEditWindow(EditPointWindow& editWindow) {
    editWindow.draw(window, font);
}

void Renderer::render(EditPointWindow& editWindow) {
    window.clear(sf::Color::Black);

    drawWorkArea();
    drawPoints();
    drawHull();
    drawPreview();
    drawUI();
    drawEditWindow(editWindow);

    window.display();
}