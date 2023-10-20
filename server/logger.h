#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>


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


//
// Logger
//

class Logger {
public:
    Logger(): _name("default"), _logLevel(LogLevel::None) {};
    Logger(std::string name, LogLevel lvl): _name(name), _logLevel(lvl) {
        filename =  _name, ".log";
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
    void fatal(std::string& message) {
        addEntryMessage(LogLevel::Fatal, message);
    };

    void error(std::string& message) {
        addEntryMessage(LogLevel::Error, message);
    };

    void warning(std::string message) {
        addEntryMessage(LogLevel::Warning, message);
    };

    void info(std::string message) {
        addEntryMessage(LogLevel::Info, message);
    };

    void debug(std::string message) {
        addEntryMessage(LogLevel::Debug, message);
    };

private:
    void addEntryMessage(LogLevel msgLevel, std::string& message) {
        std::fstream logfile(filename, std::fstream::in);
        logfile << strLogLevelMap.at(msgLevel), ": ", message, "\n";
        logfile.close();
    };

    std::string _name;
    LogLevel _logLevel = LogLevel::None;
    std::string filename;
};


