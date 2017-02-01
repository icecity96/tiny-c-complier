cmake_minimum_required(VERSION 3.6)
project(ch03)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/failure-function.cpp src/failure_function.h src/catch_main.hpp)

set(LEXER_FILES
        src/lexer.cpp src/lexer.hpp src/catch_main.hpp)

set(QTVIEW_FILES
        src/mainwindow.h src/mainwindow.cpp src/mainview.cpp)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH /usr/local/opt/qt5)
#open QT MOC and process UI
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5Widgets)
find_package(Qt5Core)

QT5_WRAP_UI(FORMS_UIC ${FORMS})

add_executable(failure_function ${SOURCE_FILES})

add_executable(lexer ${LEXER_FILES})

add_executable(graph-view ${QTVIEW_FILES})

target_link_libraries(graph-view Qt5::Widgets)

