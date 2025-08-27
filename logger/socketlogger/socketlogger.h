#include <filesystem>
#include <logger/baselogger/baselogger.h>
#include <netinet/in.h>


class SocketLogger : public BaseLogger{
    public:
        SocketLogger(uint16_t socketPort, ImportanceLevel defaultImportanceLevel);
        ~SocketLogger();
        std::optional<Error>Log(ImportanceLevel importance, const std::string& text) override;
    private:
        int Soket;
        sockaddr_in ServerAddres;
};