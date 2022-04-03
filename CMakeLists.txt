cmake_minimum_required(VERSION 3.16)

project(PendulumSimulation)

# Windows specific config
IF (WIN32)
    # Include local sfml cmake config
    set(SFML_DIR "E:/Programmieren/c++/projects-gitHub/SFML/pendulum-simulation1/SFML-2.5.1/lib/cmake/SFML")
    # Link sfml statically (Optional)
    set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

file(GLOB_RECURSE SCRS_FILES "src/*.cpp" "src/*.hpp" "src/*.h" "src/*.c")

add_executable(PendulumSimulation ${SCRS_FILES})

target_link_libraries(PendulumSimulation sfml-graphics sfml-window sfml-system)

target_include_directories(PendulumSimulation
    PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)