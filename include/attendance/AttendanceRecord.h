#ifndef ATTENDANCE_RECORD_H
#define ATTENDANCE_RECORD_H

#include <chrono>
#include <stdexcept>
#include <string>
using namespace std;

enum AttendanceStatus{
    Present,
    Absent,
    Late,
    Excused
};

class AttendanceRecord {
    private:
    string record_ID;
    string student_ID;
    string session_ID;

    chrono::system_clock::time_point time_stamp;

    AttendanceStatus status;
    string capture_method;

    //used when correction appear
    string correction_of;
    string acting_lecturer_ID;
    string reason;

    public:
    AttendanceRecord(
        const string& record_ID,
        const string& student_ID,
        const string& sessoion_ID,
        AttendanceStatus status,
        const string& capture_method,
        const string correction_of = " ",
        const string acting_lecturer_ID = " ",
        const string reason = " "
    ) 
    : record_ID(record_ID),
    student_ID(student_ID),
    session_ID(session_ID),
    time_stamp(chrono::system_clock::now()),
    status(status),
    capture_method(capture_method),
    correction_of(correction_of),
    acting_lecturer_ID(acting_lecturer_ID),
    reason(reason)
    {
        if(record_ID.empty())
        {
            throw invalid_argument("Record ID caannot be empty.");
        }

        if(student_ID.empty())
        {
            throw invalid_argument("Student ID caannot be empty.");
        }

        if(session_ID.empty())
        {
            throw invalid_argument("Session ID caannot be empty.");
        }

        if(capture_method.empty())
        {
            throw invalid_argument("Capture method caannot be empty.");
        }

        if(!correction_of.empty() && (acting_lecturer_ID.empty()||reason.empty()))
        {
            throw invalid_argument("Correction need lecturer ID and reason.");
        }

    }

    const string& getRecordID() const{
        return record_ID;
    }

    const string& getStudentID() const{
        return student_ID;
    }

    const string& getSessionID(){
        return session_ID;
    }
    AttendanceStatus getStatus() const {
        return status;
    }

    const string& getCaptureMethod() const {
        return capture_method;
    }

    const string& getCorrectionOf() const {
        return correction_of;
    }

    const string& getActingLecturerId() const {
        return acting_lecturer_ID;
    }

    const string& getReason() const {
        return reason;
    }

    chrono::system_clock::time_point getTimestamp() const {
        return time_stamp;
    }

    bool isCorrection() const {
        return !correction_of.empty();
    }






};

#endif