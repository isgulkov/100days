#include <iostream>

int main()
{
    int tram_range, igor_origin, igor_destination;

    std::cin >> tram_range >> igor_origin >> igor_destination;

    int tram_pace, igor_pace;

    std::cin >> tram_pace >> igor_pace;

    int tram_origin, tram_direction;

    std::cin >> tram_origin >> tram_direction;

    /**
     * Time it takes Igor to walk to his destination by foot
     */
    int walking_time = std::abs(igor_origin - igor_destination) * igor_pace;

    /**
     * Time it takes for Igor and the tram to meet and then for the tram to reach Igor's destination
     */
    int ride_time;

    {
        int time_meet_left = 1000;

        int time_meet_right = 1000;

        ride_time = std::min(time_meet_left, time_meet_right);
    }

    std::cout << std::min(walking_time, ride_time) << std::endl;
}
