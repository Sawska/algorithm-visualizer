#include "TreeVisualizer.h"
#include "LinkedList.h"
#include "MyStack.h"
#include "tree.h"
#include "graph.h"



const int WHITE = 0xFFFFFF;


void linked_show(TreeVizualizer& visualizer) {
    LinkedList list = LinkedList(0);
    visualizer.drawLinkedList(&list, 0, 0, 1, 1, 0, 0);
    list.add(0, &list);
    visualizer.drawLinkedList(&list, 0, 0, 1, 1, 0, 0);
    list.add(1, &list);
    visualizer.drawLinkedList(&list, 0, 0, 1, 1, 0, 0);
    list.add(2, &list);
    visualizer.drawLinkedList(&list, 0, 0, 1, 1, 0, 0);
    list.add(3, &list);
    visualizer.drawLinkedList(&list, 0, 0, 1, 1, 0, 0);
    list.remove(1, &list);
    visualizer.drawLinkedList(&list, 0, 0, 1, 1, 0, 0);
    list.add(3, &list);
    visualizer.drawLinkedList(&list, 0, 0, 1, 1, 0, 0);
}

void show_stack(TreeVizualizer& visualizer) {
    MYSTACK<int> stack;
    stack.push(1);
    visualizer.drawStack(&stack, 0, 0, 1, 1, 0, 0);
    stack.push(2);
    visualizer.drawStack(&stack, 0, 0, 1, 1, 0, 0);
    stack.push(3);
    visualizer.drawStack(&stack, 0, 0, 1, 1, 0, 0);
    stack.push(4);
    while (stack.size() != 0) {
        stack.pop();
        visualizer.drawStack(&stack, 0, 0, 1, 1, 0, 0);
    }
}


void show_tree(TreeVizualizer& visualizer) {

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    bool found = root->DFS(4, root, visualizer, true);
}

void show_graph(TreeVizualizer& visualizer) {
    auto node = std::make_unique<GraphNode>("a", 2);
    auto node1 = std::make_unique<GraphNode>("b", 3);
    auto node2 = std::make_unique<GraphNode>("c", 4);
    auto node3 = std::make_unique<GraphNode>("d", 5);

    visualizer.drawGraph(node.get(), 0, 0, 10, 10, WHITE);


    node->insert_node(std::move(node1));
    visualizer.drawGraph(node.get(), 0, 0, 10, 10, WHITE);

    node->insert_node(std::move(node2));
    visualizer.drawGraph(node.get(), 0, 0, 10, 10, WHITE);

    node->insert_node(std::move(node3));
    visualizer.drawGraph(node.get(), 0, 0, 10, 10, WHITE);

    node->dijkstra(node.get(), node3.get(), &visualizer);

    node->delete_node("b");
    visualizer.drawGraph(node.get(), 0, 0, 10, 10, WHITE);

    node->delete_node("d");
    visualizer.drawGraph(node.get(), 0, 0, 10, 10, WHITE);
}





int main() {
    TreeVizualizer visualizer;
    glfwMakeContextCurrent(visualizer.window);
    int width, height;
    glfwGetFramebufferSize(visualizer.window, &width, &height);
    glViewport(0, 0, width, height);




    while (!glfwWindowShouldClose(visualizer.window)) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        linked_show(visualizer);
        // show_stack(visualizer);
        // show_tree(visualizer);
        // show_graph(visualizer);

        glfwSwapBuffers(visualizer.window);

        glfwPollEvents();
    }
    return 0;
}



