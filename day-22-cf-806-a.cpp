#include <iostream>
#include <climits>

struct fraction
{
    int a, b;

    fraction(int a, int b) : a(a), b(b) { }
};

long long minimum_additions(fraction proj, fraction target)
{
    long long left = 1;
    long long right = LLONG_MAX / std::max(target.a, target.b);

    while(right != left) {
        long long mid = left + (right - left) / 2;

        long long num_diff = mid * target.a - proj.a;
        long long denom_diff = mid * target.b - proj.b;

        if(0 <= num_diff && num_diff <= denom_diff) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }

    if(left == LLONG_MAX / std::max(target.a, target.b)) {
        return -1;
    }
    else {
        return left * target.b - proj.b;
    }
}

int main()
{
    int t;

    std::cin >> t;

    while(t--) {
        int x, y, p, q;

        std::cin >> x >> y >> p >> q;

        fraction xy(x, y);
        fraction pq(p, q);

        std::cout << minimum_additions(xy, pq) << std::endl;
    }
}
