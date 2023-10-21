#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <chrono>
#include <filesystem>
#include <sys/stat.h>


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
    Logger(std::string name, LogLevel lvl): _name(name), _logLevel(lvl) {
        std::string logsFolder = "logs";
        mkdir(logsFolder.c_str(), 0777);
        auto timestamp = std::time(nullptr);
        filename =  logsFolder + "/" + _name + "_" + std::to_string(timestamp) + ".log";
        std::cout << "File name: " << filename << std::endl;
        std::ofstream loggerFile(filename);
    };

    auto name() const {
        return _name;
    };

    void setName(std::string& name) {
        _name = name;
    };

    auto level() const {
        return _logLevel;
    };

    void setLevel(LogLevel lvl) {
        _logLevel = lvl;
    };

public:
    void fatal(std::string& message, bool printToCout=false) {
        addEntryMessage(LogLevel::Fatal, message, printToCout);
    };

    void error(std::string& message, bool printToCout=false) {
        addEntryMessage(LogLevel::Error, message, printToCout);
    };

    void warning(std::string message, bool printToCout=false) {
        addEntryMessage(LogLevel::Warning, message, printToCout);
    };

    void info(std::string message, bool printToCout=false) {
        addEntryMessage(LogLevel::Info, message, printToCout);
    };

    void debug(std::string message, bool printToCout=false) {
        addEntryMessage(LogLevel::Debug, message, printToCout);
    };

private:
    void addEntryMessage(LogLevel msgLevel, std::string& message, bool printToCout) {
        auto mess = timePointAsString(std::chrono::system_clock::now()) \
                          + ": " + strLogLevelMap.at(msgLevel) + ": " + message + "\n";
        std::ofstream loggerFile(filename, std::ios_base::app);
        loggerFile << mess;
        loggerFile.close();
        if (printToCout)
            std::cout << mess << std::endl;
    };

    std::string _name;
    LogLevel _logLevel = LogLevel::None;
    std::string filename;
};


