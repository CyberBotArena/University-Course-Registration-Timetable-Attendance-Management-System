#ifndef ATTENDANCE_REGISTER_H
#define ATTENDANCE_REGISTER_H

#include<stdexcept>
#include<string>
#include<vector>

#include "AttendanceRecord.h"
#include "AttendanceSession.h"
using namespace std;

class AttendanceRegister{
    private:
    vector<AttendanceSession> sessions;
    vector<AttendanceRecord> records;

    public:

    //add a new attendance session
    void addSession(const AttendanceSession& session){
        if(findSession(session.getId()) != nullptr) 
        {
            throw invalid_argument("A sssion with this ID already exist.");
        }
        sessions.push_back(session);
    }

    // Add a new attendance record
    void addRecord(const AttendanceRecord& record){
        if (findRecord(record.getRecordID()) !=nullptr)
        {
            throw invalid_argument("A record with this Id already exists.");
        }
        AttendanceSession* session = findSession(record.getSessionID());
        
        if (!session->isOpen()) 
        {
            throw std::runtime_error("Cannot add attendance to a closed or expired session."); 
        }
            
            records.push_back(record);
        }
        
        // Find a session; return nullptr if it is not found
        AttendanceSession* findSession(const string& sessionId) {
            for (AttendanceSession& session : sessions) 
            {
                if (session.getId() == sessionId) 
                {
                    return &session;
                }
            }
            
            return nullptr;
        }

// Read-only version for const AttendanceRegister objects
const AttendanceSession* findSession(const string& sessionId) const {
    
    for (const AttendanceSession& session : sessions) 
    {
        if (session.getId() == sessionId) {
            return &session;
        }
    }

    return nullptr;
}

// Find a record; return nullptr if it is not found
AttendanceRecord* findRecord(const string& recordId) {
    for (AttendanceRecord& record : records) {
        if (record.getRecordID() == recordId) {
            return &record;
        }
    }

    return nullptr;
}

/* Read-only version
const AttendanceRecord* findRecord(const string& recordId ) const {
    for (const AttendanceRecord& record : records) {
        if (record.getRecordID() == recordId) {
            return &record;
        }
    }

    return nullptr;
}*/

// Close an existing attendance session
void closeSession(const string& sessionId) {
    AttendanceSession* session = findSession(sessionId);

    if (session == nullptr) 
    {
        throw invalid_argument( "The attendance session does not exist.");
    }

    session->close();
}
//Returns a read-only reference to the original sessions vector.
const vector<AttendanceSession>& getSessions() const {
    return sessions;
}
//Returns a read-only reference to the original record vector.
const std::vector<AttendanceRecord>& getRecords() const {
    return records;
}

void markPresent(const string& record_ID, const string& student_ID, const string& session_ID, const string& capture_method){
    AttendanceRecord newrecord(record_ID,student_ID,session_ID,AttendanceStatus::Present, capture_method);

    addRecord(newrecord);
}

void appendCorrection(
    const string& new_record_ID, 
    const string& original_record_ID,
    AttendanceStatus newt_satus,
    const string& lecturer_ID,
    const string& reason){
        AttendanceRecord* originalRecord = findRecord(original_record_ID);

        if(originalRecord == nullptr){
            throw invalid_argument("Original attendance record does not exist.");

        }

        AttendanceRecord correctionRecord(
            new_record_ID,
            originalRecord->getStudentID(),
            originalRecord->getSessionID(),
            newt_satus,
            "Lecturer Correction",
            original_record_ID,
            lecturer_ID,
            reason
                 



        );
    }

//calculate one student's attendance percentage for one course offering

double percentageFor(const string& student_ID, const string& offering_ID) const{
    int total_sessions =0;
    int attended_sessions =0;

    for(const AttendanceSession& session : sessions)
    {
        if(session.getOfferingId() == offering_ID)
        {
            total_sessions++;
             // Search backwards to find the latest record or correction
             
             for (int i = static_cast<int>(records.size()) - 1; i >= 0;i--) 
             {
                const AttendanceRecord& record = records[i];
                if (record.getStudentID() == student_ID && record.getSessionID() == session.getId()) 
                {
                    if (record.getStatus() == AttendanceStatus::Present || record.getStatus() == AttendanceStatus::Late) 
                    {
                    attended_sessions++;
                    }

                // Latest applicable record was found
                break;
                }
             }
        }

    if (total_sessions == 0) 
    {
        return 0.0;
    }

    }

    return (static_cast<double>(attended_sessions)/total_sessions)*100.0;

    }




};

#endif

