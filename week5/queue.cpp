#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct NODE 
{
    int key;
    NODE* p_next;
};

struct Queue 
{
    NODE* head;
    NODE* tail;
};

Queue* initializeQueue() 
{
    Queue* q = new Queue;
    if (q == nullptr) return q;
    q->head = q->tail = nullptr;
    return q;
}

void enqueue(Queue& q, int key) 
{
    NODE* newNode = new NODE;
    if (newNode == nullptr) return;
    newNode->key = key;
    newNode->p_next = nullptr;

    if (q.tail == nullptr) 
    {
        q.head = q.tail = newNode;
    }
    else 
    {
        q.tail->p_next = newNode;
        q.tail = newNode;
    }
}

int dequeue(Queue& q) 
{
    if (q.head == nullptr) 
    {
        return -1; 
    }
    NODE* temp = q.head;
    int dequeuedValue = temp->key;
    q.head = temp->p_next;
    if (q.head == nullptr) 
    {
        q.tail = nullptr;
    }
    delete temp;
    return dequeuedValue;
}

int size(Queue q) 
{
    int count = 0;
    NODE* cur = q.head;
    while (cur != nullptr) 
    {
        count++;
        cur = cur->p_next;
    }
    return count;
}

bool isEmpty(Queue q) 
{
    return (q.head == nullptr);
}

void outputQueue(ofstream& fout, Queue q)
{
    if (isEmpty(q)) 
    {
        fout << "EMPTY" << endl;
        return;
    }
    NODE* cur = q.head;
    while (cur != nullptr) {
        fout << cur->key;
        if (cur->p_next != nullptr) {
            fout << " ";
        }
        cur = cur->p_next;
    }
    fout << endl;
}

int main() 
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    Queue* q = nullptr;
    string command;

    while (fin >> command) 
    {
        if (command == "init") 
        {
            if (q != nullptr) 
            {
                while (!isEmpty(*q)) 
                {
                    dequeue(*q);
                }
                delete q;
            }
            q = initializeQueue();
            outputQueue(fout, *q);
        }
        else if (command == "enqueue") {
            int value;
            fin >> value;
            if (q != nullptr) {
                enqueue(*q, value);
                outputQueue(fout, *q);
            }
        }
        else if (command == "dequeue") {
            if (q != nullptr) {
                int dequeuedValue = dequeue(*q);
                outputQueue(fout, *q);
            }
        }
    }

    if (q != nullptr) 
    {
        while (!isEmpty(*q)) 
        {
            dequeue(*q);
        }
        delete q;
    }

    fin.close();
    fout.close();

    return 0;
}
