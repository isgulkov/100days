#include <iostream>
#include <vector>

int gcd(int a, int b)
{
    while(b) {
        a %= b;

        std::swap(a, b);
    }

    return a;
}

int main()
{
    int n;

    std::cin >> n;

    int total_ops = 0;
    int current_odd_streak = 0;

    std::vector<int> xs;

    while(n--) {
        int x;

        std::cin >> x;

        xs.push_back(x);
    }

    /**
     * Compute GCD of the numbers to check if it isn't one already
     */

    int common_gcd = xs[0];

    for(int x : xs) {
        common_gcd = gcd(common_gcd, x);
    }

    if(common_gcd > 1) {
        std::cout << "YES" << std::endl << 0 << std::endl;

        return 0;
    }

    /**
     * Count the number of operations needed to turn every element even
     */

    for(int x : xs) {
        if(x % 2 == 1) {
            current_odd_streak += 1;
        }
        else {
            /**
             * The following can be done to pairs of consecutive elements:
             *
             * 11 -> 00
             * 10 -> 11 -> 00
             * 01 -> 11 -> 00
             *
             * So for an odd-length streak of odd elements, the number of operations to turn it even is equal to that
             * for a streak one element longer than it, plus one.
             *
             * For even-length streaks of odd elements the number of ops is just floor(len / 2)
             */

            total_ops += (current_odd_streak + 1) / 2 + current_odd_streak % 2;

            current_odd_streak = 0;
        }
    }

    total_ops += (current_odd_streak + 1) / 2 + current_odd_streak % 2;

    std::cout << "YES" << std::endl << total_ops << std::endl;
}
