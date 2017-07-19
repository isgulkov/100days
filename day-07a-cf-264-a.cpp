#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

struct list_node
{
    int value;
    list_node* prev;
    list_node* next;
};

inline void insert_before(list_node* mouth, list_node* foot)
{
    foot->prev = mouth->prev;
    foot->next = mouth;

    if(mouth->prev != nullptr) {
        mouth->prev->next = foot;
    }

    mouth->prev = foot;
}

inline void insert_after(list_node* mouth, list_node* foot)
{
    foot->next = mouth->next;
    foot->prev = mouth;

    if(mouth->next != nullptr) {
        mouth->next->prev = foot;
    }

    mouth->next = foot;
}

int main()
{
    std::string s;

    std::cin >> s;

    std::vector<list_node> nodes(1000000);

    list_node* head = &nodes[0];

    head->value = 1;
    head->prev = nullptr;
    head->next = nullptr;

    list_node* prev_node = head;

    for(int i = 0; i < s.length() - 1; i++) {
        list_node* new_node = &nodes[i + 1];

        new_node->value = i + 2;
        new_node->prev = nullptr;
        new_node->next = nullptr;

        if(s[i] == 'l') {
            insert_before(prev_node, new_node);

            if(new_node->prev == nullptr) {
                head = new_node;
            }
        }
        else if(s[i] == 'r') {
            insert_after(prev_node, new_node);
        }

        prev_node = new_node;
    }

    while(head != nullptr) {
        printf("%d\n", head->value);

        head = head->next;
    }
}
