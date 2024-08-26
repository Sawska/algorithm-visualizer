#ifndef TREE_H

#define TREE_H


#include <queue>
#include "TreeVisualizer.h"


class TreeVizualizer;



class TreeNode {
    public:
    int value;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int d){
        value = d;
        left = nullptr;
        right = nullptr;
    }
    void insert_node(TreeNode *node,TreeNode* head);
    TreeNode* delete_node(int value,TreeNode* head); 
    bool DFS(int value, TreeNode* head, TreeVizualizer& visualizer, bool paint);
    bool BFS(int value, TreeNode* head, TreeVizualizer& visualizer, bool paint);
};

#endif // TREE_H