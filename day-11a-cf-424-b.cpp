#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <unordered_map>

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

    std::set<int> card_values;

    std::unordered_map<int, int> card_first_occurence;
    std::unordered_map<int, int> card_last_occurence;

    for(int i = 0; i < num_cards; i++) {
        int card_value = cards[i];

        card_values.insert(card_value);

        if(card_first_occurence.find(card_value) == card_first_occurence.end()) {
            card_first_occurence[card_value] = i;
        }

        card_last_occurence[card_value] = i;
    }

    for(int cv : card_values) {
        std::cout << cv << " ";
    }
}
