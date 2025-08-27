#include <filesystem>
#include <fstream>
#include <string>
#include <mutex>
#include <logger/baselogger/baselogger.h>
#include <logger/util/error.h>


class Logger : public BaseLogger{
    public:
        Logger(std::filesystem::path path, ImportanceLevel defaultImportanceLevel);
        ~Logger();
        std::optional<Error>Log(ImportanceLevel importance, const std::string& text) override;
    private:
        struct LogJournal {
            std::filesystem::path path;
            std::ofstream value;
            std::mutex Mutex;
            LogJournal(std::filesystem::path p): value(p, std::ios::ate), path(p) {}
        };
        LogJournal Journal;
};