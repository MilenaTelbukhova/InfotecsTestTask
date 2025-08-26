#include <filesystem>
#include <fstream>
#include <string>
#include <optional>
#include <mutex>
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
        std::optional<Error>Log(ImportanceLevel importance, const std::string& text);
        void SetImportanceLevel(ImportanceLevel importanceLevel);
        ImportanceLevel GetImportanceLevel();
    private:
        
        struct GuardedImportanceLevel {
            ImportanceLevel value;
            std::mutex Mutex;
            GuardedImportanceLevel(ImportanceLevel l): value(l){}
        };

        struct LogJournal {
            std::filesystem::path path;
            std::ofstream value;
            std::mutex Mutex;
            LogJournal(std::filesystem::path p): value(p, std::ios::ate), path(p) {}
        };

        GuardedImportanceLevel Importance;
        LogJournal Journal;
};
