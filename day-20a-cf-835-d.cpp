#include <iostream>
#include <vector>

int main()
{
    std::string s;

    std::cin >> s;

    std::vector<int> num_palidromes(s.length(), 0);

    std::vector<std::vector<int>> max_palindrome_degree(s.length(), std::vector<int>(s.length()));

    /**
     * Update max palindrome degree values for substrings in order of increasing length
     */
    for(int i = 0; i < s.length(); i++) {
        max_palindrome_degree[i][i] = 1;
    }

    num_palidromes[0] = (int)s.length();

    for(int i = 1; i < s.length(); i++) {
        if(s[i - 1] == s[i]) {
            max_palindrome_degree[i - 1][i] = 2;

            num_palidromes[1] += 1;
        }
        else {
            max_palindrome_degree[i - 1][i] = 0;
        }
    }

    for(size_t substr_length = 3; substr_length <= s.length(); substr_length++) {
        for(size_t l = 0; l <= s.length() - substr_length; l++) {
            size_t r = l + substr_length - 1;

            size_t mid = (l + r) / 2;

            if(s[l] != s[r] || max_palindrome_degree[l + 1][r - 1] == 0) {
                /**
                 * This substring isn't a 1-palindrome (regular palindrome), and therefore, not any k-palindrome at all
                 * (as any k-palindrome is also a (k-1)-palindrome).
                 *
                 * Second clause: suppose [l; r] is a 1-palindrome, then (l; r) would also be at least a 1-palindrome,
                 * which it isn't
                 */

                max_palindrome_degree[l][r] = 0;
            }
            else {
                /**
                 * This substring is at least a 1-palindrome
                 */

                size_t left_half_end = substr_length % 2 ? mid - 1 : mid;

                int max_degree = 1 + std::min(
                        max_palindrome_degree[l][left_half_end],
                        max_palindrome_degree[mid + 1][r]
                );

                max_palindrome_degree[l][r] = max_degree;

                num_palidromes[max_degree - 1] += 1;
            }
        }
    }

    /**
     * Account for every k-palindrome also as a (k-1)-palindrome
     */
    for(size_t i = s.length() - 1; i > 0; i--) {
        num_palidromes[i - 1] += num_palidromes[i];
    }

    for(int n : num_palidromes) {
        std::cout << n << " ";
    }

    std::cout << std::endl;
}
