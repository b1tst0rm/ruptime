#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    setbuf(stdout, NULL);
    printf("hi");
    char buffer[128] = {0};
    struct sockaddr_in server_addr;
    int addrlen = sizeof(server_addr);
    int server_fd, accept_fd; // fd = file descriptor

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) <= 0) {
        perror("Failed to create socket.");
        exit(0);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(44444);

    if ((bind(server_fd, (struct sockaddr*)&server_addr, addrlen)) < 0) {
        printf("Binding failed.");
        exit(0);
    }

    if ((listen(server_fd, 3)) < 0) {
        printf("Failed to begin listening.");
        exit(0);
    }

    if ((accept_fd = accept(server_fd, (struct sockaddr*)&server_addr, (socklen_t*)&addrlen)) < 0) {
        printf("Failed to setup accepting file descriptor.");
        exit(0);
    }

    printf("Server started on port 44444. Press CTRL+C to stop.");

    // Infinite loop, server always running
    while(1) {
        read(accept_fd, buffer, 128);
        send(accept_fd, buffer, strlen(buffer), 0);
    }
}

