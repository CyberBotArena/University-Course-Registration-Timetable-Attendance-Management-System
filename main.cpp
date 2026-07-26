#include <iostream>
#include "include/attendance/AttendanceSession.h"

int main() {
    try {
        TimeSlot lectureSlot(
            Day::Monday,
            9 * 60,
            11 * 60,
            "Room A"
        );

        AttendanceSession session(
            "SESSION001",
            "OFFERING001",
            "LECTURER001",
            lectureSlot,
            60
        );

        std::cout << "Session ID: "
                  << session.getId() << '\n';

        std::cout << "Offering ID: "
                  << session.getOfferingId() << '\n';

        std::cout << "Session open: "
                  << std::boolalpha
                  << session.isOpen() << '\n';

        session.close();

        std::cout << "Session open after closing: "
                  << session.isOpen() << '\n';
    }
    catch (const std::invalid_argument& error) {
        std::cout << "Error: "
                  << error.what() << '\n';
    }

    return 0;
}