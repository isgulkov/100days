#include <iostream>

int minimum_additions(int a, int b, int p, int q)
{
    return 1;
}

int main()
{
    int t;

    std::cin >> t;

    while(t--) {
        int a, b, p, q;

        std::cin >> a >> b >> p >> q;

        std::cout << minimum_additions(a, b, p, q) << std::endl;
    }
}
