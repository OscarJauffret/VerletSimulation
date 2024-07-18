cmake_minimum_required(VERSION 3.28)
project(VerletSimulation)

set(CMAKE_CXX_STANDARD 20)

add_executable(VerletSimulation src/main.cpp
        src/sim/headers/verletobject.hpp
        src/sim/solver.cpp
        src/sim/headers/solver.hpp
        src/config.hpp
        src/renderer.hpp
        src/sim/solverutils.cpp
        src/rng/rng.cpp
)

set(CMAKE_PREFIX_PATH "C:/SFML-2.6.1")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)