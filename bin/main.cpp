#include<chrono>
#include<iostream>
#include<string>
#include "logger.h"

#include <utility>
#include <thread>

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
    std::cout << "PARSER gave away:[" << command.substr(lptr) << ']' << std::endl;
    return {level, ans};
}


int main(int argc, char*argv[])
{
    if (argc < 2) {
        std::cout << "Not enought arguments" << std::endl;
        return 0;
    } 
    std::string importanceLevelstr = std::string(argv[1]) + " ";
    ImportanceLevel importanceLevel = ParseCommand(ImportanceLevel::debug, importanceLevelstr).first;
    std::filesystem::path path = argv[2];
    Logger logger{path, importanceLevel};
    while (true)
    {
        std::string s;
        std::getline(std::cin, s);
        auto res = ParseCommand(logger.GetImportanceLevel(), s);
        std::thread th ([&logger](ImportanceLevel importance, const std::string& message){
            logger.Log(importance, message);
        }, res.first, res.second);
        th.detach();
    }

    return 0;
}