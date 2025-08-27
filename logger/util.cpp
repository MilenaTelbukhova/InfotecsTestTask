#include <utility>
#include "baselogger.h"
#include "util.h"

std::string MessageParse::getTime(){
        const auto now = std::chrono::system_clock::now();
        const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
        return std::ctime(&t_c);
    };

std::string MessageParse::getImportanceString(ImportanceLevel level){
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


std::pair<ImportanceLevel, std::string> MessageParse::ParseCommand(ImportanceLevel default_level, std::string& command) {
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