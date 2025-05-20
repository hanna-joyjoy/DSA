#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct NODE 
{
    int key;
    NODE* p_left;
    NODE* p_right;
};

NODE* createNode(int data) 
{
    NODE* p = new NODE;
    if (!p) return nullptr;
    p->key = data;
    p->p_left = p->p_right = nullptr;
    return p;
}
void preOrder(NODE* pRoot, vector<int>& result) 
{
    if (!pRoot) return;
    result.push_back(pRoot->key);
    preOrder(pRoot->p_left, result);
    preOrder(pRoot->p_right, result);
}

vector<int> NLR(NODE* pRoot) 
{
    vector<int> result;
    preOrder(pRoot, result);
    return result;
}

void inOrder(NODE* pRoot, vector<int>& result) 
{
    if (!pRoot) return;
    inOrder(pRoot->p_left, result);
    result.push_back(pRoot->key);
    inOrder(pRoot->p_right, result);
}

vector<int> LNR(NODE* pRoot) 
{
    vector<int> result;
    inOrder(pRoot, result);
    return result;
}

void postOrder(NODE* pRoot, vector<int>& result) 
{
    if (!pRoot) return;
    postOrder(pRoot->p_left, result);
    postOrder(pRoot->p_right, result);
    result.push_back(pRoot->key);
}

vector<int> LRN(NODE* pRoot) 
{
    vector<int> result;
    postOrder(pRoot, result);
    return result;
}

vector<vector<int>> LevelOrder(NODE* pRoot) 
{
    vector<vector<int>> result;
    if (!pRoot) return result;

    queue<NODE*> q;
    q.push(pRoot);

    while (!q.empty()) 
    {
        int size = q.size();
        vector<int> level;
        for (int i = 0; i < size; ++i) 
        {
            NODE* node = q.front(); 
            q.pop();
            level.push_back(node->key);
            if (node->p_left) q.push(node->p_left);
            if (node->p_right) q.push(node->p_right);
        }
        result.push_back(level);
    }

    return result;
}

int countNode(NODE* pRoot) 
{
    if (!pRoot) return 0;
    return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

int sumNode(NODE* pRoot) 
{
    if (!pRoot) return 0;
    return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}

int getHeight(NODE* node) 
{
    if (!node) return -1;
    return 1 + max(getHeight(node->p_left), getHeight(node->p_right));
}

int heightNode(NODE* pRoot, int value) 
{
    if (!pRoot) return -1;
    if (pRoot->key == value) return getHeight(pRoot);

    int left = heightNode(pRoot->p_left, value);
    if (left != -1) return left;

    return heightNode(pRoot->p_right, value);
}

int getLevel(NODE* root, NODE* p, int level) 
{
    if (!root) return -1;
    if (root == p) return level;

    int l = getLevel(root->p_left, p, level + 1);
    if (l != -1) return l;

    return getLevel(root->p_right, p, level + 1);
}

int Level(NODE* pRoot, NODE* p) 
{
    return getLevel(pRoot, p, 0);
}

int countLeaf(NODE* pRoot) 
{
    if (!pRoot) return 0;
    if (!pRoot->p_left && !pRoot->p_right) return 1;
    return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}