#include <string>

enum Day {
    Monday,
    Tueseday,
    Wednesday,
    Thursday,
    Friday
};
class Timeslot
{
private:
Day day;
int statrt_minutes;
int end_minutes;
std::string location;
    
public:
    Timeslot(Day day,
    int start_minute,
    int end_minutes,
    std::string location);
    ~Timeslot();

    Day getDay() const;
    int getStartMinutes() const;
    int getEndMinutes() const;
    const std::string getLocation() const;

};

Timeslot::Timeslot(Day day,
    int startMinutes,
    int endMinutes,
    const std::string& location)
: day(day),
startMinutes(startMinutes),
endMinutes(endMinutes),
location(location) {
if (startMinutes < 0 || endMinutes > 24 * 60) {
throw std::invalid_argument(
"Time must be between 00:00 and 24:00.");
}

if (startMinutes >= endMinutes) {
throw std::invalid_argument(
"The start time must be earlier than the end time.");
}

if (location.empty()) {
throw std::invalid_argument("Location cannot be empty.");
}
}
Day TimeSlot::getDay() const {
    return day;
}

int TimeSlot::getStartMinutes() const {
    return startMinutes;
}

int TimeSlot::getEndMinutes() const {
    return endMinutes;
}

const std::string& TimeSlot::getLocation() const {
    return location;
}

Timeslot::~Timeslot()
{
}
