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
            int last_occurrence = card_last_occurrence[card_value];

            /**
             * Count untaken cards in [top_card; last_occurrence] and mark `card_value` cards on this interval as taken
             */

            int current_inspections = 0;

            for(int i = top_card; i <= card_last_occurrence[card_value]; i++) {
                if(!card_taken[i]) {
                    current_inspections += 1;

                    if(cards[i] == card_value) {
                        card_taken[i] = true;
                    }
                }
            }

            total_inspections += current_inspections;

            top_card = card_last_occurrence[card_value] + 1;
        }
        else {

        }
    }

    std::cout << total_inspections << std::endl;
}
