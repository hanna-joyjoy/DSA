#include <iostream>
#include <climits>  
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

NODE* Search(NODE* pRoot, int x) 
{
    if (!pRoot || pRoot->key == x) return pRoot;
    if (x < pRoot->key) return Search(pRoot->p_left, x);
    return Search(pRoot->p_right, x);
}

void Insert(NODE*& pRoot, int x) 
{
    if (!pRoot) 
    {
        pRoot = createNode(x);
        return;
    }
    if (x < pRoot->key)
        Insert(pRoot->p_left, x);
    else if (x > pRoot->key)
        Insert(pRoot->p_right, x);
}

NODE* findMin(NODE* pRoot) 
{
    while (pRoot && pRoot->p_left) pRoot = pRoot->p_left;
    return pRoot;
}

void Remove(NODE*& pRoot, int x) 
{
    if (!pRoot) return;
    if (x < pRoot->key)
        Remove(pRoot->p_left, x);
    else if (x > pRoot->key)
        Remove(pRoot->p_right, x);
    else 
    {
        if (!pRoot->p_left) 
        {
            NODE* temp = pRoot;
            pRoot = pRoot->p_right;
            delete temp;
        }
        else if (!pRoot->p_right) 
        {
            NODE* temp = pRoot;
            pRoot = pRoot->p_left;
            delete temp;
        }
        else 
        {
            NODE* temp = findMin(pRoot->p_right);
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }
}

NODE* createTree(int a[], int n) 
{
    NODE* pRoot = nullptr;
    for (int i = 0; i < n; ++i)
        Insert(pRoot, a[i]);
    return pRoot;
}

void removeTree(NODE*& pRoot) 
{
    if (!pRoot) return;
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    delete pRoot;
    pRoot = nullptr;
}

int Height(NODE* pRoot) 
{
    if (!pRoot) return -1;  
    return 1 + max(Height(pRoot->p_left), Height(pRoot->p_right));
}

int countLess(NODE* pRoot, int x) 
{
    if (!pRoot) return 0;
    if (pRoot->key < x)
        return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
    return countLess(pRoot->p_left, x);
}

int countGreater(NODE* pRoot, int x) 
{
    if (!pRoot) return 0;
    if (pRoot->key > x)
        return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
    return countGreater(pRoot->p_right, x);
}

bool isBSTUtil(NODE* pRoot, int minVal, int maxVal) 
{
    if (!pRoot) return true;
    if (pRoot->key <= minVal || pRoot->key >= maxVal) return false;
    return isBSTUtil(pRoot->p_left, minVal, pRoot->key) &&
        isBSTUtil(pRoot->p_right, pRoot->key, maxVal);
}

bool isBST(NODE* pRoot) 
{
    return isBSTUtil(pRoot, INT_MIN, INT_MAX);
}

bool isFullBST(NODE* pRoot) 
{
    if (!pRoot) return true;
    if (!pRoot->p_left && !pRoot->p_right) return true;
    if (pRoot->p_left && pRoot->p_right)
        return isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right);
    return false;
}
