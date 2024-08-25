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

    if (found) {
        std::cout << "Node found!" << std::endl;
    } else {
        std::cout << "Node not found!" << std::endl;
    }
}

void show_graph(TreeVizualizer& visualizer) {
    
    GraphNode node("a",2);
    GraphNode node1("b",3);
    GraphNode node2("c",4);
    GraphNode node3("d",5);

    
    visualizer.drawGraph(&node,0,0,10,10,WHITE);

    
    node.insert_node(&node1);  
    visualizer.drawGraph(&node,0,0,10,10,WHITE);

    node1.insert_node(&node2); 
    visualizer.drawGraph(&node,0,0,10,10,WHITE);

    node1.insert_node(&node3); 
    visualizer.drawGraph(&node,0,0,10,10,WHITE);

    node.dijkstra(&node,&node3,&visualizer);

    
    node.delete_node("b"); 
    visualizer.drawGraph(&node,0,0,10,10,WHITE);

    node.delete_node("d");  
    visualizer.drawGraph(&node,0,0,10,10,WHITE);


}


int main() {
    
    TreeVizualizer visualizer;

    
    linked_show(visualizer);
    // show_stack(visualizer);

    return 0;
}

