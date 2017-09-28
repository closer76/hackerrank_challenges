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

Node* constructTree(int index, const vector<Pair>& pairs) {
    //cout << "index=" << index << endl;
    if (index < 0) {
        return nullptr;
    }

    Node* result = new Node;
    result->data = index + 1;
    auto& pair = pairs[index];
    result->left = constructTree(pair.left - 1, pairs);
    result->right = constructTree(pair.right - 1, pairs);

    return result;
}

void inOrder(Node* root, string& history) {
    if (root) {
        inOrder(root->left, history);
        history += (to_string(root->data) + " ");
        inOrder(root->right, history);
    }
}

void doSwap(Node* root) {
    if (root) {
        swap(root->left, root->right);
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
    Node* tree = constructTree(0, pairs);
    
    vector<vector<Node*>> depths(1, vector<Node*>(1, tree));
    Node* curr = tree;
    for (int level = 0; !depths[level].empty(); level++) {
        depths.push_back(vector<Node*>(0));
        for (auto ptr : depths[level]) {
            if (ptr->left) {
                depths[level + 1].push_back(ptr->left);
            }
            if (ptr->right) {
                depths[level + 1].push_back(ptr->right);
            }
        }
    };
    
    int op_count;
    cin >> op_count;
    for (int i = 0; i < op_count; i++) {
        cin >> tmp;
        for (int j = tmp; j < depths.size(); j += tmp) {
            for (auto ptr : depths[j - 1]) {
                doSwap(ptr);
            }
        }

        string result = "";
        inOrder(tree, result);
        cout << result << endl;
    }

    return 0;
}
