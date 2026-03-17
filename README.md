# Convex Hull Graham Scan

# Постановка задачи
Реализовать программу в виде оконного приложения, реализующего ввод в графическое поле набора точек, построение на этом наборе точек минимально выпуклой оболочки и вывод на экран результата.  
Язык программирования - C++.  
Разрешается использовать любые доступные фреймворки для построения оконных приложений на C++.  
Запрещается использовать готовые библиотечные решения для построения оболочек.  

# Описание проекта
Данное приложение демонстрирует работу алгоритма построения выпуклой оболочки множества точек на плоскости. Пользователь может добавлять точки вручную, генерировать случайные наборы, редактировать координаты и наблюдать, как строится оболочка в реальном времени.

# Технические требования

ОС: Windows 10/11 (протестировано), Linux/macOS (совместимо)  
Компилятор: C++17 или новее (GCC, Clang, MSVC)  
Библиотека: SFML 3.x (Graphics, Window, System)  
Шрифт: arial.ttf (или любой другой .ttf, в папке resources есть arial)  

# Сборка проекта и запуск
## Windows
### Прямая компиляция через g++
```
# Компиляция всех файлов + линковка SFML
g++ -std=c++17 -Wall -I"C:\SFML\include" -L"C:\SFML\lib" ^
    main.cpp Point.cpp GameState.cpp Renderer.cpp ^
    InputHandler.cpp Button.cpp InputField.cpp ^
    EditPointWindow.cpp ConvexHull.cpp ^
    -lsfml-graphics -lsfml-window -lsfml-system ^
    -o Convex-Hull.exe

# Запуск
Convex-Hull.exe
```
**Важно:** Укажите правильные пути к SFML (-I для заголовков, -L для библиотек)

### С помощью Makefile (рекомендуется)
```
# Создание папки сборки
mkdir build && cd build

# Генерация проекта (укажите путь к SFML, если нужно)
cmake .. -DSFML_DIR="C:/SFML/lib/cmake/SFML"

# Сборка
cmake --build . --config Release

# Запуск
Release\Convex-Hull.exe
```

## Linux/macOS

### CMake
```
mkdir build && cd build
cmake ..
make
./Convex-Hull
```
### Прямая компиляция
```
g++ -std=c++17 -Wall \
    main.cpp Point.cpp GameState.cpp Renderer.cpp \
    InputHandler.cpp Button.cpp InputField.cpp \
    EditPointWindow.cpp ConvexHull.cpp \
    -lsfml-graphics -lsfml-window -lsfml-system \
    -o Convex-Hull

./Convex-Hull
```
# Структура проекта
Convex-Hull/  
├── main.cpp              # Точка входа, игровой цикл  
├── Point.h / Point.cpp   # Класс точки, утилиты (ориентация, расстояние)  
├── GameState.h / GameState.cpp   # Состояние приложения, конфигурация  
├── Renderer.h / Renderer.cpp     # Отрисовка всех элементов  
├── InputHandler.h / InputHandler.cpp  # Обработка ввода  
├── Button.h / Button.cpp         # UI-компонент: кнопка  
├── InputField.h / InputField.cpp # UI-компонент: поле ввода  
├── EditPointWindow.h / EditPointWindow.cpp  # Окно редактирования точки  
├── ConvexHull.h / ConvexHull.cpp # Алгоритм Грэхема  
├── resources/  
│______________ arial.ttf           # Шрифт для отображения текста  
├── README.md               # Этот файл  
└── CMakeLists.txt   # Конфигурация сборки  

# Работа программы
![Convex Hull Visualization 2026-03-17 22-40-09](https://github.com/user-attachments/assets/bc005d8e-79a6-4060-bf74-bbb68260ab9a)


### Генерация множества из случайных 20 точек
<img width="1192" height="798" alt="image" src="https://github.com/user-attachments/assets/8fc9734d-f396-49e5-9a6c-d0e135cb5e51" />


### Генерация множества из случайных 50 точек
<img width="1177" height="794" alt="image" src="https://github.com/user-attachments/assets/5ae1005d-de8d-4177-bb27-40f35f0b31a4" />

### Пустое поле после нажатия кнопки "Очистить"
<img width="1180" height="801" alt="image" src="https://github.com/user-attachments/assets/435a347b-f31e-4fc5-b1e8-d6e53ea93783" />

### Режим добавления точек
<img width="1182" height="797" alt="image" src="https://github.com/user-attachments/assets/1470a3bd-0d88-4fdd-8a51-e1ead6245b0c" />

<img width="1189" height="795" alt="image" src="https://github.com/user-attachments/assets/b8a64087-e57a-4550-a08f-4bb94921a270" />

### Пошаговое удаление точек
<img width="1191" height="801" alt="image" src="https://github.com/user-attachments/assets/adaa79ba-3994-4e3f-9489-c883b67be2f6" />

<img width="1181" height="799" alt="image" src="https://github.com/user-attachments/assets/ec4d7e9e-b21a-4a07-8de3-9593c640d89a" />

### Режим изменения координат точки
<img width="1191" height="794" alt="image" src="https://github.com/user-attachments/assets/e7f40806-4c55-4ef7-85fa-0c3fb6c252c2" />

<img width="1178" height="801" alt="image" src="https://github.com/user-attachments/assets/1b57fe77-1b02-4054-8704-edf7386138fb" />

<img width="1188" height="798" alt="image" src="https://github.com/user-attachments/assets/109c66ea-77dc-4004-a50c-e1d297ba6bd8" />
