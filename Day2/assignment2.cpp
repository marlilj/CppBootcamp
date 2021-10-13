#include <iostream>

typedef struct Node {
    int value;
    struct Node *next = nullptr;
}Node_t;

void add(Node_t *LL, int value) {
    Node_t *ll=LL;
    while (ll->next != nullptr) {
        ll = ll->next;
    }
    ll->next = new Node_t;
    ll->next->value = value;
    ll->next->next = nullptr;

}

void remove(Node_t *&LL) {
    if (LL == nullptr) {
        return;
    } else {
        Node_t *next = LL->next;
        delete LL;
        LL = next;
    }

}

void print(Node_t *LL) {
    if (LL == nullptr) {
        return;
    } else {
        Node_t *ll = LL;
        while (ll->next != nullptr) {
            ll = ll->next;
            std::cout << ll->value << std::endl;
        }
    }
}

int main(int argc, char ** argv) {

    Node_t *head = new Node_t;
    add(head, 11);
    add(head, 12);
    add(head, 11);
    add(head, 12);
    print(head);
    std::cout << "new print" << std::endl;
    remove(head);
    print(head);

}