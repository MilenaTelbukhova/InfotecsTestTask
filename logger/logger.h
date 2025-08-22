#include <filesystem>
#include <string>

enum ImportanceLevel {
    debug,
    info,
    warn,
    error
};

class Logger {
    public:
        Logger(std::filesystem::path path, ImportanceLevel defaultImportanceLevel);
        void Log(ImportanceLevel importance, std::string text);
        void ChangeImportanceLevel(ImportanceLevel importanceLevel);
    private:
        ImportanceLevel Importance;
        std::filesystem::path Path;
};
