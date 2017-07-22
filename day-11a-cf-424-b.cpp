#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <unordered_map>

int main()
{
    size_t num_cards;

    std::cin >> num_cards;

    std::vector<int> cards;

    for(int i = 0; i < num_cards; i++) {
        int card;

        scanf("%d", &card);

        cards.push_back(card);
    }

    std::set<int> card_values;

    std::unordered_map<int, int> card_first_occurrence;
    std::unordered_map<int, int> card_last_occurrence;

    for(int i = 0; i < num_cards; i++) {
        int card_value = cards[i];

        card_values.insert(card_value);

        if(card_first_occurrence.find(card_value) == card_first_occurrence.end()) {
            card_first_occurrence[card_value] = i;
        }

        card_last_occurrence[card_value] = i;
    }

    std::vector<bool> card_taken(num_cards, false);

    int total_inspections = 0;

    /**
     * Consider cards [top_card; n) be on top of the stack, [0; top_card) below them in the existing order
     */
    int top_card = 0;

    for(int card_value : card_values) {
        if(top_card <= card_first_occurrence[card_value]) {
            total_inspections += card_last_occurrence[card_value] - top_card + 1;

            top_card = card_last_occurrence[card_value] + 1;
        }
        else {
            total_inspections += num_cards - top_card;
            total_inspections += card_first_occurrence[card_value] + 1;

            top_card = card_first_occurrence[card_value] + 1;
        }
    }

    std::cout << total_inspections << std::endl;
}
