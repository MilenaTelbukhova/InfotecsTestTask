#include<chrono>
#include<iostream>
#include<string>
#include "logger.h"

#include <utility>
#include <thread>

std::pair<std::optional<ImportanceLevel>, std::string> ParseCommand(std::string& command) {
    if(command.size() < 5) return {{}, command};
    ImportanceLevel level;
    size_t lptr = command.find(' ');
    if (lptr == std::string::npos) lptr = 0;

    std::string str_level = command.substr(0, lptr);

    if(str_level == "INFO") {
        level = ImportanceLevel::info;

    } else if(str_level== "WARN") {
        level = ImportanceLevel::warn;

    } else if(command.substr(0, 6) == "ERROR") {
        level = ImportanceLevel::error;

    } else if (command.substr(0, 6) == "DEBUG") {
        level = ImportanceLevel::debug;
    }

    while (lptr < command.size() && command[lptr] == ' ') lptr++;
    
    return {level, command.substr(lptr)};
}


int main(std::filesystem::path path, ImportanceLevel importanceLevel)
{
    Logger logger{path, importanceLevel};
    while (true)
    {
        std::string s;
        std::getline(std::cin, s);
        auto res = ParseCommand(s);
        std::thread th([&logger, &res]{
            if (!res.first.has_value()) res.first = logger.GetImportanceLevel();

            logger.Log(res.first.value(), res.second);
        });
        th.detach();
    }
}