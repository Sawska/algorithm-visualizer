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





const int WHITE = 0xFFFFFF;

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>





void linked_show(TreeVizualizer& visualizer) {
    LinkedList list = LinkedList(0);
    
    float x1 = -0.9f, y1 = -0.1f; 
    float x2 = -0.7f, y2 = 0.0f;  
    float xOffset = 0.3f;         
    float yOffset = 0.0f;         

    visualizer.drawLinkedList(&list, x1, y1, x2, y2, xOffset, yOffset);
    glfwSwapBuffers(visualizer.window);
    visualizer.delay(1.0f);

    list.add(0, &list);
    visualizer.drawLinkedList(&list, x1, y1, x2, y2, xOffset, yOffset);
    glfwSwapBuffers(visualizer.window);
    visualizer.delay(1.0f);

    list.add(1, &list);
    visualizer.drawLinkedList(&list, x1, y1, x2, y2, xOffset, yOffset);
    glfwSwapBuffers(visualizer.window);
    visualizer.delay(1.0f);

    list.add(2, &list);
    visualizer.drawLinkedList(&list, x1, y1, x2, y2, xOffset, yOffset);
    glfwSwapBuffers(visualizer.window);
    visualizer.delay(1.0f);

    list.add(3, &list);
    visualizer.drawLinkedList(&list, x1, y1, x2, y2, xOffset, yOffset);
    glfwSwapBuffers(visualizer.window);
    visualizer.delay(1.0f);

    list.remove(1, &list);
    visualizer.drawLinkedList(&list, x1, y1, x2, y2, xOffset, yOffset);
    glfwSwapBuffers(visualizer.window);
    visualizer.delay(1.0f);

    list.add(3, &list);
    visualizer.drawLinkedList(&list, x1, y1, x2, y2, xOffset, yOffset);
    glfwSwapBuffers(visualizer.window);
    visualizer.delay(1.0f);

}



void show_stack(TreeVizualizer& visualizer) {
    MYSTACK<int> stack;

    float x1 = -0.9f, y1 = 0.9f;
    float x2 = -0.7f, y2 = 0.8f;
    float xOffset = 0.0f;       
    float yOffset = -0.1f;      

    stack.push(1);
    glfwSwapBuffers(visualizer.window);
    visualizer.delay(1.0f);
    visualizer.drawStack(&stack, x1, y1, x2, y2, xOffset, yOffset);
    stack.push(2);
    visualizer.drawStack(&stack, x1, y1, x2, y2, xOffset, yOffset);
    glfwSwapBuffers(visualizer.window);
    visualizer.delay(1.0f);
    stack.push(3);
    visualizer.drawStack(&stack, x1, y1, x2, y2, xOffset, yOffset);
    glfwSwapBuffers(visualizer.window);
    visualizer.delay(1.0f);
    stack.push(4);
    visualizer.delay(1.0f);
    visualizer.drawStack(&stack, x1, y1, x2, y2, xOffset, yOffset);
    glfwSwapBuffers(visualizer.window);

    while (stack.size() != 0) {
        stack.pop();
        visualizer.drawStack(&stack, x1, y1, x2, y2, xOffset, yOffset);
        glfwSwapBuffers(visualizer.window);
        visualizer.delay(1.0f);
    }
}




void show_tree(TreeVizualizer& visualizer) {

    float x2 = 0.3f, y2 = 0.3f;
    float x1 = -0.1f, y1 = -0.1f;
    TreeNode* root = new TreeNode(1);
    visualizer.drawTreeNode(root,x1,y1,x2,y2,WHITE);
    glfwSwapBuffers(visualizer.window);
    visualizer.delay(1.0f);
    root->left = new TreeNode(2);
    visualizer.drawTreeNode(root,x1,y1,x2,y2,WHITE);
    glfwSwapBuffers(visualizer.window);
    visualizer.delay(1.0f);
    root->right = new TreeNode(3);
    visualizer.drawTreeNode(root,x1,y1,x2,y2,WHITE);
    glfwSwapBuffers(visualizer.window);
    visualizer.delay(1.0f);
    root->left->left = new TreeNode(4);
    visualizer.drawTreeNode(root,x1,y1,x2,y2,WHITE);
    glfwSwapBuffers(visualizer.window);
    visualizer.delay(1.0f);
    root->left->right = new TreeNode(5);
    visualizer.drawTreeNode(root,x1,y1,x2,y2,WHITE);
    glfwSwapBuffers(visualizer.window);
    visualizer.delay(1.0f);
    
    // bool found = root->DFS(4, root, visualizer, true);
}

void show_graph(TreeVizualizer& visualizer) {
    auto node = std::make_unique<GraphNode>("a", 2);
    auto node1 = std::make_unique<GraphNode>("b", 3);
    auto node2 = std::make_unique<GraphNode>("c", 4);
    auto node3 = std::make_unique<GraphNode>("d", 5);


    float x1 = -0.1f, y1 = -0.1f;
    float x2 = 0.1f, y2 = 0.1f;

    visualizer.drawGraph(node.get(), x1, y1, x2, y2, WHITE);
    glfwSwapBuffers(visualizer.window);
    visualizer.delay(1.0f);
    node->insert_node(std::move(node1));
    visualizer.drawGraph(node.get(), x1, y1, x2, y2, WHITE);
    glfwSwapBuffers(visualizer.window);
    visualizer.delay(1.0f);

    node->insert_node(std::move(node2));
    visualizer.drawGraph(node.get(), x1, y1, x2, y2, WHITE);
    glfwSwapBuffers(visualizer.window);
    visualizer.delay(1.0f);

    node->insert_node(std::move(node3));
    visualizer.drawGraph(node.get(), x1, y1, x2, y2, WHITE);
    glfwSwapBuffers(visualizer.window);
    visualizer.delay(1.0f);

    // node->dijkstra(node.get(), node3.get(), &visualizer);
}




int main() {
    TreeVizualizer visualizer;

    
    int width, height;
    glfwGetFramebufferSize(visualizer.window, &width, &height);
    glViewport(0, 0, width, height);

    while (!glfwWindowShouldClose(visualizer.window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
        glUseProgram(visualizer.shaderProgram);

    
        show_graph(visualizer);

    
        glBindVertexArray(visualizer.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

    
        glfwSwapBuffers(visualizer.window);
        glfwPollEvents();
    }

    
    glfwDestroyWindow(visualizer.window);
    glfwTerminate();

    return 0;
}
