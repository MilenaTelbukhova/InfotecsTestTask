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
                                    BaseLogger(defaultImportanceLevel){};


Logger::~Logger(){
    Journal.value.close();
}

std::optional<Error> Logger::Log(ImportanceLevel importance,const std::string& text){
    std::lock_guard<std::mutex> lg_i(Importance.Mutex);
    std::lock_guard<std::mutex> lg_j(Journal.Mutex);
    if (importance < this->Importance.value) return {};
    if (Journal.value.is_open() && std::filesystem::exists(Journal.path)) {
        std::string t = getTime();
        Journal.value << t.substr(4, t.size() - 5) << " [" << getImportanceString(importance) << "] "<< text << std::endl;
    } else {
        return Error{"Can not open journal\n"};
    }
    return {};
};

std::pair<ImportanceLevel, std::string> ParseCommand(ImportanceLevel default_level, std::string& command) {
    ImportanceLevel level = default_level;
    if(command.size() < 5) return {level, command};
    size_t lptr = command.find(' ');
    if (lptr == std::string::npos) lptr = 0;

    std::string str_level = command.substr(0, lptr);

    if(str_level == "INFO") {
        level = ImportanceLevel::info;

    } else if(str_level== "WARN") {
        level = ImportanceLevel::warn;

    } else if(str_level == "ERROR") {
        level = ImportanceLevel::error;

    } else if (str_level == "DEBUG") {
        level = ImportanceLevel::debug;
    } else lptr = 0;

    while (lptr < command.size() && command[lptr] == ' ') lptr++;
    std::string ans = command.substr(lptr);
    return {level, ans};
}