#ifndef TREEVIZUALIZER_H
#define TREEVIZUALIZER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "tree.h"
#include "LinkedList.h"
#include "graph.h"
#include "MyStack.h"
#include "TreeVisualizer.h"
#include "LinkedList.h"
#include "MyStack.h"
#include "tree.h"
#include "graph.h"
#include <cmath>
#include <GL/glut.h>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include <map>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

class GraphNode;
class TreeNode;

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
    gl_Position = vec4(aPos, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0, 1.0, 1.0, 1.0); // White color
}
)";



class Shader {
public:
    unsigned int Program;

    Shader(const char* vertexPath, const char* fragmentPath) {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            vShaderFile.close();
            fShaderFile.close();
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        } catch (std::ifstream::failure& e) {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        Program = glCreateProgram();
        glAttachShader(Program, vertex);
        glAttachShader(Program, fragment);
        glLinkProgram(Program);
        glGetProgramiv(Program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(Program, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Use() {
        glUseProgram(Program);
    }
};

struct Character {
    unsigned int TextureID; 
    glm::ivec2 Size;        
    glm::ivec2 Bearing;     
    unsigned int Advance;   
};

class TreeVizualizer {
public:
    GLFWwindow* window;
    GLuint shaderProgram;
    GLuint VAO;
    GLuint VBO;
    Shader textShader;
    std::map<char, Character> Characters;

    TreeVizualizer() : textShader("/path/to/text_vertex_shader.vs", "/path/to/text_fragment_shader.fs") {
        if (!glfwInit()) {
            std::cerr << "ERROR: could not start GLFW3" << std::endl;
            exit(EXIT_FAILURE);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(1920, 1080, "Tree Visualizer", NULL, NULL);
        if (!window) {
            std::cerr << "ERROR: could not open window with GLFW3" << std::endl;
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window);
        glewExperimental = GL_TRUE;
        GLenum glewInitResult = glewInit();
        if (glewInitResult != GLEW_OK) {
            std::cerr << "ERROR: could not initialize GLEW: " << glewGetErrorString(glewInitResult) << std::endl;
            glfwDestroyWindow(window);
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        const GLubyte* renderer = glGetString(GL_RENDERER);
        const GLubyte* version = glGetString(GL_VERSION);
        std::cout << "Renderer: " << renderer << std::endl;
        std::cout << "OpenGL version supported: " << version << std::endl;

        glViewport(0, 0, 1920, 1080);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        checkShaderCompileErrors(vertexShader, "VERTEX");

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        checkShaderCompileErrors(fragmentShader, "FRAGMENT");

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        checkProgramLinkErrors(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        
        FT_Library ft;
        if (FT_Init_FreeType(&ft)) {
            std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
            exit(EXIT_FAILURE);
        }

        FT_Face face;
        if (FT_New_Face(ft, "/System/Library/Fonts/Supplemental/Arial.ttf", 0, &face)) {
            std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;
            exit(EXIT_FAILURE);
        }

        FT_Set_Pixel_Sizes(face, 0, 48);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        for (unsigned int c = 0; c < 256; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cerr << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
                continue;
            }

            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters.insert(std::make_pair(c, character));
        }
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }


    ~TreeVizualizer() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteProgram(shaderProgram);
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void drawTriangle() {
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }


    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
    void drawCircle(float x, float y, float radius, int value, int hexcode);
    void drawDiagonalLine(float x1, float y1, float x2, float y2);
    void drawTreeNode(TreeNode* node, float x, float y, float xOffset, float yOffset, int hexcode);
    void drawGraph(GraphNode* node, float x, float y, float xOffset, float yOffset, int hexcode);
    void drawLinkedList(LinkedList* list, float x1, float y1, float x2, float y2, float xOffset, float yOffset);
    void drawRectangle(float x1, float y1, float x2, float y2, int value);
    void drawStraightLine(float x1, float y1, float x2, float y2);
    void drawStack(MYSTACK<int>* stack, float x1, float y1, float x2, float y2, float xOffset, float yOffset);
    void hexToRgb(int hexValue, float& r, float& g, float& b);
    void output(int x, int y, float r, float g, float b, void* font, const char* string);
    void getRandomColor(float& r, float& g, float& b);
    float getRandomFloat();
    void initializeRandomColorGenerator();
    void delay(float seconds);

private:
    void checkShaderCompileErrors(GLuint shader, std::string type) {
        int success;
        char infoLog[512];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 512, NULL, infoLog);
                std::cerr << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 512, NULL, infoLog);
                std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            }
        }
    }

    void checkProgramLinkErrors(GLuint program) {
        GLint success;
        GLchar infoLog[512];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(program, 512, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }
};

#endif // TREEVIZUALIZER_H
