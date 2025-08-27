#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int main(int args, char* argv[]) {
    if (args < 2) {
        std::cout << "Not enought arguments" << std::endl;
        return 0;
    }
    uint16_t port = std::atoi(argv[1]);
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Не удалось создать сокет\n";
        return 0;
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "Не удалось установить SO_REUSEADDR\n";
        // продолжаем, это не критично
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Ошибка привязки\n";
        return 0;
    }

    if (listen(server_fd, 3) < 0) {
        std::cerr << "Ошибка прослушивания\n";
        return 0;
    }

    std::cout << "Сервер запущен на порту " << port << ". Ожидание подключений..." << std::endl;;
    while (true) {
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(server_fd, (sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) {
            std::cerr << "Ошибка принятия подключения\n";
            return 1;
        }

        std::cout << "Клиент подключен\n";

        while (true) {
            char buffer[1024];
            ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
            if (bytes_read > 0) {
                buffer[bytes_read] = '\0';
                std::cout << buffer;
                std::cout.flush();
            } else if (bytes_read == 0) {
                std::cout << "Клиент отключился\n";
                break;
            } else {
                std::cerr << "Ошибка чтения из сокета\n";
                break;
            }
        }
        close(client_socket);
    }
    // close(client_socket);
    close(server_fd);

    return 0;
}