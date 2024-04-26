#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        error("Usage: %s hostname port\n");
    }

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[255];

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("Error opening socket");
    }

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        error("No such host");
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("Connection failed");
    }

    while (1) {
        bzero(buffer, sizeof(buffer));
        fgets(buffer, sizeof(buffer), stdin);
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0) {
            error("Error writing to socket");
        }

        bzero(buffer, sizeof(buffer));
        n = read(sockfd, buffer, sizeof(buffer));
        if (n < 0) {
            error("Error reading from socket");
        }
        printf("Server: %s", buffer);

        if (strncmp("Bye", buffer, 3) == 0) {
            break;
        }
    }

    close(sockfd);
    return 0;
}
