#include <iostream>
#include <vector>

int main()
{
    int num_devices, charge_power;

    std::cin >> num_devices >> charge_power;

    std::vector<int> power((size_t)num_devices);
    std::vector<int> initial_charge((size_t)num_devices);

    for(int i = 0; i < num_devices; i++) {
        std::cin >> power[i] >> initial_charge[i];
    }

    
}
