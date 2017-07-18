#include <iostream>
#include <list>
#include <string>

int main()
{
    std::string s;

    std::cin >> s;

    std::list<int> masik;

    masik.push_front(1);

    auto prev_element = masik.begin();

    for(int i = 0; i < s.length() - 1; i++) {
        if(s[i] == 'r') {
            prev_element++;
        }

        prev_element = masik.insert(prev_element, i + 2);
    }

    for(auto it = masik.begin(); it != masik.end(); it++) {
        std::cout << *it << std::endl;
    }
}
