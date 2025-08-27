#include "logger.h"
#include <filesystem>
#include <string>
#include <fstream>
#include <optional>
#include "error.h"
#include "util.cpp"
#include <iostream>


using namespace MessageParse;

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
        std::string t = MessageParse::getTime();
        Journal.value << t.substr(4, t.size() - 5) << " [" << MessageParse::getImportanceString(importance) << "] "<< text << std::endl;
    } else {
        return Error{"Can not open journal\n"};
    }
    return {};
};