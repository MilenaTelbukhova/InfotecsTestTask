#include "socketlogger.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <logger/util/util.h>
#include <iostream>


SocketLogger::SocketLogger(uint16_t socketPort, ImportanceLevel defaultImportanceLevel)
                                                        : BaseLogger(defaultImportanceLevel){
    Soket = socket(AF_INET, SOCK_STREAM, 0);
    if (Soket == -1) std::cout << "CANT MAKE SOCKET\n";
    ServerAddres = {};
    ServerAddres.sin_family = AF_INET;
    ServerAddres.sin_port = htons(socketPort);
    if(inet_pton(AF_INET, "127.0.0.1", &ServerAddres.sin_addr) <= 0) std::cout << "CANT MAKE ADDRESS\n";
};

SocketLogger::~SocketLogger() { close(Soket); };

std::optional<Error>SocketLogger::Log(ImportanceLevel importance, const std::string& text) {
    std::lock_guard<std::mutex> lg(Importance.Mutex);
    if (importance < this->Importance.value) return {};
    if (connect(Soket, (sockaddr*)&ServerAddres, sizeof(ServerAddres)) < 0 && errno != EISCONN) {
        return Error{"Connection error\n"};
    }
    std::string t = MessageParse::getTime();
    std::string message = t.substr(4, t.size() - 5) + " [" + MessageParse::getImportanceString(importance) + "] " + text + '\n';
    send(Soket, message.c_str(), message.size(), 0);
    return {};
};

