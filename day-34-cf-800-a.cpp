#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>

class devices
{
    std::vector<int> power;
    std::vector<int> initial_charge;

    int num_devices;
    int charge_power;

public:
    devices(int charge_power) : num_devices(0), charge_power(charge_power) { }

    void add_device(int p, int c)
    {
        power.push_back(p);
        initial_charge.push_back(c);

        num_devices += 1;
    }

    bool can_work_indefinitely()
    {
        long long total_power = std::accumulate(power.begin(), power.end(), 0LL);

        return total_power <= charge_power;
    }

    bool can_work_for(long double time)
    {
        /**
         * For each device, calculate the minimum time it has to be charged during `time` to keep it alive, and sum
         * those up
         */

        long double total_min_charing_time = 0.0L;

        for(int i = 0; i < num_devices; i++) {
            long double min_charging_time = (time * power[i] - initial_charge[i]) / charge_power;

            total_min_charing_time += std::max(0.0L, min_charging_time);
        }

        /**
         * If the total time devices have to be charged is greater than `time`, the devices can't work for `time`
         */

        return total_min_charing_time <= time;
    }
};

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

    std::cout << l + (r - l) / 2.0L << std::endl;
}
