#include <iostream>
#include "include/attendance/AttendanceRegister.h"

int main() {
    try {
        TimeSlot slot(
            Day::Monday,
            9 * 60,
            11 * 60,
            "Room A"
        );

        AttendanceSession session(
            "SESSION001",
            "OFFERING001",
            "LECTURER001",
            slot,
            60
        );

        AttendanceRegister attendanceRegister;

        attendanceRegister.addSession(session);

        attendanceRegister.markPresent(
            "RECORD001",
            "STUDENT001",
            "SESSION001",
            "Card Tap"
        );

        std::cout << "Number of records: "
                  << attendanceRegister.getRecords().size()
                  << '\n';

        const AttendanceRecord* savedRecord =
            attendanceRegister.findRecord("RECORD001");

        if (savedRecord != nullptr) {
            std::cout << "Student ID: "
                      << savedRecord->getStudentID()
                      << '\n';

            if (savedRecord->getStatus() ==
                AttendanceStatus::Present) {
                std::cout << "Status: Present\n";
            }
        }
    }
    catch (const std::exception& error) {
        std::cout << "Error: "
                  << error.what()
                  << '\n';
    }

    return 0;
}