#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 4096

int main() {

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    

    return 0;
}