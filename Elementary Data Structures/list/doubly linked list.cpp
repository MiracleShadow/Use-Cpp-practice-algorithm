#include <iostream>

class Node      // 节点
{
public:
    int key;
    Node *prev, *next;
    Node();
};

Node::Node()
{
    this->next = NULL;
}


class doublyLinkedList      // 构造一个双向链表
{
private:
    Node *head, *tail;
    int length;
public:
    doublyLinkedList();
    bool push_back(int data);    // 尾插
    bool push_front(int data);   // 头插
    int pop_back();              // 尾出
    int pop_front();             // 头出
    Node* insert(Node *p, int key);
    Node* erase(Node *p);
    bool empty();
    size_t size();
    int front();
    int back();
};

doublyLinkedList::doublyLinkedList()
{
}

