cmake_minimum_required(VERSION 3.15)
project(pig_repgen_gui)

#  Qt5 Setup
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(SQLiteCpp CONFIG REQUIRED)
find_package(pig_repgen REQUIRED)

# Add the executable (or any other targets)
add_executable(pig_repgen_gui
    mainwindow.ui
    mainwindow.cpp
    main.cpp
    resources.qrc
)

# Link the static library
target_link_libraries(pig_repgen_gui PRIVATE ${PIG_REPGEN_CORE_LIB} Qt5::Widgets SQLiteCpp pig_repgen::pig_repgen_core)
target_compile_features(pig_repgen_gui PRIVATE cxx_std_17)