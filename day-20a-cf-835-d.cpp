#include <iostream>
#include <vector>

int main()
{
    std::string s;

    std::cin >> s;

    std::vector<int> num_palidromes(s.length(), 0);

    std::vector<std::vector<int>> max_palindrome_degree(s.length(), std::vector<int>(s.length()));

    /**
     * Declare substrings of length one 1-palindromes
     */

    for(int i = 1; i < s.length(); i++) {
        max_palindrome_degree[i - 1][i] = 1;
    }

    /**
     * Update max palindrome degree values for substrings in order of increasing length
     */
    for(size_t substr_length = 2; substr_length <= s.length(); substr_length++) {
        for(size_t l = 0; l < s.length() - substr_length; l++) {
            size_t r = l + substr_length;

            size_t mid = (l + r) / 2;

            /**
             * If string length is odd, include middle symbol in neither half
             */
            size_t left_half_end = (r - l) % 2 == 1 ? mid - 1 : mid;

            size_t right_half_start = mid + 1;

            if(!s.compare(l, substr_length / 2, s, mid + 1, substr_length / 2)) {
                /**
                 * If two halves of the substring aren't equal, the substring isn't a k-palindrome
                 */

                max_palindrome_degree[l][r] = 0;
            }
            else {
                max_palindrome_degree[l][r] = 1 + std::min(
                        max_palindrome_degree[l][left_half_end],
                        max_palindrome_degree[right_half_start][r]
                );

                num_palidromes[max_palindrome_degree[l][r] - 1] += 1;
            }
        }
    }

    for(int n : num_palidromes) {
        std::cout << n << " ";
    }

    std::cout << std::endl;
}
