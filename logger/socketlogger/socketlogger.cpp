#include "socketlogger.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <logger/util/util.h>


SocketLogger::SocketLogger(uint16_t socketPort, ImportanceLevel defaultImportanceLevel)
                                                        : BaseLogger(defaultImportanceLevel){
    Soket = socket(AF_INET6, SOCK_STREAM, 0);
    ServerAddres.sin_family = AF_INET6;
    ServerAddres.sin_port = htons(socketPort);
};

SocketLogger::~SocketLogger() { close(Soket); };

std::optional<Error>SocketLogger::Log(ImportanceLevel importance, const std::string& text) {
    std::lock_guard<std::mutex> lg_i(Importance.Mutex);
    if (importance < this->Importance.value) return {};
    if (connect(Soket, (sockaddr*)&ServerAddres, sizeof(ServerAddres)) < 0) {
        return Error{"Connection error\n"};
    }
    std::string t = MessageParse::getTime();
    std::string message = t.substr(4, t.size() - 5) + " [" + MessageParse::getImportanceString(importance) + "] " + text + '\n';
    send(Soket, message.c_str(), message.size(), 0);
    shutdown(Soket, SHUT_RDWR);
};
