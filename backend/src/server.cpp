#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>

#define BUFFER_SIZE 4096
#define PORT 8080

int main() {

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_fd == -1) {
        std::perror("Error on socket syscall");
        std::exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sock_fd, (sockaddr *)&server_addr, sizeof(sockaddr_in)) == -1) {
        std::perror("Error on bindng socket to an address, syscall BIND");
        close(sock_fd);
        std::exit(EXIT_FAILURE);
    }

    if (listen(sock_fd, SOMAXCONN) == -1) {
        std::perror("Error on marking socket as passive, syscall LISTEN");
        close(sock_fd);
        std::exit(EXIT_FAILURE);
    }

    while (1) {

        struct sockaddr client_addr{};
        socklen_t client_addr_len = sizeof(client_addr);

        int client_fd = accept(sock_fd, (sockaddr *)&client_addr, &client_addr_len);

        if (client_fd == -1) {
            std::perror("Error on accept");
            continue;
        }

        int pid = fork();
        else if (pid == -1) {
            std::perror("Error on forking");
            close(sock_fd);
            close(client_fd);
            continue;
        }
        
    }

    return 0;
}