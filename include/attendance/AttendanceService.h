#ifndef ATTENDANCE_SERVICE_H
#define ATTENDANCE_SERVICE_H

//#include <memory>
#include <stdexcept>
#include <string>
//#include <utility>

#include "AttendanceRegister.h"
#include "../capture/AttendanceCapture.h"
using namespace std;

class AttendanceService {
private:
    AttendanceCapture* capture;
    AttendanceRegister* attendance_register;
    int next_record_number;

public:
    AttendanceService(AttendanceRegister* register_pointer) {
        attendance_register = register_pointer;
        capture =nullptr;
        next_record_number = 1;
    }

    void setCapture(AttendanceCapture* new_capture) {
        capture = new_capture;
    }

    void runCapture(AttendanceSession& session) {
        if (attendance_register == nullptr) {
            throw runtime_error( "Attendance register is not available." );
        }

        if (capture == nullptr) {
            throw runtime_error("Attendance capture method is not selected.");
        }

        capture->beginSession(session);

        string student_ID = capture->captureNext();

        while (student_ID != "") {
            string record_ID ="RECORD" + to_string(next_record_number);

            attendance_register->markPresent(
                record_ID,
                student_ID,
                session.getId(),
                capture->getMethodName()
            );

            next_record_number++;

            student_ID = capture->captureNext();
        }

        capture->endSession();
    }
};

#endif