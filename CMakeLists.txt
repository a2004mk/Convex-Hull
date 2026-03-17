cmake_minimum_required(VERSION 3.16)
project(ConvexHullVisualization LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ==================== SFML ====================
find_package(SFML 3.0 COMPONENTS graphics window system REQUIRED)

# ==================== Исходные файлы ====================
set(SOURCES
    "src/Convex-Hull.cpp"           # ← main() здесь (с дефисом!)
    src/Button.cpp
    src/ConvexHull.cpp              # ← алгоритм (слитно)
    src/EditPointWindow.cpp
    src/GameState.cpp
    src/InputField.cpp
    src/InputHandler.cpp
    src/Point.cpp
    src/Renderer.cpp
)

set(HEADERS
    src/Button.h
    src/ConvexHull.h                # ← заголовок алгоритма
    src/EditPointWindow.h
    src/GameState.h
    src/InputField.h
    src/InputHandler.h
    src/Point.h
    src/Renderer.h
)

# ==================== Исполняемый файл ====================
# Имя целевого файла без дефисов (чтобы избежать проблем на некоторых платформах)
add_executable(ConvexHullApp ${SOURCES} ${HEADERS})
set_target_properties(ConvexHullApp PROPERTIES
    OUTPUT_NAME "Convex-Hull"       # ← имя .exe будет Convex-Hull (с дефисом)
)

# ==================== Линковка ====================
if(TARGET sfml-graphics)
    target_link_libraries(ConvexHullApp PRIVATE sfml-graphics sfml-window sfml-system)
else()
    target_link_libraries(ConvexHullApp PRIVATE SFML::Graphics SFML::Window SFML::System)
endif()

# ==================== Платформенные настройки ====================
if(WIN32)
    target_compile_definitions(ConvexHullApp PRIVATE UNICODE _UNICODE NOMINMAX)
    
    # Копирование ресурсов при сборке
    add_custom_command(TARGET ConvexHullApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:ConvexHullApp>/resources
        COMMENT "Copying resources to build directory"
    )
endif()

if(UNIX AND NOT APPLE)
    find_package(Threads REQUIRED)
    target_link_libraries(ConvexHullApp PRIVATE Threads::Threads)
endif()

if(APPLE)
    target_link_libraries(ConvexHullApp PRIVATE "-framework Cocoa" "-framework IOKit")
endif()

# ==================== Include directories ====================
target_include_directories(ConvexHullApp PRIVATE ${CMAKE_SOURCE_DIR}/src)

# ==================== Ресурсы ====================
file(GLOB RESOURCE_FILES resources/*)
add_custom_target(resources DEPENDS ${RESOURCE_FILES})
add_dependencies(ConvexHullApp resources)