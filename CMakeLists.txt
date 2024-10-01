cmake_minimum_required(VERSION 3.15)
project(pig_repgen_gui)

#  Qt5 Setup
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Find the library
find_library(PIG_REPGEN_CORE_LIB NAMES pig_repgen_core
             PATHS "${PIG_REPGEN_INSTALL_PREFIX}/lib"
             NO_DEFAULT_PATH
)

# Find the headers
find_path(PIG_REPGEN_CORE_INCLUDE_DIR NAMES repgen/repgen.h db.h
          PATHS "${PIG_REPGEN_INSTALL_PREFIX}/include"
)

# Check if the library and headers were found
if (NOT PIG_REPGEN_CORE_LIB OR NOT PIG_REPGEN_CORE_INCLUDE_DIR)
    message(FATAL_ERROR "Could not find pig_repgen_core library or headers")
endif()

# Add include directories
include_directories(${PIG_REPGEN_CORE_INCLUDE_DIR})

# Find SQLitecpp library
find_package(SQLiteCpp CONFIG REQUIRED)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# Add the executable (or any other targets)
add_executable(pig_repgen_gui
    mainwindow.ui
    mainwindow.cpp
    main.cpp
    resources.qrc
)

# Link the static library
target_link_libraries(pig_repgen_gui PRIVATE ${PIG_REPGEN_CORE_LIB} Qt5::Widgets SQLiteCpp)
target_compile_features(pig_repgen_gui PRIVATE cxx_std_17)