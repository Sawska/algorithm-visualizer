cmake_minimum_required(VERSION 3.13)

project(algorithm_visualizer)

set(CMAKE_CXX_STANDARD 14)

if(APPLE)
    add_definitions(-Wno-deprecated-declarations)
endif()


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(Freetype REQUIRED)

if(APPLE)
    set(OPENGL_LIBRARIES "-framework OpenGL")
    set(GLUT_LIBRARIES "-framework GLUT")
else()
    find_package(GLEW REQUIRED)
    set(LIBRARIES ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES})
endif()


include_directories(/opt/homebrew/Cellar/freeglut/3.6.0/include)
include_directories(/opt/homebrew/Cellar/glfw/3.4/include)
include_directories(/opt/homebrew/Cellar/glew/2.2.0_1/include)
include_directories(/opt/homebrew/Cellar/glm/1.0.1/include/glm)
include_directories(${FREETYPE_INCLUDE_DIRS})


link_directories(/opt/homebrew/Cellar/freeglut/3.6.0/lib)
link_directories(/opt/homebrew/Cellar/glfw/3.4/lib)
link_directories(/opt/homebrew/Cellar/glew/2.2.0_1/lib)
link_directories(/opt/homebrew/Cellar/glm/1.0.1/lib)


file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)


add_executable(algorithm_visualizer ${SOURCE_FILES})


target_link_libraries(algorithm_visualizer 
    ${OPENGL_LIBRARIES} 
    ${GLUT_LIBRARIES}
    glfw
    GLEW
    ${FREETYPE_LIBRARIES}
)
