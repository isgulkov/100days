#include <iostream>

bool express_as_sum_of_3_fractions(int n, long long& x, long long& y, long long& z)
{
    /**
     * Iterating over sums of the first two indices first allows to traverse the plane "slice by slice" starting from
     * the origin, thus encountering the smaller and thus more likely doubles earlier
     */

    for(int sum_indices = 2; sum_indices <= 1000 * 1000 * 1000; sum_indices++) {
        for(x = 1; x <= sum_indices - 1; x++) {
            y = sum_indices - x;

            if(x == y) {
                continue;
            }

            /**
             * Try to solve "2/n = 1/x + 1/y + 1/z" for z.
             */

            long long num = n * x * y;

            long long denom = 2 * x * y - n * (x + y);

            if(num % denom != 0) {
                continue;
            }

            z = num / denom;

            if(z > 0 && z != x && z != y) {
                return true;
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
