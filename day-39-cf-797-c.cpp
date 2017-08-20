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

    for(char c : c_stack) {
        std::cout << c;
    }

    std::cout << std::endl;
}
