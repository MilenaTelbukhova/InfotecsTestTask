#include <filesystem>
#include <fstream>
#include <string>
#include <optional>
#include "error.h"

enum ImportanceLevel {
    debug = 0,
    info,
    warn,
    error
};

class Logger {
    public:
        Logger(std::filesystem::path path, ImportanceLevel defaultImportanceLevel);
        ~Logger();
        std::optional<Error>Log(ImportanceLevel importance, std::string text);
        void SetImportanceLevel(ImportanceLevel importanceLevel);
    private:
        ImportanceLevel Importance;
        std::ofstream Journal;
};
