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
             * Every two adjacent odd elements can be turned into two even elements in one op. One odd element that
             * is adjacent to two even ones can be turned even in two ops
             */

            total_ops += (current_odd_streak + 1) / 2;
        }
    }

    total_ops += (current_odd_streak + 1) / 2;

    std::cout << "YES" << std::endl;

    std::cout << total_ops << std::endl;
}
