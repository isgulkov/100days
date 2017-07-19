#include <iostream>
#include <list>
#include <string>
#include <stdio.h>

int main()
{
    std::string s;

    std::cin >> s;

    std::list<int> stones = { 1 };

    auto last_node = stones.begin();

    for(int i = 0; i < s.length() - 1; i++) {
        if(s[i] == 'r') {
            /**
             * Increment iterator so that we insert the new node after the last node instead of before it
             */
            last_node++;
        }

        last_node = stones.insert(last_node, i + 2);
    }

    for(auto it = stones.begin(); it != stones.end(); it++) {
        printf("%d\n", *it);
    }
}
