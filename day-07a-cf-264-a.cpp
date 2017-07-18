#include <iostream>
#include <map>
#include <string>

int main()
{
    std::string s;

    std::cin >> s;

    std::map<double, int> masik;

    double left = 0.0, right = 1.0;

    for(int i = 0; i < s.length(); i++) {
        double mid = (right + left) / 2.0;

        masik[mid] = i + 1;

        if(s[i] == 'l') {
            right = mid;
        }
        else if(s[i] == 'r') {
            left = mid;
        }
    }

    for(auto it = masik.begin(); it != masik.end(); it++) {
        std::cout << it->second << std::endl;
    }
}
