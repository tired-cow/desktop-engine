cmake_minimum_required(VERSION 3.26.3)

project(desktop-engine)

add_executable(${PROJECT_NAME} main.cpp XWindow.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC /usr/include/)
target_link_directories(${PROJECT_NAME} PRIVATE /usr/lib/)

target_link_libraries(${PROJECT_NAME} xcb X11 X11-xcb GL GLEW)