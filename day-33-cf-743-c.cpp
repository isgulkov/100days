#include <iostream>

int main()
{
    int n;

    std::cin >> n;

    if(n != 1) {
        std::cout << n << " " << n + 1 << " " << n * (n + 1) << std::endl;
    }
    else {
        std::cout << -1 << std::endl;
    }
}
