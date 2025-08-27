#pragma once
#include <optional>
#include <mutex>
#include <logger/util/error.h>

enum ImportanceLevel {
    debug = 0,
    info,
    warn,
    error
};

class BaseLogger {
    public:
        BaseLogger();
        BaseLogger(ImportanceLevel importance);
        virtual ~BaseLogger() = 0;
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