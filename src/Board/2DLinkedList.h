#ifndef _2DLINKEDLIST_H_
#define _2DLINKEDLIST_H_
#include <iostream>
using namespace std;

// Defining the linked list for shifting
struct Node {
    char data;
    Node *next;
};

struct List {
    Node *pHead = NULL;
    Node *pTail = NULL;

    void addHead(char data) {
        Node *pCur = new Node;
        pCur->data = data;
        pCur->next = pHead;
        pHead = pCur;
        if (pHead->next == NULL)
            pTail = pHead;
    }

    void printList() {
        Node *pCur = pHead;

        while (pCur) {
            cout << pCur->data << " ";
            pCur = pCur->next;
        }
        cout << endl;
    }

    // moving the removed cell into the last of the list
    void remove(int index) {
        Node *pPrev = NULL;
        Node *pTemp = pHead;
        while (index--) {
            pPrev = pTemp;
            pTemp = pTemp->next;
        }
        pTemp->data = '#';

        if (pPrev)
            pPrev->next = pTemp->next;

        else
            pHead = pTemp->next;

        if (pTemp->next)
            pTail->next = pTemp;

        pTemp->next = NULL;
        pTail = pTemp;
    }

    char &operator[](int index) {
        Node *pCur = pHead;

        while (index--) {
            pCur = pCur->next;
        }

        return pCur->data;
    }

    void del() {
        while (pHead) {
            Node *pCur = pHead;
            pHead = pHead->next;
            delete pCur;
        }
        pTail = NULL;
    }
};

// defining the 2D list for shifting
struct Node2D {
    List data;
    Node2D *next;
};

struct List2D {
    Node2D *pHead = NULL;
    Node2D *pTail = NULL;

    void addHead(List data) {
        Node2D *pCur = new Node2D;
        pCur->data = data;
        pCur->next = pHead;
        pHead = pCur;
        if (pHead->next == NULL)
            pTail = pHead;
    }

    void printList() {
        Node2D *pCur = pHead;

        while (pCur) {
            pCur->data.printList();
            pCur = pCur->next;
        }
        cout << endl;
    }

    List &operator[](int index) {
        Node2D *pCur = pHead;

        while (index--) {
            pCur = pCur->next;
        }

        return pCur->data;
    }

    void del() {
        while (pHead) {
            Node2D *pCur = pHead;
            pHead = pHead->next;
            delete pCur;
        }
        pTail = pHead;
    }
};

#endif