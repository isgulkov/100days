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
     * Time it takes Igor to ride the tram to his destination
     *
     * Suppose Igor will wait for the tram at `igor_origin` -- there is no point to chase the tram because the time it
     * takes for the tram to reach Igor's destination doesn't depend on it
     */
    int ride_time;

    /**
     * Calculate the time it takes the tram to reach `igor_origin`
     */

    if(tram_direction == 1 && tram_origin > igor_origin) {
        /**
         * Got to make a round-trip to the end of the line
         */

        ride_time = tram_pace * ((tram_range - tram_origin) + (tram_range - igor_origin));

        tram_direction *= -1;
    }
    else if(tram_direction == -1 && tram_origin < igor_origin) {
        /**
         * Got to make a round-trip to the beginning of the line
         */

        ride_time = tram_pace * (tram_origin + igor_origin);

        tram_direction *= -1;
    }
    else {
        /**
         * No round-trip required
         */

        ride_time = tram_pace * std::abs(tram_origin - igor_origin);
    }

    /**
     * Add the time it now takes the tram to reach `igor_destination` from `igor_origin`
     */

    if(tram_direction == 1 && igor_origin > igor_destination) {
        ride_time += tram_pace * ((tram_range - igor_origin) + (tram_range - igor_destination));
    }
    else if(tram_direction == -1 && igor_origin < igor_destination) {
        ride_time += tram_pace * (igor_origin + igor_destination);
    }
    else {
        ride_time += tram_pace * std::abs(igor_origin - igor_destination);
    }

    std::cout << std::min(walking_time, ride_time) << std::endl;
}
