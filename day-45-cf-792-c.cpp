#include <iostream>
#include <algorithm>

int main()
{
    std::string s;

    std::cin >> s;

    /**
     * If `sum_digits` % 3 is 1, we need to remove either one "one" (digits comparable to 1 modulo 3) or two "twos".
     * Likewise, if `sum_digits` % 3 is 2, we need to remove either one "two" or two "ones".
     *
     * While calculating the sum of digits, remember all the indices necessary for those operations
     */

    int sum_digits = 0;

    int i_first_one = -1, i_second_one = -1;
    int i_first_two = -1, i_second_two = -1;

    /**
     * Remember if there are zero digits -- this way the number can always be made divisible by three if no other
     * options exist
     */
    bool there_are_zeroes = false;

    for(int i = (int)(s.length()) - 1; i >= 0; i--) {
        int d = s[i] - '0';

        sum_digits += d;

        /**
         * Traverse the string backwards to always not include index `0` if there are alternatives (its removal may
         * produce leading zeroes that need to be removed which increases cost)
         */

        if(d == 0) {
            there_are_zeroes = true;
        }

        if(d % 3 == 1) {
            if(i_second_one == -1) {
                i_second_one = i;
            }
            else if(i_first_one == -1) {
                i_first_one = i;
            }
        }
        else if(d % 3 == 2) {
            if(i_second_two == -1) {
                i_second_two = i;
            }
            else if(i_first_two == -1) {
                i_first_two = i;
            }
        }
    }

    int i_one_removal;
    int i_two_removals_a, i_two_removals_b;

    if(sum_digits % 3 == 1) {
        i_one_removal = i_second_one;

        i_two_removals_a = i_first_two;
        i_two_removals_b = i_second_two;
    }
    else if(sum_digits % 3 == 2) {
        i_one_removal = i_second_two;

        i_two_removals_a = i_first_one;
        i_two_removals_b = i_second_one;
    }
    else {
        /**
         * Number is already divisible by 3 — no need to remove any digits
         */

        std::cout << s << std::endl;

        return 0;
    }

//    std::cout << i_one_removal << std::endl;
//    std::cout << i_two_removals_a << " " << i_two_removals_b << std::endl;

    int l_zeroes_1 = 0;

    if(i_one_removal == 0) {
        for(l_zeroes_1 = 0; l_zeroes_1 < s.length() && s[1 + l_zeroes_1] == '0'; l_zeroes_1++) { }
    }

    int l_zeroes_2 = 0;

    if(i_two_removals_a == 0) {
        for(l_zeroes_2 = 0; l_zeroes_2 < s.length() && s[1 + l_zeroes_2] == '0'; l_zeroes_2++) { }
    }

    if(s.length() > 1 && i_one_removal != -1 && (l_zeroes_1 + 1 < l_zeroes_2 + 2 || i_two_removals_a == -1)) {
        int i = 0;

        if(l_zeroes_1 != 0) {
            i = std::min(l_zeroes_1 + 1, (int)s.length() - 1);
        }

        for( ; i < s.length(); i++) {
            if(i != i_one_removal) {
                std::cout << s[i];
            }
        }

        std::cout << std::endl;
    }
    else if(s.length() > 2 && i_two_removals_a != -1 && (l_zeroes_2 + 2 <= l_zeroes_1 + 1 || i_one_removal == -1)) {
        int i = 0;

        if(l_zeroes_2 != 0) {
            i = l_zeroes_2 + 1;
        }

        for( ; i < s.length(); i++) {
            if(i != i_two_removals_a && i != i_two_removals_b) {
                std::cout << s[i];
            }
        }

        std::cout << std::endl;
    }
    else {
        if(there_are_zeroes) {
            std::cout << 0 << std::endl;
        }
        else {
            std::cout << -1 << std::endl;
        }
    }
}
