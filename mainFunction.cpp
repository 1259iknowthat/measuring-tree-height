#include "trees.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

#define MAXN 1000000

template <typename T>
class Node {
    public:
        T data;
        Node* left;
        Node* right;
        int height;
};

// Function to calculate the height of the tree recursively
template <typename T>
int calculateTreeHeight(T* node) {
    if (node == nullptr)
        return -1;

    int leftHeight = calculateTreeHeight(node->left);
    int rightHeight = calculateTreeHeight(node->right);

    return 1 + std::max(leftHeight, rightHeight);
}

int main(){
    int **arr = new int*[10];
    FILE *height_rp_file;
    height_rp_file = fopen("height.txt", "w");

    // read data from file
    std::string line;
    // create a pointer to an array of pointers to int
    std::ifstream myfile("input-data.txt");
    if (myfile.is_open()) {
        int i = 0;
        while (getline(myfile, line)) {
            std::istringstream iss(line);
            int j = 0;
            arr[i] = new int[MAXN]; // allocate memory for the i-th row
            while (iss >> arr[i][j]) {
                j++;
            }
            i++;
        }
        myfile.close();
    }

    // calculate height
    printf("+---------------------------------------+\n");
    printf("|\tAVL\t|\tRed-Black\t|\n");
    printf("+---------------------------------------+\n");
    fprintf(height_rp_file, "+-----------------------+\n");
    fprintf(height_rp_file,"|\tAVL\t|\tRed-Black\t|\n" );
    fprintf(height_rp_file, "+-----------------------+\n");
    for (int i = 0; i < 10; i++){
        AVL<int> avlt;
        RedBlackTree<int> rbt;
        for (int j = 0; j < MAXN; j++){
            avlt.insert(arr[i][j]);
            rbt.insert(arr[i][j]);
        }
        int avlHeight = calculateTreeHeight(avlt.root);
        int rbtHeight = calculateTreeHeight(rbt.root);
        printf("|\t%d\t|\t%d\t\t|\n",avlHeight,rbtHeight);
        fprintf(height_rp_file,"|\t%3d\t|\t%9d\t|\n",avlHeight,rbtHeight);
        avlt.deleteTree(avlt.root);
        rbt.deleteTree(rbt.root);
    }
    printf("+---------------------------------------+\n");
    fprintf(height_rp_file, "+-----------------------+\n");

    fclose(height_rp_file);
    
    // retrieve space
    for (int i = 0; i < 10; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}
