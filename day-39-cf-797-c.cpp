#include <iostream>
#include <vector>

int main()
{
    std::string s;

    std::cin >> s;

    std::vector<char> a_stack;

    for(size_t i = s.length(); i != 0; i--) {
        a_stack.push_back(s[i - 1]);
    }

    std::vector<char> b_stack;
    std::vector<char> c_stack;

    while(!a_stack.empty()) {
        c_stack.push_back((char&&)a_stack.back());

        a_stack.pop_back();
    }

    for(char c : c_stack) {
        std::cout << c;
    }

    std::cout << std::endl;
}
