#include <iostream>
#include <vector>
#include <algorithm>

class mouse
{
    int x_start, y_start;
    int v_x, v_y;

    bool starts_inside(rect& trap)
    {
        return trap.x_left < x_start && x_start < trap.x_right && trap.y_bottom < y_start && y_start < trap.y_top;
    }

    /**
     * Returns vector of all points in time when path of the mouse intersects with some of the lines that form the
     * trap's rectangle
     */
    std::vector<long double> intersection_points(rect& trap)
    {
        long double intersect_x_left = (trap.x_left - x_start) * 1.0L / v_x;

        long double intersect_y_bottom = (trap.y_bottom - y_start) * 1.0L / v_y;

        long double intersect_x_right = (trap.x_right - x_start) * 1.0L / v_x;

        long double intersect_y_top = (trap.y_top - y_start) * 1.0L / v_y;

        std::vector<long double> result;

        result.reserve(4);

        for(long double t : { intersect_x_left, intersect_y_bottom, intersect_x_right, intersect_y_top }) {
            if(t >= 0) {
                result.push_back(t);
            }
        }

        std::sort(result.begin(), result.end());

        return result;
    }

public:
    mouse(int x_start, int y_start, int v_x, int v_y) : x_start(x_start), y_start(y_start), v_x(v_x), v_y(v_y) { }

    bool comes_into_trap(rect& trap, long double& in, long double& out)
    {
        return false;
    }
};

struct rect
{
    int x_left, y_bottom, x_right, y_top;

    rect(int x_one, int y_one, int x_another, int y_another)
    {
        x_left = x_one;
        x_right = x_another;

        if(x_left > x_right) {
            std::swap(x_left, x_right);
        }

        y_bottom = y_one;
        y_top = y_another;

        if(y_bottom > y_top) {
            std::swap(y_bottom, y_top);
        }
    }
};

int main()
{
    int num_mice;

    std::cin >> num_mice;

    int x_one, y_one, x_another, y_another;

    std::cin >> x_one >> y_one >> x_another >> y_another;

    rect trap(x_one, y_one, x_another, y_another);

    std::vector<mouse> mice;

    for(int i = 0; i < num_mice; i++) {
        int x, y, vx, vy;

        std::cin >> x >> y >> vx >> vy;

        mice.push_back(mouse(x, y, vx, vy));
    }


}
