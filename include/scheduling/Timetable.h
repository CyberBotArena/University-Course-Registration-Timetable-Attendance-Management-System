#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <vector>
#include "Timeslot.h"
using namespace std;

class Timetable {
    private:
    vector<TimeSlot> slots;



    public:
    void addSlot(const TimeSlot& slot) {
        slots.push_back(slot);
    }

    const vector<TimeSlot>& getSlots() const {
        return slots;
    }

    bool clashWith(const Timetable& other) const{
        for(const TimeSlot& myslot : slots){
            for(const TimeSlot& otherSlot : other.slots){
                if(myslot.overlaps(otherSlot)){
                    return true;
                }
            }
        }
        return false;
    }

    Timetable& operator+=(const TimeSlot& slot){
        addSlot(slot);
        return *this;
    }





};

#endif
