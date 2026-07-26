#ifndef TIME_SLOT_H
#define TIME_SLOT_H

#include <string>
#include <stdexcept>
using namespace std;

enum class Day {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

class TimeSlot {
private:
    Day day;
    int startMinutes;
    int endMinutes;
    string location;

public:
    // Constructor
    TimeSlot(
        Day day,
        int startMinutes,
        int endMinutes,
        const string& location
    )
        : day(day),
          startMinutes(startMinutes),
          endMinutes(endMinutes),
          location(location)
    {
        if (startMinutes < 0 || endMinutes > 24 * 60) {
            throw invalid_argument(
                "Time must be between 00:00 and 24:00."
            );
        }

        if (startMinutes >= endMinutes) {
            throw invalid_argument(
                "Start time must be earlier than end time."
            );
        }

        if (location.empty()) {
            throw invalid_argument(
                "Location cannot be empty."
            );
        }
    }

    Day getDay() const {
        return day;
    }

    int getStartMinutes() const {
        return startMinutes;
    }

    int getEndMinutes() const {
        return endMinutes;
    }

    const string& getLocation() const {
        return location;
    }

    bool overlaps(const TimeSlot& other) const {
        if (day != other.day) {
            return false;
        }

        return startMinutes < other.endMinutes &&
               other.startMinutes < endMinutes;
    }

    bool operator==(const TimeSlot& other) const {
        return day == other.day &&
               startMinutes == other.startMinutes &&
               endMinutes == other.endMinutes &&
               location == other.location;
    }
};

#endif