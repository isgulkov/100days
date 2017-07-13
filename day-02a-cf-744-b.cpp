#include <iostream>
#include <vector>

/*
 * Generates all numbers up to a certain number that have certain bit set or unset
 */
struct NumbersWithCertainBitValueGenerator
{
private:
    int bit_pos;
    bool bit_val;

    int max_state;

    int state = 0;

public:
    NumbersWithCertainBitValueGenerator(int up_to, int position, bool value)
        : max_state(up_to), bit_pos(position), bit_val(value)
    {
        move_to_next();
    }

    bool has_next()
    {
        return state < max_state;
    }

    int get_next()
    {
        int next = state++;

        move_to_next();

        return next;
    }

private:
    void move_to_next()
    {
        while(state < max_state && ((state >> bit_pos) & 1) != bit_val) {
            state += 1;
        }
    }
};

int main()
{
    int n;

    std::cin >> n;

    int minimums[20][2];

    for(int bit = 0; bit < 10; bit++) {
        for(int val = 0; val <= 1; val++) {
            NumbersWithCertainBitValueGenerator g(n, bit, (bool)val);

            std::vector<int> indices;
            indices.reserve(1000);

            while(g.has_next()) {
                indices.push_back(g.get_next());
            }

            std::cout << indices.size() << std::endl;

            for(int i : indices) {
                std::cout << i + 1 << " ";
            }

            std::cout << std::endl;
        }
    }

    std::cout << -1 << std::endl;

    for(int i = 0; i < n; i++) {
        std::cout << mins[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}
