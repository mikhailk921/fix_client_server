#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <chrono>
#include <filesystem>
#include <sys/stat.h>
#include <sstream>
#include <utility>


#define LOGGER_PRINT_TO_OUT true
#define LOGGER_DONT_PRINT_TO_OUT false
#define MAX_BUFFER_MESSAGE_COUNT 10


//
// LogLevel
//

// Logger verbosity levels


enum class LogLevel {
    None = 0,     // Logging is disabled
    Fatal = 1,    // Used for fatal error
    Error = 2,    // Used for error
    Warning = 3,  // Used for warning
    Info = 4,     // Info message
    Debug = 5,    // Debug message
};

const std::unordered_map<LogLevel, std::string> strLogLevelMap = {
        {LogLevel::None,    "None"},
        {LogLevel::Fatal,   "Fatal"},
        {LogLevel::Error,   "Error"},
        {LogLevel::Warning, "Warning"},
        {LogLevel::Info,    "Info"},
        {LogLevel::Debug,   "Debug"},
};

static std::string timePointAsString(const std::chrono::system_clock::time_point& tp) {
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::string ts = std::ctime(&t);
    ts.resize(ts.size()-1);
    return ts;
}


//
// Logger
//

class Logger {
public:
    Logger(): _name("default"), _logLevel(LogLevel::None) {};
    Logger(std::string  name, const LogLevel& lvl): _name(std::move(name)), _logLevel(lvl) {
        std::string logsFolder = "logs";
        auto status = mkdir(logsFolder.c_str(), 0777);
        if (status and status != -1) {
            throw std::runtime_error("Error creating director: " + logsFolder + "; Status: " + std::to_string(status));
        }
        auto timestamp = std::time(nullptr);
        filename =  logsFolder + "/" + _name + "_" + std::to_string(timestamp) + ".log";
        std::cout << "Log file name: " << filename << std::endl;
        std::ofstream loggerFile(filename);
    };

    virtual ~Logger() {
        writeBufferToFile();
    }

    auto name() const {
        return _name;
    };

    void setName(std::string& name) {
        _name = name;
    };

    auto level() const {
        return _logLevel;
    };

    void setLevel(LogLevel& lvl) {
        _logLevel = lvl;
    };

public:
    void fatal(const std::string& message, bool printToCout=LOGGER_DONT_PRINT_TO_OUT) {
        addEntryMessage(LogLevel::Fatal, message, printToCout);
    };

    void error(const std::string& message, bool printToCout=LOGGER_DONT_PRINT_TO_OUT) {
        addEntryMessage(LogLevel::Error, message, printToCout);
    };

    void warning(const std::string& message, bool printToCout=LOGGER_DONT_PRINT_TO_OUT) {
        addEntryMessage(LogLevel::Warning, message, printToCout);
    };

    void info(const std::string& message, bool printToCout=LOGGER_DONT_PRINT_TO_OUT) {
        addEntryMessage(LogLevel::Info, message, printToCout);
    };

    void debug(const std::string& message, bool printToCout=LOGGER_DONT_PRINT_TO_OUT) {
        addEntryMessage(LogLevel::Debug, message, printToCout);
    };

private:
    void writeBufferToFile() {
        std::ofstream loggerFile(filename, std::ios_base::app);
        loggerFile << outStringBuffer.str();
        loggerFile.close();
    }

    void addEntryMessage(const LogLevel msgLevel, const std::string& message, const bool printToCout) {
        std::string mess = timePointAsString(std::chrono::system_clock::now()) \
                          + ": " + strLogLevelMap.at(msgLevel) + ": " + message + "\n";
        if (printToCout) {
            std::cout << mess << std::endl;
        }
        outStringBuffer << mess;
        bufferMessageCount++;
        if (bufferMessageCount >= MAX_BUFFER_MESSAGE_COUNT) {
            writeBufferToFile();
            bufferMessageCount = 0;
            outStringBuffer.clear();
        }
    };

    std::string _name;
    LogLevel _logLevel = LogLevel::None;
    std::string filename;
    std::stringstream outStringBuffer;
    u_int32_t bufferMessageCount = 0;
};
