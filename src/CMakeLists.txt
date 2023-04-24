cmake_minimum_required(VERSION 3.26.3)
project(desktop-engine)

add_executable(${PROJECT_NAME} 
  main.cpp
  Core/XWindow.cpp
  Core/OpenGL/GLObject.cpp
  Core/OpenGL/GLBufferObject.cpp
  Core/OpenGL/IndexBuffer.cpp
  Core/OpenGL/Shader.cpp
  Core/OpenGL/ShaderProgram.cpp
  Core/OpenGL/VertexBuffer.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC /usr/include/)
target_link_directories(${PROJECT_NAME} PRIVATE /usr/lib/)

target_link_libraries(${PROJECT_NAME} xcb X11 X11-xcb GL GLEW)