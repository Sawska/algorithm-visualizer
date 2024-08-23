cmake_minimum_required(VERSION 3.13)

project(algorithm_visualizer)
find_package(OpenGL REQUIRED)
link_directories(${OPENGL_gl_LIBRARY})
set(CMAKE_CXX_STANDARD 14)


set(SOURCE_FILES 
    graph.cpp
    LinkedList.cpp
    MyStack.cpp
    tree.cpp
)


add_executable(simple_example ${SOURCE_FILES} ${OPENGL_gl_LIBRARY})
