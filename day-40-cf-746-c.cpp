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
     * Time it takes for the tram to get to Igor's destination
     */
    int ride_time;

    if(tram_direction == 1 && tram_origin <= igor_origin) {
        /**
         * Tram catches Igor before reaching end of the line
         */

        ride_time = tram_pace * std::abs(tram_origin - igor_destination);

        if(igor_destination < tram_origin) {
            /**
             * Tram has to make a round-trip to the end of the line
             */

            ride_time += 2 * tram_pace * (tram_range - tram_origin);
        }
    }
    else if(tram_direction == -1 && tram_origin >= igor_origin) {
        /**
         * Tram catches Igor before reaching the beginning of the line
         */

        ride_time = tram_pace * std::abs(tram_origin - igor_destination);

        if(igor_destination > tram_origin) {
            /**
             * Tram has to make a round-trip to the beginning of the line
             */

            ride_time += 2 * tram_pace * tram_origin;
        }
    }
    else if(tram_direction == 1 && tram_origin > igor_origin) {
        /**
         * Tram has to make a round-trip to catch Igor
         */

        ride_time = tram_pace * ((tram_range - tram_origin) + tram_range + igor_destination);
    }
    else if(tram_direction == -1 && tram_origin < igor_destination) {
        /**
         * same
         */

        ride_time = tram_pace * (tram_origin + tram_range + (tram_range - igor_destination));
    }

    std::cout << std::min(walking_time, ride_time) << std::endl;
}
