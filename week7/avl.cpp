#include <iostream>
#include <algorithm>  
#include <climits>    

using namespace std;

struct NODE 
{
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;  
};

NODE* createNode(int data) 
{
    NODE* p = new NODE;
    p->key = data;
    p->p_left = p->p_right = nullptr;
    p->height = 0;  
    return p;
}

int height(NODE* p) 
{
    if (!p) return -1; 
    return p->height;
}

int getBalance(NODE* p) 
{
    if (!p) return 0;
    return height(p->p_left) - height(p->p_right);
}

NODE* rotateRight(NODE* y) 
{
    NODE* x = y->p_left;
    NODE* T2 = x->p_right;

    x->p_right = y;
    y->p_left = T2;

    y->height = max(height(y->p_left), height(y->p_right)) + 1;
    x->height = max(height(x->p_left), height(x->p_right)) + 1;

    return x;  
}

NODE* rotateLeft(NODE* x) 
{
    NODE* y = x->p_right;
    NODE* T2 = y->p_left;

    y->p_left = x;
    x->p_right = T2;

    x->height = max(height(x->p_left), height(x->p_right)) + 1;
    y->height = max(height(y->p_left), height(y->p_right)) + 1;

    return y; 
}

NODE* Insert(NODE*& pRoot, int x) 
{
    if (!pRoot) return createNode(x);

    if (x < pRoot->key)
        pRoot->p_left = Insert(pRoot->p_left, x);
    else if (x > pRoot->key)
        pRoot->p_right = Insert(pRoot->p_right, x);
    else
        return pRoot;  

    pRoot->height = max(height(pRoot->p_left), height(pRoot->p_right)) + 1;

    int balance = getBalance(pRoot);

    if (balance > 1 && x < pRoot->p_left->key)
        return rotateRight(pRoot);

    if (balance < -1 && x > pRoot->p_right->key)
        return rotateLeft(pRoot);

    if (balance > 1 && x > pRoot->p_left->key) 
    {
        pRoot->p_left = rotateLeft(pRoot->p_left);
        return rotateRight(pRoot);
    }

    if (balance < -1 && x < pRoot->p_right->key) 
    {
        pRoot->p_right = rotateRight(pRoot->p_right);
        return rotateLeft(pRoot);
    }

    return pRoot;
}

NODE* findMin(NODE* pRoot) 
{
    while (pRoot->p_left)
        pRoot = pRoot->p_left;
    return pRoot;
}

NODE* Remove(NODE*& pRoot, int x) 
{
    if (!pRoot) return pRoot;

    if (x < pRoot->key)
        pRoot->p_left = Remove(pRoot->p_left, x);
    else if (x > pRoot->key)
        pRoot->p_right = Remove(pRoot->p_right, x);
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
            pRoot->p_right = Remove(pRoot->p_right, temp->key);
        }
    }

    if (!pRoot) return pRoot;

    pRoot->height = max(height(pRoot->p_left), height(pRoot->p_right)) + 1;
    int balance = getBalance(pRoot);

    if (balance > 1 && getBalance(pRoot->p_left) >= 0)
        return rotateRight(pRoot);

    if (balance < -1 && getBalance(pRoot->p_right) <= 0)
        return rotateLeft(pRoot);

    if (balance > 1 && getBalance(pRoot->p_left) < 0) 
    {
        pRoot->p_left = rotateLeft(pRoot->p_left);
        return rotateRight(pRoot);
    }

    if (balance < -1 && getBalance(pRoot->p_right) > 0) 
    {
        pRoot->p_right = rotateRight(pRoot->p_right);
        return rotateLeft(pRoot);
    }

    return pRoot;
}

bool isAVL(NODE* pRoot) 
{
    if (!pRoot) return true;

    int balance = getBalance(pRoot);
    return abs(balance) <= 1 && isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}
