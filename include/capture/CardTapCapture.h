#ifndef CARD_TAP_CAPTURE_H
#define CARD_TAP_CAPTURE_H

#include <stdexcept>
#include <string>

#include "AttendanceCapture.h"
#include "ConsoleCardReader.h"

class CardTapCapture : public AttendanceCapture {
private:
    ConsoleCardReader reader;
    bool capturing;

public:
    CardTapCapture(){
        capturing = false;
    }

    void beginSession(const AttendanceSession& session) override{
        capturing = true;
    }

    string captureNext()override {
        if(capturing==false)
        {
            throw runtime_error("Attendance capture has not started yet.");
        }

        return reader.readUID();
    }

    void endSession() override {
        capturing=false;
    }

    string getMethodName() const override {
        return "Card Tap";
    }

};

#endif
