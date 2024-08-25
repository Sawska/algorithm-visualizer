#ifndef TREEVIZUALIZER_H
#define TREEVIZUALIZER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include "tree.h"
#include "LinkedList.h"
#include "graph.h"
#include "MyStack.h"


class GraphNode;
class TreeNode;

class TreeVizualizer {
public:
    GLFWwindow* window;

    TreeVizualizer() {
        if (!glfwInit()) {
            std::cerr << "ERROR: could not start GLFW3" << std::endl;
            exit(EXIT_FAILURE);
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        window = glfwCreateWindow(640, 480, "Tree Visualizer", NULL, NULL);
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

    ~TreeVizualizer() {
        glfwTerminate();
    }

    void drawCircle(float x, float y, float radius, int value, int hexcode);
    void drawDiagonalLine(float x1, float y1, float x2, float y2);
    void drawTreeNode(TreeNode* node, float x, float y, float xOffset, float yOffset, int hexcode);
    void drawGraph(GraphNode* node, float x, float y, float xOffset, float yOffset, int hexcode);
    void drawLinkedList(LinkedList* list, float x1, float y1, float x2, float y2, float xOffset, float yOffset);
    void drawRectangle(float x1, float y1, float x2, float y2, float xOffset, float yOffset, int value);
    void drawStraightLine(float x1, float y1, float x2, float y2);
    void drawStack(MYSTACK<int>* stack, float x1, float y1, float x2, float y2, float xOffset, float yOffset);
    void hexToRgb(int hexValue, float& r, float& g, float& b);
};

#endif // TREEVIZUALIZER_H
