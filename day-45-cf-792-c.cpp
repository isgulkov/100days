#include <iostream>
#include <algorithm>

void print_skipping_indices(std::string& s, int i_skip, int j_skip)
{
    bool skip_leading_zeroes = (i_skip == 0);

    for(int i = 0; i < s.length(); i++) {
        if(i == i_skip || i == j_skip) {
            continue;
        }
        else if(skip_leading_zeroes && s[i] == '0') {
            continue;
        }
        else {
            skip_leading_zeroes = false;

            std::cout << s[i];
        }
    }

    if(skip_leading_zeroes) {
        /**
         * If after printing the whole number we're still skipping leading zeroes, it means that the whole number
         * consisted of leading zeroes and has been skipped — must leave at least one "0" behind for the number to be valid
         */

        std::cout << 0;
    }

    std::cout << std::endl;
}

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

    bool one_removal_possible = (i_one_removal != -1) && s.length() > 1;
    bool two_removals_possible = (i_two_removals_a != -1) && s.length() > 2;

    if(!one_removal_possible && !two_removals_possible) {
        if(there_are_zeroes) {
            std::cout << 0 << std::endl;
        }
        else {
            std::cout << -1 << std::endl;
        }
    }
    else if(!one_removal_possible) {
        print_skipping_indices(s, i_two_removals_a, i_two_removals_b);
    }
    else if(!two_removals_possible) {
        print_skipping_indices(s, i_one_removal, INT32_MIN);
    }
    else {
        /**
         * If both one removal and two removals are possible, check whichever one of them doesn't produce leading zeroes
         * (it can't be the case for both at the same time)
         */

        if(i_one_removal == 0 && s[1] == '0') {
            print_skipping_indices(s, i_two_removals_a, i_two_removals_b);
        }
        else {
            print_skipping_indices(s, i_one_removal, INT32_MIN);
        }
    }
}
