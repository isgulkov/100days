#include <iostream>

bool express_as_sum_of_3_fractions(int n, long long& x, long long& y, long long& z)
{
    /**
     * Iterating over sums of the three indices first allows to traverse the cube "slice by slice" starting from the
     * origin, thus encountering the smaller and thus more likely triples earlier
     */

    for(int sum_indices = 3; sum_indices <= 1000 * 1000 * 1000; sum_indices++) {
        for(x = 1; x <= sum_indices - 2; x++) {
            for(y = 1; y <= sum_indices - 1 - x; y++) {
                if(y == x) {
                    continue;
                }

                z = sum_indices - x - y;

                if(z == x || z == y) {
                    continue;
                }

                long long num = 2 * x * y * z;

                long long denom = x * y + x * z + y * z;

                if(num % denom == 0 && num / denom == n) {
                    return true;
                }
            }
        }
    }

    return false;
}

int main()
{
    int n;

    std::cin >> n;

    long long x, y, z;

    if(express_as_sum_of_3_fractions(n, x, y, z)) {
        std::cout << x << " " << y << " " << z << std::endl;
    }
    else {
        std::cout << -1 << std::endl;
    }
}
