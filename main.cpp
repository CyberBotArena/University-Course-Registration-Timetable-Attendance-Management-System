#include <iostream>
#include "include/scheduling/TimeSlot.h"

int main() {
    try {
        TimeSlot lecture(
            Day::Monday,
            9 * 60,
            11 * 60,
            "Room A"
        );

        std::cout << "Start: "
                  << lecture.getStartMinutes() << '\n';

        std::cout << "End: "
                  << lecture.getEndMinutes() << '\n';

        std::cout << "Location: "
                  << lecture.getLocation() << '\n';
    }
    catch (const invalid_argument& error) {
        std::cout << "Error: " << error.what() << '\n';
    }

    return 0;
}