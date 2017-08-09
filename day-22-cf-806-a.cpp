#include <iostream>

struct fraction
{
    int a, b;

    fraction(int a, int b) : a(a), b(b) { }
};

int minimum_additions(fraction proj, fraction target)
{
    int left = 1;
    int right = INT32_MAX / std::max(target.a, target.b);

    while(right - left > 1) {
        int mid = left + (right - left) / 2;

        int num_diff = mid * target.a - proj.a;
        int denom_diff = mid * target.b - proj.b;

        if(0 <= num_diff && num_diff <= denom_diff) {
            right = mid;
        }
        else {
            left = mid;
        }
    }

    if(right * target.a - proj.a > right * target.b - proj.b) {
        return -1;
    }
    else {
        return right * target.b - proj.b;
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
