#include "TreeVisualizer.h"
#include <cmath>
#include <GL/glut.h>
#include <sstream>
#include <cstdlib>  
#include <ctime>    
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
    GLint colorLocation = glGetUniformLocation(shaderProgram, "uColor");
    if (colorLocation != -1) {
        glUniform3f(colorLocation, r, g, b);
    } else {
        std::cerr << "ERROR: Could not find uniform location for uColor" << std::endl;
    }


    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, triangleAmount + 2);

    glBindVertexArray(0);
    glUseProgram(0);

    std::string valStr = std::to_string(value);
    // RenderText(valStr, x - radius / 2, y - radius / 2, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);


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
    glfwSwapBuffers(window);
    delay(0.5f);

    if (node->left) {
        drawDiagonalLine(x, y, x - xOffset, y - yOffset);
        glfwSwapBuffers(window);
        delay(0.5f);
        drawTreeNode(node->left, x - xOffset, y - yOffset, xOffset / 2, yOffset, WHITE);
        glfwSwapBuffers(window);
        delay(0.5f);
    }

    if (node->right) {
        drawDiagonalLine(x, y, x + xOffset, y - yOffset);
        glfwSwapBuffers(window);
        delay(0.5f);
        drawTreeNode(node->right, x + xOffset, y - yOffset, xOffset / 2, yOffset, WHITE);
    }
}

void TreeVizualizer::drawGraph(GraphNode* node, float x, float y, float xOffset, float yOffset,int hexcode) {
    if (!node) return;
    int nodeValue = stringToInt(node->name);
    drawCircle(x, y, 0.05f, nodeValue,hexcode);
    glfwSwapBuffers(window);
    delay(0.5f);
    for (const auto& edge : node->edges) {
        GraphNode* neighbor = edge.first.get();
        int weight = edge.second;

        float newX = x + xOffset;
        float newY = y - yOffset;

        drawDiagonalLine(x, y, newX, newY);
        glfwSwapBuffers(window);
        delay(0.5f);
        drawGraph(neighbor, newX, newY, xOffset / 2, yOffset,WHITE);
        glfwSwapBuffers(window);
        delay(0.5f);
    }
}

void TreeVizualizer::drawLinkedList(LinkedList* list, float x1, float y1, float x2, float y2, float xOffset, float yOffset) {
    if (!list) return;


    drawRectangle(x1, y1, x2, y2, list->value);
    glfwSwapBuffers(window);
    delay(2.0f);

    if (list->next != nullptr) {

        float nextX1 = x1 + xOffset;
        float nextY1 = y1;
        float nextX2 = x2 + xOffset;
        float nextY2 = y2;


        float midY = (y1 + y2) / 2.0f;

        drawStraightLine(x2, midY, nextX1, midY);
         glfwSwapBuffers(window);
            delay(0.5f);


        drawLinkedList(list->next, nextX1, nextY1, nextX2, nextY2, xOffset, yOffset);
    }
}


void TreeVizualizer::drawStack(MYSTACK<int>* stack, float x1, float y1, float x2, float y2, float xOffset, float yOffset) {
    MYSTACK<int> tempStack = *stack;  

    while (!tempStack.empty()) {
        
        int topElement = tempStack.top();
        tempStack.pop();

        
        drawRectangle(x1, y1, x2, y2, topElement);
        glfwSwapBuffers(window);
        delay(0.5f);
        
        y1 += yOffset; 
        y2 += yOffset; 
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



void TreeVizualizer::output(int x, int y, float r, float g, float b, void* font, const char* string) {
    glColor3f(r, g, b);  
    glRasterPos2f(x, y);

    int len = (int)strlen(string);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(font, string[i]);  
    }
}

void TreeVizualizer::drawRectangle(float x1, float y1, float x2, float y2, int value) {
    GLfloat vertices[] = {
        x1, y1, 0.0f,
        x2, y1, 0.0f, 
        x2, y2, 0.0f, 
        x1, y2, 0.0f  
    };

    GLuint indices[] = {
        0, 1, 2,  
        0, 2, 3   
    };

    GLuint VBO, EBO, VAO;
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

    
     float r, g, b;
    getRandomColor(r, g, b);

    glUseProgram(shaderProgram);
    
    
    GLint colorLoc = glGetUniformLocation(shaderProgram, "uColor");
    glUniform3f(colorLoc, r, g, b);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glUseProgram(0);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);

    float textX = x1 + (x2 - x1) / 2 - 10;
    float textY = y1 + (y2 - y1) / 2 + 5;

    std::string valStr = std::to_string(value);
    output(textX, textY, 0.0f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, valStr.c_str());
}






void TreeVizualizer::initializeRandomColorGenerator() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}


float TreeVizualizer::getRandomFloat() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}


void TreeVizualizer::getRandomColor(float& r, float& g, float& b) {
    r = getRandomFloat();
    g = getRandomFloat();
    b = getRandomFloat();
}






void TreeVizualizer::hexToRgb(int hexValue, float& r, float& g, float& b) {
    g = ((hexValue >> 8) & 0xFF) / 255.0f;
    r = ((hexValue >> 16) & 0xFF) / 255.0f;
    b = (hexValue & 0xFF) / 255.0f;
}



void TreeVizualizer::delay(float seconds) {
    glfwWaitEventsTimeout(seconds);
}