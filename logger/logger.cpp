#include "logger.h"
#include <filesystem>
#include <string>
#include <fstream>
#include <optional>
#include "error.h"
#include <iostream>


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
                                    : Journal(path), 
                                    Importance(defaultImportanceLevel){};


Logger::~Logger(){
    Journal.value.close();
}

std::optional<Error> Logger::Log(ImportanceLevel importance,const std::string& text){
    std::lock_guard<std::mutex> lg_i(Importance.Mutex);
    std::lock_guard<std::mutex> lg_j(Journal.Mutex);
    if (importance < this->Importance.value) return {};
    if (Journal.value.is_open()) {
        std::string t = getTime();
        Journal.value << t.substr(4, t.size() - 5) << " [" << getImportanceString(importance) << "] "<< text << std::endl;
    } else {
        return Error{"Can not open journal\n"};
    }
    return {};
};


void Logger::SetImportanceLevel(ImportanceLevel importanceLevel) {
    std::lock_guard<std::mutex> lg(Importance.Mutex);
    this->Importance.value = importanceLevel;
};

ImportanceLevel Logger::GetImportanceLevel() { return Importance.value; };
