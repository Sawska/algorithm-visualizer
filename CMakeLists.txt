cmake_minimum_required(VERSION 3.13)

project(algorithm_visualizer)


set(CMAKE_CXX_STANDARD 14)


find_package(OpenGL REQUIRED)


include_directories(/opt/homebrew/Cellar/freeglut/3.6.0/include)
include_directories(/opt/homebrew/Cellar/glfw/3.4/include)
include_directories(/opt/homebrew/Cellar/glew/2.2.0_1/include)


link_directories(/opt/homebrew/Cellar/freeglut/3.6.0/lib)
link_directories(/opt/homebrew/Cellar/glfw/3.4/lib)
link_directories(/opt/homebrew/Cellar/glew/2.2.0_1/lib)


set(SOURCE_FILES 
    graph.cpp
    LinkedList.cpp
    MyStack.cpp
    tree.cpp
    main.cpp 
)


add_executable(algorithm_visualizer ${SOURCE_FILES})


target_link_libraries(algorithm_visualizer 
    ${OPENGL_LIBRARIES}
    glut
    GLU
    GL
    glfw
    GLEW
)
