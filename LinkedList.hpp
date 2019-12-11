#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>
#include "Node.hpp"

template <class T>
class LinkedList
{
    public: // DO NOT CHANGE THIS PART.
        LinkedList();
        LinkedList(const LinkedList &obj);

        ~LinkedList();

        Node<T> *getFirstNode() const; //
        Node<T> *getHead() const;
        Node<T> *getTail() const;
        int getNumberOfNodes();
        bool isEmpty(); //

        void insertAtTheFront(const T &data); //
        void insertAtTheEnd(const T &data); //
        void insertAfterGivenNode(const T &data, Node<T> *prev); //

        void removeNode(Node<T> *node);
        void removeAllNodes();

        Node<T> *findNode(const T &data); //

        void printAllNodes();
        void printReversed();

        LinkedList &operator=(const LinkedList &rhs);

    private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

    private: // DO NOT CHANGE THIS PART.
        Node<T> *head;
        Node<T> *tail;
};

template<class T>
LinkedList<T>::LinkedList()
{
    head = new Node<T>();
    tail = new Node<T>();
    tail->prev = head;
    head->next = tail;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList &obj)
{
    head = new Node<T>();
    tail = new Node<T>();
    tail->prev = head;
    head->next = tail;
    *this = obj;
}

template<class T>
LinkedList<T>::~LinkedList()
{
    removeAllNodes();
    delete head;
    delete tail;
}

template<class T>
Node<T> * LinkedList<T>::getFirstNode() const
{
    if(head->next == tail){
        return NULL;
    }
    else{
        return head->next;
    }
}

template<class T>
Node<T> * LinkedList<T>::getHead() const
{
    return head;
}

template<class T>
Node<T> * LinkedList<T>::getTail() const
{
    return tail;
}

template<class T>
int LinkedList<T>::getNumberOfNodes() 
{
    int i = 0;
    Node<T> *current = head;
    if(current->next == tail){
        return i;
    }
    else{
        while (current->next != tail)
        {
            current = current->next;
            i++;
        }
    }
    return i;
}

template<class T>
bool LinkedList<T>::isEmpty()
{
    if(head->next == tail){
        return true;
    }
    else{
        return false;
    }
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data)
{
    if(head->next == tail){
        Node<T>* newnode = new Node<T>(data, head, tail);
        head->next = newnode;
        tail->prev = newnode;
    }
    else{
        Node<T>* newnode = new Node<T>(data, head, head->next);
        head->next = newnode;
        newnode->next->prev = newnode;
    }
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data)
{
    if(head->next == tail){
        Node<T>* newnode = new Node<T>(data, head, tail);
        head->next = newnode;
        tail->prev = newnode;
    }
    else{
        Node<T>* newnode = new Node<T>(data, tail->prev, tail);
        tail->prev = newnode;
        newnode->prev->next = newnode;
    }
}

template<class T>
void LinkedList<T>::insertAfterGivenNode(const T &data, Node<T> *prev)
{   
    Node<T>* current = head;
    while(current != tail){
        if(current == prev){
            Node<T>* newnode = new Node<T>(data, prev, current->next);
            current->next = newnode;
            newnode->next->prev = newnode;
            break;
        }
        else{
            current = current->next;
        }
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    if(head->next!=tail){
        Node<T> *current = head->next;
        while (current!=tail){
            if(current == node && current!=tail){
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
                break;
            }
            else{
                current = current->next;
            }
        }
    }    
}

template<class T>
void LinkedList<T>::removeAllNodes()
{
    Node<T> *current = head->next;
    Node<T> *temp;
    while(current!=tail && current != NULL){
        temp = current->next;
        delete current;
        current = temp;

        if(temp!=NULL){
            temp = temp->next;
        }
    }
    head->next = tail;
    tail->prev = head;
}

template<class T>
Node<T> * LinkedList<T>::findNode(const T &data)
{
    if(head->next != tail){
        Node<T> *current = head->next;
            while (current!=tail){
                if(current->element == data){
                    return current;
                }
                else{
                    current = current->next;
                }            
            }
    }
    return NULL;
}

template<class T>
void LinkedList<T>::printAllNodes()
{
    if(head->next != tail){
    Node<T> *current = head->next;
        while (current != tail)
        {
            std::cout<<current->element<<std::endl;
            current = current->next;
        }
    }
}

template<class T>
void LinkedList<T>::printReversed()
{
    if(tail->prev != head){
    Node<T> *current = tail->prev;
        while (current != head)
        {
            std::cout<<current->element<<std::endl;
            current=current->prev;
        }
    }
}

template<class T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList &rhs)
{
    if(this != &rhs){
        removeAllNodes();
        Node<T>* r = rhs.head->next;
        while(r!=rhs.tail){
            insertAtTheEnd(r->element);
            r = r->next;
        }
    }
    return *this;
}

#endif //LINKED_LIST_HPP
