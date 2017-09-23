#include <iostream>
#include <vector>

struct request_t
{
    int type, l, r;
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

        requests[i] = {t, l - 1, r - 1};
    }

    std::vector<int> positions((size_t)num_positions);

    for(int i = 0; i < num_positions; i++) {
        std::cin >> positions[i];

        positions[i] -= 1;
    }

    /*
     * Instead of performing the sequence of requests on the array elements, play the sequence back in reverse order on
     * the positions of interest. The resulting positions will be the positions in the initial array from which the
     * elements at positions of interest would have originated after the sequence would've been applied.
     *
     * This is possible because both subarray reverse and subarray shift are bijective operations.
     */
    for(auto it_request = requests.rbegin(); it_request != requests.rend(); it_request++) {
        int l = it_request->l;
        int r = it_request->r;

        if(it_request->type == 1) {
            for(int& p : positions) {
                if(p == l) {
                    p = r;
                }
                else if(l < p && p <= r) {
                    p -= 1;
                }
            }
        }
        else if(it_request->type == 2) {
            for(int& p : positions) {
                if(l <= p && p <= r) {
                    p = l + r - p;
                }
            }
        }
    }

    for(int p : positions) {
        std::cout << initial_values[p] << " ";
    }

    std::cout << std::endl;
}
