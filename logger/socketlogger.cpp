#include "socketlogger.h"
#include <arpa/inet.h>
#include <unistd.h>
#include "util.cpp"


SocketLogger::SocketLogger(uint16_t socketPort, ImportanceLevel defaultImportanceLevel)
                                                        : BaseLogger(defaultImportanceLevel){
    Soket = socket(AF_INET6, SOCK_STREAM, 0); //добавить проверку
    ServerAddres.sin_family = AF_INET6;
    ServerAddres.sin_port = htons(socketPort);
    inet_pton(AF_INET, "127.0.0.1", &ServerAddres.sin_addr); //добавить проверку
};

SocketLogger::~SocketLogger() { close(Soket); };

std::optional<Error>SocketLogger::Log(ImportanceLevel importance, const std::string& text) {
    std::lock_guard<std::mutex> lg_i(Importance.Mutex);
    if (importance < this->Importance.value) return {};
    if (connect(Soket, (sockaddr*)&ServerAddres, sizeof(ServerAddres)) < 0) {
        return Error{"Connection error"};
    }
    std::string t = MessageParse::getTime();
    std::string message = t.substr(4, t.size() - 5) + " [" + MessageParse::getImportanceString(importance) + "] " + text + '\n';
    send(Soket, message.c_str(), message.size(), 0);
    shutdown(Soket, SHUT_RDWR);
}