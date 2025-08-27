#include <optional>
#include "error.h"
#include <mutex>

enum ImportanceLevel {
    debug = 0,
    info,
    warn,
    error
};

class BaseLogger {
    public:
        BaseLogger(ImportanceLevel importance);
        virtual std::optional<Error>Log(ImportanceLevel importance, const std::string& text) = 0;
        void SetImportanceLevel(ImportanceLevel importanceLevel);
        ImportanceLevel GetImportanceLevel();
    protected:
        struct GuardedImportanceLevel {
            ImportanceLevel value;
            std::mutex Mutex;
            GuardedImportanceLevel(): value(ImportanceLevel::debug){}
            GuardedImportanceLevel(ImportanceLevel l): value(l){}
        };
        GuardedImportanceLevel Importance;
};