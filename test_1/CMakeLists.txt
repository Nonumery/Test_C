cmake_minimum_required(VERSION 3.14)

project(test_1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Network Core Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network Core REQUIRED)

add_executable(test_1
  main.cpp
)
target_link_libraries(test_1 Qt${QT_VERSION_MAJOR}::Core Qt5::Network)
