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
        const char *servers[] = {"127.0.0.1"}; // add any server IP to list
        int num_servers = sizeof(servers) / sizeof(servers[0]); 
    
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
            printf("Failed to create socket.\n"); 
            return -1;
        }

        memset(&serv_addr, '0', sizeof(serv_addr)); // allocate memory to store address
        serv_addr.sin_port = htons(PORT); // network byte order conversion
        serv_addr.sin_family = AF_INET; // IPv4

        int i = 0;
        for (i = 0; i < num_servers; i++) {
            // convert IP address from text to binary
            if (inet_pton(AF_INET, servers[i], &serv_addr.sin_addr) <= 0) {
                    printf("Invalid address provided.\n");
                    return -1;
            }

            if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
                    printf("Connection Failed.\n");
                    return -1;
            }

            send(sock, message, strlen(message), 0);
            printf("Uptime request sent\n");
            valread = read(sock, buffer, 1024);
            printf("[SERVER %s] %s\n", servers[i], buffer);
        }
        return 0;
}
