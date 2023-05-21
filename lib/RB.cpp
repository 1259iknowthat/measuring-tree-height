#include <iostream>

using namespace std;

template <typename T>
class RedBlackTree {
    public:
        class Node {
        public:
            T key;
            bool isRed;
            Node* left;
            Node* right;
            Node* parent;
            int height;
            Node(T k) {
                key = k;
                isRed = true; // New nodes are always red
                left = nullptr;
                right = nullptr;
                parent = nullptr;
                height = 1;
            }
        };

    Node* root = nullptr;

    void insert(T x) {
        Node* newNode = new Node(x);
        root = insertUtil(root, newNode);
        fixViolation(newNode);
    }

    void remove(T x) {
        Node* node = search(x);
        if (node != nullptr) {
            root = removeUtil(root, node);
        }
    }

    Node* search(T x) {
        return searchUtil(root, x);
    }

    void inorder() {
        inorderUtil(root);
        cout << endl;
    }
    
    void deleteTree(Node* node) {
        if (node == nullptr) {
            return;
        }
        deleteTree(node->left);
        deleteTree(node->right);
        delete [] node;
    }

private:
    Node* insertUtil(Node* current, Node* newNode) {
        if (current == nullptr) {
            return newNode;
        }
        if (newNode->key < current->key) {
            current->left = insertUtil(current->left, newNode);
            current->left->parent = current;
        } else if (newNode->key > current->key) {
            current->right = insertUtil(current->right, newNode);
            current->right->parent = current;
        }
        return current;
    }

    void fixViolation(Node* node) {
        while (node != root && node->parent->isRed) {
            if (node->parent == node->parent->parent->left) {
                Node* uncle = node->parent->parent->right;
                if (uncle != nullptr && uncle->isRed) {
                    node->parent->isRed = false;
                    uncle->isRed = false;
                    node->parent->parent->isRed = true;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    node->parent->isRed = false;
                    node->parent->parent->isRed = true;
                    rotateRight(node->parent->parent);
                }
            } else {
                Node* uncle = node->parent->parent->left;
                if (uncle != nullptr && uncle->isRed) {
                    node->parent->isRed = false;
                    uncle->isRed = false;
                    node->parent->parent->isRed = true;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    node->parent->isRed = false;
                    node->parent->parent->isRed = true;
                    rotateLeft(node->parent->parent);
                }
            }
        }
        root->isRed = false;
    }

    void rotateLeft(Node* node) {
        Node* rightChild = node->right;
        node->right = rightChild->left;
        if (rightChild->left != nullptr) {
            rightChild->left->parent = node;
        }
        rightChild->parent = node->parent;
        if (node->parent == nullptr) {
            root = rightChild;
        } else if (node == node->parent->left) {
            node->parent->left = rightChild;
        } else {
            node->parent->right = rightChild;
        }
        rightChild->left = node;
        node->parent = rightChild;
    }

    void rotateRight(Node* node) {
        Node* leftChild = node->left;
        node->left = leftChild->right;
        if (leftChild->right != nullptr) {
            leftChild->right->parent = node;
        }
        leftChild->parent = node->parent;
        if (node->parent == nullptr) {
            root = leftChild;
        } else if (node == node->parent->left) {
            node->parent->left = leftChild;
        } else {
            node->parent->right = leftChild;
        }
        leftChild->right = node;
        node->parent = leftChild;
    }

    Node* removeUtil(Node* current, Node* node) {
        if (current == nullptr) {
            return nullptr;
        }
        if (node->key < current->key) {
            current->left = removeUtil(current->left, node);
        } else if (node->key > current->key) {
            current->right = removeUtil(current->right, node);
        } else {
            if (current->left == nullptr || current->right == nullptr) {
                Node* child = current->left != nullptr ? current->left : current->right;
                if (child != nullptr) {
                    child->parent = current->parent;
                }
                if (current == root) {
                    root = child;
                } else {
                    if (current == current->parent->left) {
                        current->parent->left = child;
                    } else {
                        current->parent->right = child;
                    }
                }
                delete current;
                current = nullptr;
            } else {
                Node* successor = minimumNode(current->right);
                current->key = successor->key;
                current->right = removeUtil(current->right, successor);
            }
        }
        return current;
    }

    Node* minimumNode(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* searchUtil(Node* current, T x) {
        if (current == nullptr || current->key == x) {
            return current;
        }
        if (x < current->key) {
            return searchUtil(current->left, x);
        }
        return searchUtil(current->right, x);
    }

    void inorderUtil(Node* current) {
        if (current == nullptr) {
            return;
        }
        inorderUtil(current->left);
        cout << current->key << " ";
        inorderUtil(current->right);
    }
};
