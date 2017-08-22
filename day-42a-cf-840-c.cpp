#include <iostream>
#include <vector>
#include <cmath>

bool is_square(int64_t x)
{
    int64_t l = 0;
    int64_t r = (int64_t)sqrt(x);

    while(l != r) {
        int64_t mid = l + (r - l) / 2;

        if(mid * mid > x) {
            r = mid - 1;
        }
        else if(mid * mid < x) {
            l = mid + 1;
        }
        else {
            return true;
        }
    }

    return l * l == x;
}

int main()
{
    int num_items;

    std::cin >> num_items;

    std::vector<int> xs((size_t)num_items);

    for(int i = 0; i < num_items; i++) {
        std::cin >> xs[i];
    }

    std::vector<int> x_groups((size_t)num_items, -1);

    int num_groups = 0;

    for(int i = 0; i < num_items; i++) {
        if(x_groups[i] != -1) {
            continue;
        }

        x_groups[i] = num_groups;

        for(int j = i + 1; j < num_items; j++) {
            long long product = 1LL * xs[i] * xs[j];

            if(is_square(product)) {
                x_groups[j] = num_groups;
            }
        }

        num_groups += 1;
    }

    for(int g : x_groups) {
        std::cout << g << " ";
    }

    std::cout << std::endl;
}
