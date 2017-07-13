#include <iostream>

int main()
{
    int n;

    std::cin >> n;

    // i know this is wrong, ok?

    int mins[20];

    for(int i = 0; i < n; i++) {
        std::cout << n << std::endl;

        for(int j = 0; j < n; j++) {
            if(j == i) {
                continue;
            }

            std::cout << j - 1 << " ";
        }

        std::cout << std::endl;

        for(int j = 0; j < n; j++) {
            int x;

            std::cin >> x;

            if(j == i) {
                mins[j] = x;
            }
        }
    }

    std::cout << -1 << std::endl;

    for(int i = 0; i < n; i++) {
        std::cout << mins[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}