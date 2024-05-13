#include "server.h"

int setup(int* sockfd, struct sockaddr_in* host_addr, int port){

    *sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(*sockfd == -1){
        perror("socket not made");
        return -1;
    }
    else{
        printf("socket made\n");
    }

    //make connection address
    int host_addr_len = sizeof(*host_addr);

    host_addr->sin_family = AF_INET;
    host_addr->sin_port = htons(port);
    host_addr->sin_addr.s_addr = htonl(INADDR_ANY);

    //bind socket
    int binder = bind(*sockfd, (struct sockaddr*)host_addr, host_addr_len);
    if(binder){
        perror("binding socket error");
        return 1;
    } else {
        printf("socket binded..\n");
    }
    
    //listen
    int listening = listen(*sockfd, SOMAXCONN);
    if(listening){
        perror("listening error\n");
        return 2;
    } else {
        printf("socket listening..\n");
    }

    return 0;

}

int server_connect(int* sockfd, struct sockaddr_in* host_addr){
    int host_addr_len = sizeof(*host_addr);    

    int newsockfd = accept(*sockfd, (struct sockaddr*)host_addr, 
                                (socklen_t *)&host_addr_len);
    if(newsockfd < 0){
        perror("server error");
        return -1;
    } else {
        printf("connection accepted\n");
    }

    return newsockfd;
}

int buffer_read(int socket, char* buffer, int buffersize){
    int valread = read(socket, buffer, buffersize);
    if(valread < 0){
        perror("READ ERROR");
        return 4;
    }
    printf("%s\n", buffer);
    return 0; 
}

int buffer_write(int socket, void* resp){
        int valwrite = write(socket, resp, strlen(resp));
        if(valwrite < 0){
            perror("WRITE ERROR\n");
            return 5;
        }
    return 0;
}