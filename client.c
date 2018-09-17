#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>

int main() {
    char buffer[128] = {0};
    struct sockaddr_in server_addr;
    int addrlen = sizeof(server_addr);
    int socket_fd;


    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) <= 0) {
        perror("Failed to create socket.");
        exit(0);
    }

    memset(&server_addr, '0', addrlen);

    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_port = htons(44444);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        printf("Address is not valid.");
        exit();
    }

    if (connect(socket_fd, (struct sockaddr*)&server_addr, addrlen) < 0) {
        printf("Connection failed.");
        exit();
    }
    
    send(socket_fd, "test", strlen("test"), 0);
    resp = read(socket_fd, buffer, 128);
    printf("RESPONSE: %s\n", buffer);
    return 0;
}

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(44444);

}

