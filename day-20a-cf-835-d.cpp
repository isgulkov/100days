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

    for(int i = 0; i < s.length(); i++) {
        max_palindrome_degree[i][i] = 1;
    }

    num_palidromes[0] = (int)s.length();

    /**
     * Update max palindrome degree values for substrings in order of increasing length
     */
    for(size_t substr_length = 2; substr_length <= s.length(); substr_length++) {
        for(size_t l = 0; l <= s.length() - substr_length; l++) {
            size_t r = l + substr_length - 1;

            size_t mid = (l + r) / 2;

            /**
             * If string length is odd, include middle symbol in neither half
             */
            size_t left_half_end = substr_length % 2 == 1 ? mid - 1 : mid;

            size_t right_half_start = mid + 1;

            if(s.compare(l, substr_length / 2, s, right_half_start, substr_length / 2) != 0) {
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

                for(int i = 0; i < max_palindrome_degree[l][r]; i++) {
                    num_palidromes[i] += 1;
                }
            }
        }
    }

    for(int n : num_palidromes) {
        std::cout << n << " ";
    }

    std::cout << std::endl;
}
