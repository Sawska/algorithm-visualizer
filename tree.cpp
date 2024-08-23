#include <tree.h>

void TreeNode::insert_node(TreeNode* node, TreeNode* head) {
    if (node->value < head->value) {
        if (head->left != nullptr) {
            insert_node(node, head->left);
        } else {
            head->left = node;
        }
    } else if (node->value > head->value) {
        if (head->right != nullptr) {
            insert_node(node, head->right);
        } else {
            head->right = node;
        }
    }
}

TreeNode* TreeNode::delete_node(int value, TreeNode* head) {
    if (head == nullptr) return nullptr;

    if (value < head->value) {
        head->left = delete_node(value, head->left);
    } else if (value > head->value) {
        head->right = delete_node(value, head->right);
    } else {

        if (head->left == nullptr) {
            TreeNode* temp = head->right;
            delete head;
            return temp;
        } else if (head->right == nullptr) {
            TreeNode* temp = head->left;
            delete head;
            return temp;
        }
        
        TreeNode* temp = head->right;
        while (temp && temp->left != nullptr)
            temp = temp->left;
        
        head->value = temp->value;

        head->right = delete_node(temp->value, head->right);
    }
    return head;
}

bool TreeNode::DFS(int value,TreeNode* head) {
    
     if (head == nullptr) {
        return false;
    }

        if(head->value == value)
        {
            return true;
        } else {
            return BFS(value,head->left) || BFS(value,head->right);
        }
}





bool TreeNode::BFS(int value, TreeNode* head) {
    if (head == nullptr) {
        return false;
    }

    std::queue<TreeNode*> q;
    q.push(head);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        if (current->value == value) {
            return true;
        }

        if (current->left != nullptr) {
            q.push(current->left);
        }

        if (current->right != nullptr) {
            q.push(current->right);
        }
    }

    return false;
}
