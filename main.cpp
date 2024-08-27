#include "TreeVisualizer.h"
#include "LinkedList.h"
#include "MyStack.h"
#include "tree.h"
#include "graph.h"
#include <cmath>
#include <GL/glut.h>
#include <sstream>



const int WHITE = 0xFFFFFF;


void linked_show(TreeVizualizer& visualizer) {
    LinkedList list = LinkedList(0);
    
    float x1 = -0.9f, y1 = -0.1f; 
    float x2 = -0.7f, y2 = 0.0f;  
    float xOffset = 0.3f;         
    float yOffset = 0.0f;         

    visualizer.drawLinkedList(&list, x1, y1, x2, y2, xOffset, yOffset);
    list.add(0, &list);
    visualizer.drawLinkedList(&list, x1, y1, x2, y2, xOffset, yOffset);
    list.add(1, &list);
    visualizer.drawLinkedList(&list, x1, y1, x2, y2, xOffset, yOffset);
    list.add(2, &list);
    visualizer.drawLinkedList(&list, x1, y1, x2, y2, xOffset, yOffset);
    list.add(3, &list);
    visualizer.drawLinkedList(&list, x1, y1, x2, y2, xOffset, yOffset);
    list.remove(1, &list);
    visualizer.drawLinkedList(&list, x1, y1, x2, y2, xOffset, yOffset);
    list.add(3, &list);
    visualizer.drawLinkedList(&list, x1, y1, x2, y2, xOffset, yOffset);
}




void show_stack(TreeVizualizer& visualizer) {
    MYSTACK<int> stack;

    float x1 = -0.9f, y1 = 0.9f;
    float x2 = -0.7f, y2 = 0.8f;
    float xOffset = 0.0f;       
    float yOffset = -0.1f;      

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    visualizer.drawStack(&stack, x1, y1, x2, y2, xOffset, yOffset);

    while (stack.size() != 0) {
        stack.pop();
        visualizer.drawStack(&stack, x1, y1, x2, y2, xOffset, yOffset);
    }
}




void show_tree(TreeVizualizer& visualizer) {

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    float x2 = 0.3f, y2 = 0.3f;
    float x1 = -0.1f, y1 = -0.1f;
    visualizer.drawTreeNode(root,x1,y1,x2,y2,WHITE);
    bool found = root->DFS(4, root, visualizer, true);
}

void show_graph(TreeVizualizer& visualizer) {
    auto node = std::make_unique<GraphNode>("a", 2);
    auto node1 = std::make_unique<GraphNode>("b", 3);
    auto node2 = std::make_unique<GraphNode>("c", 4);
    auto node3 = std::make_unique<GraphNode>("d", 5);


    float x1 = -0.1f, y1 = -0.1f;
    float x2 = 0.1f, y2 = 0.1f;

    visualizer.drawGraph(node.get(), x1, y1, x2, y2, WHITE);

    node->insert_node(std::move(node1));
    // visualizer.drawGraph(node.get(), x1, y1, x2, y2, WHITE);

    node->insert_node(std::move(node2));
    // visualizer.drawGraph(node.get(), x1, y1, x2, y2, WHITE);

    node->insert_node(std::move(node3));
    // visualizer.drawGraph(node.get(), x1, y1, x2, y2, WHITE);

    // node->dijkstra(node.get(), node3.get(), &visualizer);

    
    // visualizer.drawGraph(node.get(), x1, y1, x2, y2, WHITE);

    
    visualizer.drawGraph(node.get(), x1, y1, x2, y2, WHITE);
    
}






int main() {

    TreeVizualizer visualizer;


    glfwMakeContextCurrent(visualizer.window);


    int width = 1920;
    int height = 1080;
    glfwGetFramebufferSize(visualizer.window, &width, &height);
    glViewport(0, 0, width, height);


    while (!glfwWindowShouldClose(visualizer.window)) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // linked_show(visualizer);
        // show_stack(visualizer);
        // show_tree(visualizer);
        show_graph(visualizer);

        glfwSwapBuffers(visualizer.window);

        
        glfwPollEvents();
    }

    return 0;
}
