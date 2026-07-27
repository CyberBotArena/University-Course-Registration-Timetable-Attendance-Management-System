#ifndef ATTENDANCE_CAPTURE_H
#define ATTENDANCE_CAPTURE_H

#include <string>

#include "../attendance/AttendanceSession.h"
using namespace std;

class AttendanceCapture {
public:
    virtual void beginSession(const AttendanceSession& session) = 0;

    virtual string captureNext() = 0;

    virtual void endSession() = 0;

    virtual string getMethodName() const = 0;

    virtual ~AttendanceCapture() = default;
};

#endif