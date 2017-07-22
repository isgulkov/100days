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

    std::unordered_map<int, std::set<int>> card_occurrences;

    for(int i = 0; i < num_cards; i++) {
        int card_value = cards[i];

        card_values.insert(card_value);

        if(card_occurrences.find(card_value) == card_occurrences.end()) {
            std::set<int> new_set;

            card_occurrences[card_value] = new_set;
        }

        card_occurrences[card_value].insert(i);
    }

    std::vector<bool> card_taken(num_cards, false);

    int total_inspections = 0;

    /**
     * Consider cards [top_card; n) be on top of the stack, [0; top_card) below them in the existing order
     */
    int top_card = 0;

    for(int card_value : card_values) {
        if(top_card <= *card_occurrences[card_value].begin()) {
            int last_occurrence = *card_occurrences[card_value].rbegin();

            /**
             * Count cards unmarked as taken in [top_card; last_occurrence] and mark `card_value` cards on this interval
             */

            int current_inspections = 0;

            for( ; top_card <= last_occurrence; top_card++) {
                if(!card_taken[top_card]) {
                    current_inspections += 1;

                    if(cards[top_card] == card_value) {
                        card_taken[top_card] = true;
                    }
                }
            }

            total_inspections += current_inspections;
        }
        else {
            /**
             * Find the occurrence previous to `top_card` (i.e. largest smaller than).
             *
             * Use `lower_bound` to find first greater than or equal, then decrease by one to get last smaller
             */
            int prev_occurrence = *(--card_occurrences[card_value].lower_bound(top_card));

            /**
             * Count all cards unmarked as taken on [top_card; num_cards) and [0; prev_occurence] and mark `card_value`
             * cards on these intervals
             */

            int current_inspections = 0;

            for( ; top_card < num_cards; top_card++) {
                if(!card_taken[top_card]) {
                    current_inspections += 1;

                    if(cards[top_card] == card_value) {
                        card_taken[top_card] = true;
                    }
                }
            }

            for(top_card = 0; top_card <= prev_occurrence; top_card++) {
                if(!card_taken[top_card]) {
                    current_inspections += 1;

                    if(cards[top_card] == card_value) {
                        card_taken[top_card] = true;
                    }
                }
            }

            total_inspections += current_inspections;
        }
    }

    std::cout << total_inspections << std::endl;
}
