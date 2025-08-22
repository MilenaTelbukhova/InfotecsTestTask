#include "logger.h"
#include <filesystem>
#include <string>
#include <fstream>

namespace {

    std::string getTime(){
        const auto now = std::chrono::system_clock::now();
        const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
        return std::ctime(&t_c);
    };

    std::string getImportanceString(ImportanceLevel level){
        switch (level)
        {
        case ImportanceLevel::debug:
            return "DEBUG";
        case ImportanceLevel::info:
            return "INFO";
        case ImportanceLevel::warn:
            return "WARN";
        case ImportanceLevel::error:
            return "ERROR";
        default:
            return "";
        }
    }

}

Logger::Logger(std::filesystem::path path, ImportanceLevel defaultImportanceLevel) {
    Path = path;
    Importance = defaultImportanceLevel;
};


void Logger::Log(ImportanceLevel importance, std::string text){
    std::ofstream journal(Path, std::ios::app);
    if (journal.is_open()) {
        journal << getTime() << " [" << getImportanceString(importance) << "] "<< text << std::endl;
    }
};


void Logger::ChangeImportanceLevel(ImportanceLevel importanceLevel) {
    Importance = importanceLevel;
};


