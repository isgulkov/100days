#include <iostream>
#include <stdio.h>
#include <vector>

int main()
{
    int num_cards;

    std::cin >> num_cards;

    std::vector<int> cards;

    for(int i = 0; i < num_cards; i++) {
        int card;

        scanf("%d", &card);

        cards.push_back(card);
    }

    for(int i = 0; i < num_cards; i++) {
        std::cout << cards[i] << " ";
    }
}
