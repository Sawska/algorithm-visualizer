#include <TreeVisualizer.h>
#include <cmath>
#include <GL/glut.h>
#include <sstream>


int stringToInt(const std::string& str) {
    int value = 0;
    for (char c : str) {
        value += static_cast<int>(c);
    }
    return value;
}

void Tree_Vizualizer::drawCircle(float x, float y, float radius, int value) {
    int triangleAmount = 40;
    float twicePi = 2.0f * M_PI;

    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(238, 139, 21); 
    glVertex2f(x, y); 
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();


    glRasterPos2f(x - radius / 2, y - radius / 2);
    std::string valStr = std::to_string(value);
    for (char c : valStr) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}

void Tree_Vizualizer::drawDiagonalLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void Tree_Vizualizer::drawTreeNode(TreeNode* node, float x, float y, float xOffset, float yOffset) {
    if (!node) return;

    drawCircle(x, y, 0.05f, node->value);

    if (node->left) {
        drawDiagonalLine(x, y, x - xOffset, y - yOffset);
        drawTreeNode(node->left, x - xOffset, y - yOffset, xOffset / 2, yOffset);
    }

    if (node->right) {
        drawDiagonalLine(x, y, x + xOffset, y - yOffset);
        drawTreeNode(node->right, x + xOffset, y - yOffset, xOffset / 2, yOffset);
    }
}

void Tree_Vizualizer::drawGraph(GraphNode* node, float x, float y, float xOffset, float yOffset) {
    if (!node) return;

    
    int nodeValue = stringToInt(node->name);

    
    drawCircle(x, y, 0.05f, nodeValue);


    for (const auto& edge : node->edges) {
        GraphNode* neighbor = edge.first;
        int weight = edge.second; 

        float newX = x + xOffset;
        float newY = y - yOffset;

        drawDiagonalLine(x, y, newX, newY);
        drawGraph(neighbor, newX, newY, xOffset / 2, yOffset);
    }
}

void Tree_Vizualizer::drawLinkedList(LinkedList* list, float x1, float y1, float x2, float y2, float xOffset, float yOffset) {
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

void Tree_Vizualizer::drawStack(MYSTACK<int>* stack, float x1, float y1, float x2, float y2, float xOffset, float yOffset) {    
    while (!stack->empty()) { 
        int topElement = stack->top(); 
        
        
        drawRectangle(x1, y1, x2, y2, xOffset, yOffset, topElement);
        
        stack->pop();


        y1 -= yOffset;
        y2 -= yOffset;
    }
}

void Tree_Vizualizer::drawStraightLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);  
    glVertex2f(x2, y2);  
    glEnd();
}

void Tree_Vizualizer::drawRectangle(float x1, float y1, float x2, float y2, float xOffset, float yOffset, int value) {

    glBegin(GL_QUADS);
    glVertex2f(x1, y1); 
    glVertex2f(x2, y1); 
    glVertex2f(x2, y2); 
    glVertex2f(x1, y2); 
    glEnd();


    glRasterPos2f((x1 + x2) / 2 - 10, (y1 + y2) / 2); // Adjust position based on text size


    std::string valStr = std::to_string(value);
    for (char c : valStr) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}
