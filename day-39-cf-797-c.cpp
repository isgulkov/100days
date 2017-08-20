#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::string s;

    std::cin >> s;

    int num_chars = (int)s.length();

    std::vector<char> a_stack;

    for(size_t i = s.length(); i != 0; i--) {
        a_stack.push_back(s[i - 1]);
    }

    /**
     * Store positions of all occurrences of each characters in the "a" stack counting from the bottom, in order from
     * top to bottom
     */

    std::vector<std::vector<int>> occurrences(26);

    for(int i = (int)a_stack.size() - 1; i >= 0; i--) {
        occurrences[a_stack[i] - 'a'].push_back(i);
    }

    std::vector<char> b_stack;
    std::vector<char> c_stack;

    char next_min_char;

    for(next_min_char = 'a'; occurrences[next_min_char - 'a'].empty(); next_min_char++) { }

    int next_occurrence_index = 0;

    while(!a_stack.empty()) {
        while(a_stack.size() > occurrences[next_min_char - 'a'][next_occurrence_index]) {
            b_stack.push_back(a_stack.back());

            a_stack.pop_back();
        }

        c_stack.push_back(b_stack.back());

        b_stack.pop_back();

        next_occurrence_index += 1;

        if(a_stack.empty()) {
            break;
        }

        while(next_occurrence_index == occurrences[next_min_char - 'a'].size()) {
            for(next_min_char += 1; occurrences[next_min_char - 'a'].empty(); next_min_char++) { }

            while(b_stack.back() == next_min_char) {
                c_stack.push_back(b_stack.back());

                b_stack.pop_back();
            }

            while(occurrences[next_min_char - 'a'][next_occurrence_index] >= a_stack.size()
                  && next_occurrence_index >= occurrences[next_min_char - 'a'].size()) {
                next_occurrence_index += 1;
            }
        }
    }

    while(!b_stack.empty()) {
        c_stack.push_back(b_stack.back());

        b_stack.pop_back();
    }

    for(char c : c_stack) {
        std::cout << c;
    }

    std::cout << std::endl;
}
