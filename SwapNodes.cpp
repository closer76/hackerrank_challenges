#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

struct Pair {
    int left;
    int right;
};

Node* constructTree(int index, const vector<Pair>& pairs, int depth, const vector<bool>& do_swap) {
    //cout << "index=" << index << endl;
    if (index < 0) {
        return nullptr;
    }

    Node* result = new Node;
    result->data = index + 1;
    auto& pair = pairs[index];
    if (do_swap[depth]) {
        result->right = constructTree(pair.left - 1, pairs, depth + 1, do_swap);
        result->left = constructTree(pair.right - 1, pairs, depth + 1, do_swap);        
    } else {
        result->left = constructTree(pair.left - 1, pairs, depth + 1, do_swap);
        result->right = constructTree(pair.right - 1, pairs, depth + 1, do_swap);
    }
    return result;
}

void inOrder(Node* root, string& history) {
    if (root) {
        inOrder(root->left, history);
        history += (to_string(root->data) + " ");
        inOrder(root->right, history);
    }
}

int main() {
    int tmp;

    int node_count;
    cin >> node_count;
    vector<Pair> pairs(node_count + 1);
    for (int i = 0; i < node_count; i++) {
        cin >> pairs[i].left >> pairs[i].right;
    }

    int op_count;
    cin >> op_count;
    vector<bool>do_swap(1024, false);
    for (int i = 0; i < op_count; i++) {
        cin >> tmp;
        do_swap[tmp - 1] = !do_swap[tmp - 1];
    }
    
    for (int i = 511; i >= 0; i--) {
        //cout << "i=" << i << "," << do_swap[i] << endl;
        if (do_swap[i]) {
            for (int k = 2 * (i + 1) - 1; k < 1024; k += (i + 1)) {
                //cout << "i=" << i << "; k=" << k << endl;
                do_swap[k] = !do_swap[k];
            }
        }
    }
    
    Node* tree = constructTree(0, pairs, 0, do_swap);
    string result = "";
    inOrder(tree, result);
    //result.erase(result.find_last_not_of(" \n\r\t")+1);

    cout << result << endl;
    
    return 0;
}
