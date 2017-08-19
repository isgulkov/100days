#include <iostream>
#include <vector>

class mouse
{
    int x_start, y_start;
    int v_x, v_y;

public:
    mouse(int x_start, int y_start, int v_x, int v_y) : x_start(x_start), y_start(y_start), v_x(v_x), v_y(v_y) { }

    bool comes_into_trap(rect& trap, long double& in, long double& out)
    {
        return false;
    }
};

class rect
{
    int x_left, y_bottom, x_right, y_top;

public:
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
