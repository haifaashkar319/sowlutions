#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node() {
        data = 0;
        next = nullptr;
    }

    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

class Linkedlist {
public:
    Node* head;

    Linkedlist() {
        head = nullptr;
    }

    void addNode(int);
    void printList();
    Node* removeGreater(Node*, int);
};

void Linkedlist::addNode(int data) {
    Node* newNode = new Node(data);

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }

    temp->next = newNode;
}

Node* Linkedlist::removeGreater(Node* head, int x) {
    Node* temp = head;
    Node* prev = nullptr;
    Node* newHead = nullptr;

    while (temp != nullptr) {
        if (temp->data <= x) {
            if (newHead == nullptr) {
                newHead = temp;
            }
            prev = temp;
            temp = temp->next;
        } else {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
            if (prev != nullptr) {
                prev->next = temp;
            }
        }
    }
    return newHead;
}

void Linkedlist::printList() {
    Node* temp = head;

    if (head == nullptr) {
        cout << "List empty" << endl;
        return;
    }

    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
}

int main() {
    Linkedlist list;

    list.addNode(10);
    list.addNode(5);
    list.addNode(12);
    list.addNode(7);
    list.addNode(3);
    list.addNode(9);
    list.addNode(10);

    cout << "Original list: ";
    list.printList();
    cout << endl;

    list.head = list.removeGreater(list.head, 7);

    cout << "List after removing nodes greater than or equal to 7: ";
    list.printList();
    cout << endl;

    return 0;
}
