#include "logger.h"
#include <filesystem>
#include <string>
#include <fstream>
#include <optional>
#include "error.h"


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

Logger::Logger(std::filesystem::path path, ImportanceLevel defaultImportanceLevel)
                                    : Journal(std::ofstream{path, std::ios::app}), Importance(defaultImportanceLevel){};


Logger::~Logger(){
    Journal.close();
}
std::optional<Error> Logger::Log(ImportanceLevel importance, std::string text){
    if (importance < this->Importance) return;

    if (Journal.is_open()) {
        Journal << getTime() << " [" << getImportanceString(importance) << "] "<< text << std::endl;
    } else {
        return Error{"Can not open journal\n"};
    }
};


void Logger::SetImportanceLevel(ImportanceLevel importanceLevel) {
    this->Importance = importanceLevel;
};


