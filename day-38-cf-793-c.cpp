#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

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

    bool empty_area()
    {
        return (x_right - x_left) * (y_top - y_bottom) == 0;
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

            if(!std::isinf(intersect_x_left) && intersect_x_left >= 0) {
                /**
                 * Check if the path will intersect the segment of the left side of the trap, not just the line it lies
                 * on
                 */

                long double y_at_x_left = y_start + intersect_x_left * v_y;

                if(trap.y_bottom < y_at_x_left && y_at_x_left < trap.y_top) {
                    result.push_back(intersect_x_left);
                }
                if(v_x && v_y) {
                    if(y_at_x_left == trap.y_bottom && (v_x > 0 == v_y > 0)) {
                        /**
                         * Mouse comes in our out of the trap through bottom left corner
                         */
                        result.push_back(intersect_x_left);
                    }
                    else if(y_at_x_left == trap.y_top && (v_x > 0 == v_y < 0)) {
                        result.push_back(intersect_x_left);
                    }
                }
            }
        }

        {
            long double intersect_y_bottom = (trap.y_bottom - y_start) * 1.0L / v_y;

            if(!std::isinf(intersect_y_bottom) && intersect_y_bottom >= 0) {
                long double x_at_y_bottom = x_start + intersect_y_bottom * v_x;

                if(trap.x_left < x_at_y_bottom && x_at_y_bottom < trap.x_right) {
                    result.push_back(intersect_y_bottom);
                }
                if(v_x && v_y) {
                    if(x_at_y_bottom == trap.x_left && (v_x > 0 == v_y > 0)) {
                        result.push_back(intersect_y_bottom);
                    }
                    else if(x_at_y_bottom == trap.x_right && (v_x < 0 == v_y > 0)) {
                        result.push_back(intersect_y_bottom);
                    }
                }
            }
        }

        {
            long double intersect_x_right = (trap.x_right - x_start) * 1.0L / v_x;

            if(!std::isinf(intersect_x_right) && intersect_x_right >= 0) {
                long double y_at_x_right = y_start + intersect_x_right * v_y;

                if(trap.y_bottom < y_at_x_right && y_at_x_right < trap.y_top) {
                    result.push_back(intersect_x_right);
                }
                if(v_x && v_y) {
                    if(y_at_x_right == trap.y_bottom && (v_x < 0 == v_y > 0)) {
                        result.push_back(intersect_x_right);
                    }
                    else if(y_at_x_right == trap.y_top && (v_x < 0 == v_y < 0)) {
                        result.push_back(intersect_x_right);
                    }
                }
            }
        }

        {
            long double intersect_y_top = (trap.y_top - y_start) * 1.0L / v_y;

            if(!std::isinf(intersect_y_top) && intersect_y_top >= 0) {
                long double x_at_y_top = x_start + intersect_y_top * v_x;

                if(trap.x_left < x_at_y_top && x_at_y_top < trap.x_right) {
                    result.push_back(intersect_y_top);
                }
                if(v_x && v_y) {
                    if(x_at_y_top == trap.x_left && (v_x > 0 == v_y < 0)) {
                        result.push_back(intersect_y_top);
                    }
                    else if(x_at_y_top == trap.x_right && (v_x < 0 == v_y < 0)) {
                        result.push_back(intersect_y_top);
                    }
                }
            }
        }

        /**
         * Remove duplicates from the list.
         *
         * Duplicates happen only when path intersects corners. This duplicate corner intersection check could be done
         * when processing corner intersections, but it's simpler to do here
         */

        for(int i = 0; i < result.size(); i++) {
            for(int j = i + 1; j < result.size(); j++) {
                if(result[i] == result[j]) {
                    std::swap(result[j], result.back());

                    result.pop_back();
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
             * Mouse doesn't intersect the borders of the box, just either goes by the trap completely or starts inside
             * of it and doesn't move
             */

            in = 0.0L;
            out = HUGE_VALL;

            return starts_inside(trap);
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

    if(trap.empty_area()) {
        std::cout << -1 << std::endl;

        return 0;
    }

    std::vector<mouse> mice;

    for(int i = 0; i < num_mice; i++) {
        int x, y, vx, vy;

        std::cin >> x >> y >> vx >> vy;

        mice.push_back(mouse(x, y, vx, vy));
    }

    long double max_come_in = 0.0L;
    long double min_come_out = HUGE_VALL;

    for(mouse& m : mice) {
        long double in, out;

        bool trapped = m.comes_into_trap(trap, in, out);

        if(!trapped) {
            std::cout << -1 << std::endl;

            return 0;
        }
        else {
            if(in > max_come_in) {
                max_come_in = in;
            }

            if(out < min_come_out) {
                min_come_out = out;
            }
        }
    }

    if(max_come_in < min_come_out) {
        std::cout << std::setprecision(20) << max_come_in << std::endl;
    }
    else {
        std::cout << -1 << std::endl;
    }
}
