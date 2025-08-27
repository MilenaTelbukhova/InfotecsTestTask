#include<chrono>
#include<iostream>
#include<string>
#include "logger.h"
#include "util.h"
#include <utility>
#include <thread>



int main(int argc, char*argv[])
{
    if (argc < 4) {
        std::cout << "Not enought arguments" << std::endl;
        return 0;
    }
    
    std::string importanceLevelstr = std::string(argv[1]) + " ";
    ImportanceLevel importanceLevel = MessageParse::ParseCommand(ImportanceLevel::debug, importanceLevelstr).first;
    std::string flag = argv[2];
    if (flag.size() != 2 && flag[0] != '-'){
        std::cout << "invalid flag input" << std::endl;
        return 0;
    }

    if (flag[1] == 'f') {
        std::filesystem::path path = argv[3];
        Logger logger{path, importanceLevel};
        while (true)
        {
            std::string s;
            std::getline(std::cin, s);
            auto res = MessageParse::ParseCommand(logger.GetImportanceLevel(), s);
            std::thread th ([&logger](ImportanceLevel importance, const std::string& message){
                auto err = logger.Log(importance, message);
                if (err.has_value()) std::cout << err.value().Message;
            }, res.first, res.second);
            th.detach();
        }
    } else if (flag[1] == 's') {
        //socket logic
    } else {
        std::cout << "invalid flag input" << std::endl;
    }

    return 0;
}