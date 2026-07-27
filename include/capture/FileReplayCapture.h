#ifndef FILE_REPLAY_CAPTURE_H
#define FILE_REPLAY_CAPTURE_H

#include <fstream>
#include <stdexcept>
#include <string>

#include "AttendanceCapture.h"

class FileReplayCapture : public AttendanceCapture {
private:
    std::string filePath;
    std::ifstream* input;

public:
    explicit FileReplayCapture(const std::string& file_path)
        : filePath(file_path), input(nullptr) {}

    void beginSession(const AttendanceSession& session) override {
        (void)session;

        endSession();
        input = new std::ifstream(filePath);

        if (!input->is_open()) {
            delete input;
            input = nullptr;
            throw std::runtime_error(
                "Could not open attendance file: " + filePath
            );
        }
    }

    std::string captureNext() override {
        if (input == nullptr) {
            throw std::runtime_error("Attendance capture has not started yet.");
        }

        std::string student_ID;
        if (std::getline(*input, student_ID)) {
            if (!student_ID.empty() && student_ID.back() == '\r') {
                student_ID.pop_back();
            }
            return student_ID;
        }

        return "";
    }

    void endSession() override {
        if (input != nullptr) {
            input->close();
            delete input;
            input = nullptr;
        }
    }

    std::string getMethodName() const override {
        return "File Replay";
    }

    ~FileReplayCapture() override {
        endSession();
    }

    FileReplayCapture(const FileReplayCapture&) = delete;
    FileReplayCapture& operator=(const FileReplayCapture&) = delete;
};

#endif
