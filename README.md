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
    Convex-Hull.cpp Point.cpp GameState.cpp Renderer.cpp ^
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
├── Convex-Hull.cpp              # Точка входа, игровой цикл  
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



### Генерация множества из случайных 20 точек
![Convex Hull Visualization 2026-03-17 22-40-09](https://github.com/user-attachments/assets/305ee6ab-3181-4dba-af2b-d91184ee0873)



### Генерация множества из случайных 50 точек
<img width="1180" height="794" alt="image" src="https://github.com/user-attachments/assets/67b65275-5435-43c2-9df9-0c7587548543" />


### Пустое поле после нажатия кнопки "Очистить"
<img width="1181" height="793" alt="image" src="https://github.com/user-attachments/assets/6fcb262e-7d5a-49df-a17f-d92f6c78969a" />


### Режим добавления точек
<img width="1188" height="800" alt="image" src="https://github.com/user-attachments/assets/0e368f1b-5034-4b45-ae5e-14b84fab4f2f" />


<img width="1188" height="799" alt="image" src="https://github.com/user-attachments/assets/f560951e-08a4-4c04-b24d-4f14dc787969" />


### Пошаговое удаление точек
<img width="1184" height="794" alt="image" src="https://github.com/user-attachments/assets/17dbee04-b259-42c3-99a8-56b816e81e09" />


<img width="1177" height="792" alt="image" src="https://github.com/user-attachments/assets/6d264011-be4e-4ee1-86de-5cb923f25d5d" />


### Режим изменения координат точки
<img width="1190" height="806" alt="image" src="https://github.com/user-attachments/assets/b907153a-b7aa-4c31-ace4-e4cf14304fcc" />

<img width="1176" height="796" alt="image" src="https://github.com/user-attachments/assets/ef9913ce-767f-4d44-bf7f-d9a5482426cd" />

<img width="1185" height="791" alt="image" src="https://github.com/user-attachments/assets/04497640-d5ca-4699-a3c9-8f3583bf6231" />


