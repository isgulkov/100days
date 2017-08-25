#include <iostream>

int main()
{
    std::string s;

    std::cin >> s;

    for(char c : s) {
        std::cout << c;
    }

    std::cout << std::endl;
}
