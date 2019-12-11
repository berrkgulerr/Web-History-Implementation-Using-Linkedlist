#include <iostream>

#include "LinkedList.hpp"

int main() {
    LinkedList<int> llist;

    llist.printAllNodes();
    std::cout << "empty" << llist.isEmpty()<< std::endl;
    llist.insertAtTheEnd(1);
    llist.insertAtTheEnd(7);
    llist.insertAtTheEnd(4);
    llist.insertAtTheEnd(3);
    llist.printAllNodes();

    llist.removeNode(llist.findNode(4));
    llist.removeNode(llist.findNode(5));
    llist.printAllNodes();

    llist.insertAfterGivenNode(5, llist.getHead());
    llist.printAllNodes();
    llist.removeAllNodes();
    std::cout << "empty" << llist.isEmpty()<< std::endl;
    llist.insertAtTheFront(1);
    llist.printAllNodes();
    return 0;
}