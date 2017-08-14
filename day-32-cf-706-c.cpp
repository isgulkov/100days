#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int num_words;

    std::cin >> num_words;

    std::vector<int> reversal_costs((size_t)num_words);

    for(int i = 0; i < num_words; i++) {
        std::cin >> reversal_costs[i];
    }

    std::vector<std::string> words((size_t)num_words);

    for(int i = 0; i < num_words; i++) {
        std::cin >> words[i];
    }

    std::vector<std::string> reversed_words(words);

    for(std::string& w : reversed_words) {
        std::reverse(w.begin(), w.end());
    }

    /**
     * min_original[i] stores the minimum number of reversals required to achieve non-descending order of first (i + 1)
     * words with `i`th word not reversed (`INT32_MAX` if not achievable)
     */
    std::vector<long long> min_original((size_t)num_words);

    /**
     * Same, but with the `i`th word reversed
     */
    std::vector<long long> min_reversed((size_t)num_words);

    min_original[0] = 0;
    min_reversed[0] = reversal_costs[0];

    for(int i = 1; i < num_words; i++) {
        min_original[i] = INT64_MAX;

        if(words[i] >= words[i - 1]) {
            min_original[i] = std::min(min_original[i], min_original[i - 1]);
        }

        if(words[i] >= reversed_words[i - 1]) {
            min_original[i] = std::min(min_original[i], min_reversed[i - 1]);
        }

        min_reversed[i] = INT64_MAX;

        if(reversed_words[i] >= words[i - 1] && min_original[i - 1] != INT64_MAX) {
            min_reversed[i] = std::min(min_reversed[i], min_original[i - 1] + reversal_costs[i]);
        }

        if(reversed_words[i] >= reversed_words[i - 1] && min_reversed[i - 1] != INT64_MAX) {
            min_reversed[i] = std::min(min_reversed[i], min_reversed[i - 1] + reversal_costs[i]);
        }
    }

    long long result = std::min(min_original[num_words - 1], min_reversed[num_words - 1]);

    if(result != INT64_MAX) {
        std::cout << result << std::endl;
    }
    else {
        std::cout << -1 << std::endl;
    }
}
