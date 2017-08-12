#include <iostream>

int main()
{
    int n;

    std::cin >> n;

    int total_ops = 0;
    int current_odd_streak = 0;

    /**
     * Count the number of operations needed to turn every element even
     */

    while(n--) {
        int x;

        std::cin >> x;

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

    std::cout << "YES" << std::endl;

    std::cout << total_ops << std::endl;
}
