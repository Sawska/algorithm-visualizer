#ifndef TREEVIZUALIZER_H
#define TREEVIZUALIZER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <tree.h>
#include <string>

class Tree_Vizualizer {
public:
    GLFWwindow* window;

    Tree_Vizualizer() {
        if (!glfwInit()) {
            std::cerr << "ERROR: could not start GLFW3" << std::endl;
            exit(EXIT_FAILURE);
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        window = glfwCreateWindow(640, 480, "OpenGL Initialization Example", NULL, NULL);
        if (!window) {
            std::cerr << "ERROR: could not open window with GLFW3" << std::endl;
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        glfwMakeContextCurrent(window);
        glewExperimental = GL_TRUE;
        glewInit();
        const GLubyte* renderer = glGetString(GL_RENDERER);
        const GLubyte* version = glGetString(GL_VERSION);
        std::cout << "Renderer: " << renderer << std::endl;
        std::cout << "OpenGL version supported " << version << std::endl;
    }

    ~Tree_Vizualizer() {
        glfwTerminate();
    }

    void drawCircle(float x, float y, float radius);
    void drawNameInCircle(float x, float y, float radius,std::string name);
    void drawDiagonalLine(float x1, float y1,float x2, float y2);
    void drawTreeNode(TreeNode node);

};

#endif // TREEVIZUALIZER_H