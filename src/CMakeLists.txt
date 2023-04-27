cmake_minimum_required(VERSION 3.26.3)
project(desktop-engine)

set(CORE_DIR ${PROJECT_SOURCE_DIR}/Core/)



add_executable(${PROJECT_NAME} ;
  main.cpp;
  
)

add_subdirectory(${CORE_DIR}/Engine/)
add_subdirectory(${CORE_DIR}/Math/)
add_subdirectory(${CORE_DIR}/OpenGL/)
add_subdirectory(${CORE_DIR}/Windowing/)


target_include_directories(${PROJECT_NAME} PRIVATE ${CORE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CORE_DIR}/Engine/)
target_include_directories(${PROJECT_NAME} PRIVATE ${CORE_DIR}/Math/)
target_include_directories(${PROJECT_NAME} PRIVATE ${CORE_DIR}/OpenGL/)
target_include_directories(${PROJECT_NAME} PRIVATE ${CORE_DIR}/Windowing/)
target_include_directories(${PROJECT_NAME} PUBLIC /usr/include/)


target_link_directories(${PROJECT_NAME} PRIVATE /usr/lib/)
target_link_libraries(${PROJECT_NAME} xcb X11 X11-xcb GL GLEW assimp)