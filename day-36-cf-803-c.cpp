#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    long long sum, size;

    std::cin >> sum >> size;

    /**
     * If the sum of numbers 1 to n is greater than sum, there isn't a strictly increasing sequence of positive numbers
     * of given size with given sum of elements
     *
     * First clause is added to avoid "size * (size + 1)" overflowing in 64-bit integer. Maximum `size` that can fit
     * into the second equation with `sum` <= 10^10 is about 141 000 anyway
     */
    if(size > 1 * 1000 * 1000 * 1000 || size * (size + 1) / 2 > sum) {
        std::cout << -1 << std::endl;

        return 0;
    }


}
