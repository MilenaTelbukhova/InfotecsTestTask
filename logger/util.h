#pragma once
#include <string>
#include "baselogger.h"

namespace MessageParse {
    std::string getTime();
    std::string getImportanceString(ImportanceLevel level);
    std::pair<ImportanceLevel, std::string> ParseCommand(ImportanceLevel default_level, std::string& command);
}