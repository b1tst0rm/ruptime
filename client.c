#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#define PORT 44444

int main(int argc, char const *argv[])
{
        struct sockaddr_in address;
        int sock = 0, valread;
        struct sockaddr_in serv_addr;
        char *message = "uptime";
        char buffer[1024] = {0};

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
            printf("Failed to create socket."); 
            return -1;
        }

        memset(&serv_addr, '0', sizeof(serv_addr)); // allocate memory to store address

        serv_addr.sin_family = AF_INET; // IPv4
        serv_addr.sin_port = htons(PORT); // network byte order conversion

        // convert IP address from text to binary
        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
                printf("Invalid address provided.");
                return -1;
        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
                printf("\nConnection Failed \n");
                return -1;
        }

        send(sock, message, strlen(message), 0);
        printf("Uptime request sent\n");
        valread = read(sock, buffer, 1024);
        printf("SERVER RESPONSE: %s\n", buffer);
        return 0;
}
