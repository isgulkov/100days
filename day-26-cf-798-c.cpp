#include <iostream>

int ops_for_streak(int len)
{
    /**
     * Every two adjacent odd elements can be turned into two even elements in one op. One odd element that
     * is adjacent to two even ones can be turned even in two ops
     *
     * So odd streak of odd length contributes 2 more ops than a streak that is one element shorter
     */

    return len / 2 + (len % 2) * 2;
}

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
            total_ops += ops_for_streak(current_odd_streak);
        }
    }

    total_ops += ops_for_streak(current_odd_streak);

    std::cout << "YES" << std::endl;

    std::cout << total_ops << std::endl;
}
