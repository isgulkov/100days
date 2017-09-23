#include <iostream>
#include <vector>

struct request_t
{
    enum request_type { right_shift, reverse };

    request_type t;
    int l, r;
};

int main()
{
    std::ios_base::sync_with_stdio(false);

    int n, num_requests, num_positions;

    std::cin >> n >> num_requests >> num_positions;

    std::vector<int> initial_values((size_t)n);

    for(int i = 0; i < n; i++) {
        std::cin >> initial_values[i];
    }

    std::vector<request_t> requests((size_t)num_requests);

    for(int i = 0; i < num_requests; i++) {
        int t, l, r;

        std::cin >> t >> l >> r;

        requests[i] = {t == 1 ? request_t::request_type::right_shift : request_t::request_type::reverse, l, r};
    }

    std::vector<int> positions((size_t)num_positions);

    for(int i = 0; i < num_positions; i++) {
        std::cin >> positions[i];
    }


}
