#include "TreeVisualizer.h"
#include <cmath>
#include <GL/glut.h>
#include <sstream>
const int WHITE = 0xFFFFFF;


int stringToInt(const std::string& str) {
    int value = 0;
    for (char c : str) {
        value += static_cast<int>(c);
    }
    return value;
}

void TreeVizualizer::drawCircle(float x, float y, float radius, int value, int hexCode) {
    int triangleAmount = 40;
    float twicePi = 2.0f * M_PI;

    std::vector<GLfloat> vertices((triangleAmount + 2) * 3);

    
    vertices[0] = x;
    vertices[1] = y;
    vertices[2] = 0.0f;


    for (int i = 1; i <= triangleAmount + 1; i++) {
        vertices[i * 3] = x + (radius * cos(i * twicePi / triangleAmount));
        vertices[i * 3 + 1] = y + (radius * sin(i * twicePi / triangleAmount));
        vertices[i * 3 + 2] = 0.0f;
    }

    GLuint VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    float r, g, b;
    hexToRgb(hexCode, r, g, b);
    glUseProgram(shaderProgram);
    glUniform3f(glGetUniformLocation(shaderProgram, "FragColor"), r, g, b);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, triangleAmount + 2);

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);


    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x - radius / 2, y - radius / 2);
    std::string valStr = std::to_string(value);
    for (char c : valStr) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}



void TreeVizualizer::drawDiagonalLine(float x1, float y1, float x2, float y2) {
    GLfloat vertices[] = {
        x1, y1, 0.0f,
        x2, y2, 0.0f 
    };

    GLuint VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}


void TreeVizualizer::drawTreeNode(TreeNode* node, float x, float y, float xOffset, float yOffset, int hexcode = WHITE) {
    if (!node) return;

    drawCircle(x, y, 0.05f, node->value, hexcode);

    if (node->left) {
        drawDiagonalLine(x, y, x - xOffset, y - yOffset);
        drawTreeNode(node->left, x - xOffset, y - yOffset, xOffset / 2, yOffset, WHITE);
    }

    if (node->right) {
        drawDiagonalLine(x, y, x + xOffset, y - yOffset);
        drawTreeNode(node->right, x + xOffset, y - yOffset, xOffset / 2, yOffset, WHITE);
    }
}

void TreeVizualizer::drawGraph(GraphNode* node, float x, float y, float xOffset, float yOffset,int hexcode) {
    if (!node) return;
    int nodeValue = stringToInt(node->name);
    drawCircle(x, y, 0.05f, nodeValue,hexcode);
    for (const auto& edge : node->edges) {
        GraphNode* neighbor = edge.first.get();
        int weight = edge.second;

        float newX = x + xOffset;
        float newY = y - yOffset;

        drawDiagonalLine(x, y, newX, newY);
        drawGraph(neighbor, newX, newY, xOffset / 2, yOffset,WHITE);
    }
}

void TreeVizualizer::drawLinkedList(LinkedList* list, float x1, float y1, float x2, float y2, float xOffset, float yOffset) {
    if (!list) return;


    drawRectangle(x1, y1, x2, y2,list->value);


    if (list->next != nullptr) {

        float nextX1 = x1 + xOffset;
        float nextY1 = y1;
        float nextX2 = x2 + xOffset;
        float nextY2 = y2;


        drawStraightLine(x2, y2, nextX1, nextY1);


        drawLinkedList(list->next, nextX1, nextY1, nextX2, nextY2, xOffset, yOffset);
    }

}

void TreeVizualizer::drawStack(MYSTACK<int>* stack, float x1, float y1, float x2, float y2, float xOffset, float yOffset) {
    while (!stack->empty()) {
        int topElement = stack->top();


        drawRectangle(x1, y1, x2, y2, topElement);

        stack->pop();


        y1 -= yOffset;
        y2 -= yOffset;
    }
}

void TreeVizualizer::drawStraightLine(float x1, float y1, float x2, float y2) {
    GLfloat vertices[] = {
        x1, y1, 0.0f, 
        x2, y2, 0.0f  
    };

    GLuint VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}


void TreeVizualizer::drawRectangle(float x1, float y1, float x2, float y2, int value) {
    GLfloat vertices[] = {
        x1, y1, 0.0f,  // Bottom-left
        x2, y1, 0.0f,  // Bottom-right
        x2, y2, 0.0f,  // Top-right
        x1, y2, 0.0f   // Top-left
    };

    GLuint indices[] = {
        0, 1, 2,  // First triangle
        0, 2, 3   // Second triangle
    };

    GLuint VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);


    glColor3f(0.0f, 0.0f, 0.0f); 
    glRasterPos2f((x1 + x2) / 2 - 10, (y1 + y2) / 2);
    std::string valStr = std::to_string(value);
    for (char c : valStr) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}



void TreeVizualizer::hexToRgb(int hexValue, float& r, float& g, float& b) {
    g = ((hexValue >> 8) & 0xFF) / 255.0f;
    r = ((hexValue >> 16) & 0xFF) / 255.0f;
    b = (hexValue & 0xFF) / 255.0f;
}
