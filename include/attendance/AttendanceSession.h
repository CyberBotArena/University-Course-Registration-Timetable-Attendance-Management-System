#ifndef ATTENDANCE_SESSION_H
#define ATTENDANCE_SESSION_H

#include <chrono>
#include <string>

#include "../scheduling/Timeslot.h"
using namespace std;

class AttendanceSession {
    private:
    string session_ID;
    string offering_ID;
    string open_by_lecture_ID;

    chrono::system_clock::time_point opened_at;
    chrono::system_clock::time_point expires_at;

    bool open;
    TimeSlot slot;

    public:
    AttendanceSession(
        const string& session_ID,
        const string& offering_ID,
        const string& lecturer_ID,
        const TimeSlot& slot,
        int duration_minutes
    ) : 
    session_ID(session_ID),
    offering_ID(offering_ID),
    open_by_lecture_ID(lecturer_ID),
    opened_at(chrono::system_clock::now()),
    expires_at(opened_at + chrono::minutes(duration_minutes)),
    open(true),
    slot(slot)
    {
        if (session_ID.empty()){
            throw invalid_argument(
                "Session ID cannot be empty."
            );
        }

        if (offering_ID.empty()){
            throw invalid_argument(
                "Offering ID cannot be empty."
            );
        }

        if (lecturer_ID.empty()){
            throw invalid_argument(
                "Lecturer ID cannot be empty."
            );
        }

        if (duration_minutes<=0){
            throw invalid_argument(
                "Session duration must be greater than zero."
            );
        }

    }

    const string& getId() const{
        return session_ID;
    }

    const string& getOfferingId() const{
        return offering_ID;
    }
    
    bool hasExpired() const {
        return chrono::system_clock::now() > expires_at;
    }

    bool isOpen() const {
        return open && !hasExpired();
    }

    void close() {
        open = false;
    }

};

#endif