#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>

class devices
{
    std::vector<int> power;
    std::vector<int> initial_charge;

    int charge_power;

public:
    devices(int charge_power) : charge_power(charge_power) { }

    void add_device(int p, int c)
    {
        power.push_back(p);
        initial_charge.push_back(c);
    }

    bool can_work_indefinitely()
    {
        long long total_power = std::accumulate(power.begin(), power.end(), 0LL);

        return total_power <= charge_power;
    }

    bool can_work_for(long double time)
    {
        return true;
    }
};

bool possible_to_work_for(double time, std::vector<int>& power, std::vector<int>& initial_charge)
{
    return true;
}

int main()
{
    int num_devices, charge_power;

    std::cin >> num_devices >> charge_power;

    devices ds(charge_power);

    for(int i = 0; i < num_devices; i++) {
        int power, initial_charge;

        std::cin >> power >> initial_charge;

        ds.add_device(power, initial_charge);
    }

    if(ds.can_work_indefinitely()) {
        std::cout << -1 << std::endl;

        return 0;
    }

    long double l = 0.0L, r = 1000.0L * 1000.0L * 1000.0L;

    while(r - l > 0.001L * 0.001L * 0.001L) {
        long double mid = l + (r - l) / 2.0L;

        if(ds.can_work_for(mid)) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    std::cout << std::ios::fixed << std::setprecision(20) << l << std::endl;
}
