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


    float r, g, b;
    hexToRgb(hexCode, r, g, b);

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(r, g, b); 
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    
    glColor3f(1.0f, 1.0f, 1.0f); 
    glRasterPos2f(x - radius / 2, y - radius / 2);
    std::string valStr = std::to_string(value);
    for (char c : valStr) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}


void TreeVizualizer::drawDiagonalLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
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
        GraphNode* neighbor = edge.first;
        int weight = edge.second; 

        float newX = x + xOffset;
        float newY = y - yOffset;

        drawDiagonalLine(x, y, newX, newY);
        drawGraph(neighbor, newX, newY, xOffset / 2, yOffset,WHITE);
    }
}

void TreeVizualizer::drawLinkedList(LinkedList* list, float x1, float y1, float x2, float y2, float xOffset, float yOffset) {
    if (!list) return;


    drawRectangle(x1, y1, x2, y2, xOffset, yOffset,list->value);


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
        
        
        drawRectangle(x1, y1, x2, y2, xOffset, yOffset, topElement);
        
        stack->pop();


        y1 -= yOffset;
        y2 -= yOffset;
    }
}

void TreeVizualizer::drawStraightLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);  
    glVertex2f(x2, y2);  
    glEnd();
}

void TreeVizualizer::drawRectangle(float x1, float y1, float x2, float y2, float xOffset, float yOffset, int value) {

    glBegin(GL_QUADS);
    glVertex2f(x1, y1); 
    glVertex2f(x2, y1); 
    glVertex2f(x2, y2); 
    glVertex2f(x1, y2); 
    glEnd();


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
