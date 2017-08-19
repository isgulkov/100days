#include <iostream>
#include <vector>
#include <algorithm>

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
    std::vector<long double> get_intersection_points(rect& trap)
    {
        std::vector<long double> result;

        result.reserve(2);

        /**
         * Find points in time when the mouse's path will intersect sides of the trap (lines), then check if it will
         * intersect the actual segments
         */

        {
            long double intersect_x_left = (trap.x_left - x_start) * 1.0L / v_x;

            if(intersect_x_left >= 0) {
                /**
                 * Check if the path will intersect the segment of the left side of the trap, not just the line it lies
                 * on
                 */
                long double y_at_x_left = y_start + intersect_x_left * v_y;

                if(trap.y_bottom < y_at_x_left && y_at_x_left < trap.y_top) {
                    result.push_back(intersect_x_left);
                }
            }
        }

        {
            long double intersect_y_bottom = (trap.y_bottom - y_start) * 1.0L / v_y;

            if(intersect_y_bottom >= 0) {
                long double x_at_y_bottom = x_start + intersect_y_bottom * v_x;

                if(trap.x_left < x_at_y_bottom && x_at_y_bottom < trap.x_right) {
                    result.push_back(intersect_y_bottom);
                }
            }
        }

        {
            long double intersect_x_right = (trap.x_right - x_start) * 1.0L / v_x;

            if(intersect_x_right >= 0) {
                /**
                 * Check if the path will intersect the segment of the left side of the trap, not just the line it lies
                 * on
                 */
                long double y_at_x_right = y_start + intersect_x_right * v_y;

                if(trap.y_bottom < y_at_x_right && y_at_x_right < trap.y_top) {
                    result.push_back(intersect_x_right);
                }
            }
        }

        {
            long double intersect_y_top = (trap.y_top - y_start) * 1.0L / v_y;

            if(intersect_y_top >= 0) {
                long double x_at_y_top = x_start + intersect_y_top * v_x;

                if(trap.x_left < x_at_y_top && x_at_y_top < trap.x_right) {
                    result.push_back(intersect_y_top);
                }
            }
        }

        std::sort(result.begin(), result.end());

        return result;
    }

public:
    mouse(int x_start, int y_start, int v_x, int v_y) : x_start(x_start), y_start(y_start), v_x(v_x), v_y(v_y) { }

    bool comes_into_trap(rect& trap, long double& in, long double& out)
    {
        std::vector<long double> intersection_points = get_intersection_points(trap);

        if(intersection_points.size() == 0) {
            /**
             * Mouse goes by the trap completely
             */

            return false;
        }
        else if(intersection_points.size() == 1) {
            /**
             * Mouse starts in the trap and goes out of it
             */

            in = 0.0L;
            out = intersection_points[0];

            return true;
        }
        else {
            /**
             * Mouse starts outside and goes in and out of the trap
             */

            in = intersection_points.front();
            out = intersection_points.back();

            return true;
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

    for(mouse& m : mice) {
        long double a, b;

        if(m.comes_into_trap(trap, a, b)) {
            std::cout << "1 " << a << " " << b << std::endl;
        }
        else {
            std::cout << "0" << std::endl;
        }
    }
}
