#include <iostream>

typedef struct Node {
    int value = 0;
    struct Node *next = nullptr;

    Node() {};
    Node(int _value) : value(_value) {};

} Node_t;

class LinkedList {

    Node_t *head = nullptr;

public:

    ~LinkedList() {
        this->clearList();
    }

    void printLinkedList() {
        std::cout << "Printing LinkedList in order" << std::endl;
        Node_t *current = this->head;
        if (current != nullptr) {
            while (current->next != nullptr) {
                std::cout << current->value << " ";
                current = current->next;
            }
            std::cout << current->value << " ";
        } else {
            std::cout << "-";
        }
        
        std::cout << std::endl;

    }

    void addItem(int value) {
        if (this->head == nullptr) {
            this->head = new Node_t(value);
        } else {
            Node_t *prevLast = this->findLastItem();
            Node_t *newItem = new Node_t(value);
            prevLast->next = newItem;
        }
    }

    void removeFirstItem() {
        if (this->head != nullptr) {
            Node_t *p_intermediate = this->head->next;
            delete this->head;
            this->head = p_intermediate;
        }
    }

    Node_t * findLastItem() {
        Node_t *returnNode = nullptr;
        if (this->head != nullptr) {
            returnNode = this->head;
            // Propagate until last item  
            while (returnNode->next != nullptr) {
                returnNode = returnNode->next;
            }
        }
        return returnNode;
    }

    void clearList() {
        // TODO: Ask why Valgrind throws error but memory is freed
        if (this->head != nullptr) {
            Node_t *current = this->head;
            Node_t *next = current->next;
            while (next != nullptr) {
                delete current;
                current = next;
                next = next->next;
            }
            delete current;
            this->head = nullptr;
        }
        
    }

    void reverseList() {
        if (this->head != nullptr) {
            Node_t *current = this->head;
            Node_t *reversedNode;
            Node_t *reversedNodePrev = nullptr;
            while (current != nullptr) {
                reversedNode = current;
                current = current->next;
                reversedNode->next = reversedNodePrev;
                reversedNodePrev = reversedNode;
            }
            this->head = reversedNode;
        }
    }

};

int main(int argc, char ** argv) {

    std::cout << "Options:\n p - print list\n a - append to end of list\n r - remove first item in list \n i - invert order of list\n e - exit\n" << std::endl;

    std::string input;
    char option = 'i';
    int value;
    LinkedList ll;

    while (option != 'e') {
        std::cout << "option (p/a/r/i/e): ";
        std::cin >> input;
        option = input[0];
        switch (option) {
            case 'p':
                ll.printLinkedList();
                break;
            case 'a':
                std::cout << "Enter a value to add: ";
                std::cin >> input;
                value = std::stoi(input);
                ll.addItem(value); 
                break;
            case 'r':
                std::cout << "Removing first item in list" << std::endl;
                ll.removeFirstItem();
                break;
            case 'i':
                std::cout << "Inverting order of list" << std::endl;
                ll.reverseList();
                break;
            case 'e':
                std::cout << "Exiting!" << std::endl;
                break;
            default:
                std::cout << "No known option: " << option << std::endl;
                break;
        }
    }

    // ll.addItem(10);
    // ll.addItem(11);
    // ll.addItem(12);
    // ll.printLinkedList();
    // ll.reverseList();
    // ll.printLinkedList();

}