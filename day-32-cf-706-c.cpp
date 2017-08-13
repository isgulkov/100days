#include <iostream>
#include <vector>

int main()
{
    int num_words;

    std::cin >> num_words;

    std::vector<int> costs((size_t)num_words);

    for(int i = 0; i < num_words; i++) {
        std::cin >> costs[i];
    }

    std::vector<std::string> words((size_t)num_words);

    for(int i = 0; i < num_words; i++) {
        std::cin >> words[i];
    }

    for(std::string w : words) {
        std::cout << w << std::endl;
    }
}
