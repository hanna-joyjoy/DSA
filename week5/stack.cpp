#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct NODE 
{
    int key;
    NODE* p_next;
};

struct Stack 
{
    NODE* top;
};

Stack* initializeStack() 
{
    Stack* s = new Stack;
    if (s == nullptr) return s;
    s->top = nullptr;
    return s;
}

void push(Stack& s, int key) 
{
    NODE* newNode = new NODE;
    if (newNode == nullptr) return;
    newNode->key = key;
    newNode->p_next = s.top;
    s.top = newNode;
}

int pop(Stack& s) 
{
    if (s.top == nullptr) return -1; 
    NODE* temp = s.top;
    int poppedValue = temp->key;
    s.top = temp->p_next;
    delete temp;
    return poppedValue;
}

int size(Stack s) 
{
    int count = 0;
    NODE* cur = s.top;
    while (cur != nullptr) 
    {
        count++;
        cur = cur->p_next;
    }
    return count;
}

bool isEmpty(Stack s) 
{
    return (s.top == nullptr);
}

void outputStack(ofstream& fout, Stack s) 
{
    if (isEmpty(s)) 
    {
        fout << "EMPTY" << endl;
        return;
    }
    const int MAX = 1000;
    int arr[MAX];
    int idx = 0;

    NODE* cur = s.top;
    while (cur != nullptr) 
    {
        arr[idx++] = cur->key;
        cur = cur->p_next;
    }
    for (int i = idx - 1; i >= 0; --i) 
    {
        fout << arr[i];
        if (i != 0) fout << " ";
    }
    fout << endl;
}

int main() 
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    Stack* s = nullptr;
    string command;

    while (fin >> command) 
    {
        if (command == "init") 
        {
            if (s != nullptr) 
            {
                while (!isEmpty(*s)) 
                {
                    pop(*s);
                }
                delete s;
            }
            s = initializeStack();
            outputStack(fout, *s);
        }
        else if (command == "push") 
        {
            int value;
            fin >> value;
            if (s != nullptr) 
            {
                push(*s, value);
                outputStack(fout, *s);
            }
        }
        else if (command == "pop") 
        {
            if (s != nullptr) 
            {
                int poppedValue = pop(*s);
                outputStack(fout, *s);
            }
        }
    }

    if (s != nullptr) 
    {
        while (!isEmpty(*s)) 
        {
            pop(*s);
        }
        delete s;
    }

    fin.close();
    fout.close();

    return 0;
}
