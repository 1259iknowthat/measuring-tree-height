#include<iostream>

using namespace std;

template <typename T>

class AVL{
    public:
        class Node{
            public:
                T key;
                int height;
                Node* left;
                Node* right;
                Node(T k){
                    height = 0;
                    key = k;
                    left = NULL;
                    right = NULL;
                }
        };

        Node* root = NULL;
        int n;

        void insert(T x){
            root=insertUtil(root, x);
        }

        void remove(T x){
            root=removeUtil(root, x);
        }

        Node* search(T x){
            return searchUtil(root,x);
        }

        void inorder(){
            inorderUtil(root);
            cout<<endl;
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
        int height(Node* head){
            if(head == NULL) return 0;
            return head->height;
        }

        Node* rightRotation(Node* head){
            Node* newhead = head->left;
            head->left = newhead->right;
            newhead->right = head;
            head->height = 1 + max(height(head->left), height(head->right));
            newhead->height = 1 + max(height(newhead->left), height(newhead->right));
            return newhead;
        }

        Node* leftRotation(Node* head){
            Node* newhead = head->right;
            head->right = newhead->left;
            newhead->left = head;
            head->height = 1 + max(height(head->left), height(head->right));
            newhead->height = 1 + max(height(newhead->left), height(newhead->right));
            return newhead;
        }

        void inorderUtil(Node* head){
            if(head == NULL) return ;
            inorderUtil(head->left);
            cout << head->key << " ";
            inorderUtil(head->right);
        }

        Node* insertUtil(Node* head, T x){
            if(head == NULL){
                n += 1;
                Node* temp = new Node(x);
                return temp;
            }
            if(x < head->key) head->left = insertUtil(head->left, x);
            else if(x > head->key) head->right = insertUtil(head->right, x);
            head->height = 1 + max(height(head->left), height(head->right));
            int bal = height(head->left) - height(head->right);
            if(bal > 1){
                if(x < head->left->key){
                    return rightRotation(head);
                }else{
                    head->left = leftRotation(head->left);
                    return rightRotation(head);
                }
            }else if(bal < -1){
                if(x > head->right->key){
                    return leftRotation(head);
                }else{
                    head->right = rightRotation(head->right);
                    return leftRotation(head);
                }
            }
            return head;
        }

        Node* removeUtil(Node* head, T x){
            if(head == NULL) return NULL;
            if(x < head->key){
                head->left = removeUtil(head->left, x);
            }else if(x > head->key){
                head->right = removeUtil(head->right, x);
            }else { 
                Node* r = head->right;
                if(head->right == NULL){
                    Node* l = head->left;
                    delete(head);
                    head = l;
                }else if(head->left == NULL){
                    delete(head);
                    head = r;
                }else {
                    while(r->left!=NULL) r = r->left;
                    head->key = r->key;
                    head->right = removeUtil(head->right, r->key);
                }
            }
            if(head == NULL) return head;
            head->height = 1 + max(height(head->left), height(head->right));
            int bal = height(head->left) - height(head->right);
            if(bal > 1){
                if(height(head->left) >= height(head->right)){
                    return rightRotation(head);
                }else{
                    head->left = leftRotation(head->left);
                    return rightRotation(head);
                }
            }else if(bal < -1){
                if(height(head->right) >= height(head->left)){
                    return leftRotation(head);
                }else{
                    head->right = rightRotation(head->right);
                    return leftRotation(head);
                }
            }
            return head;
        }

        Node* searchUtil(Node* head, T x){
            if(head == NULL) return NULL;
            T k = head->key;
            if(k == x) return head;
            if(k > x) return searchUtil(head->left, x);
            if(k < x) return searchUtil(head->right, x);
        }
};