#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    printf("Hello, world!\n");

    //generate reponse
    char buffer[BUFFER_SIZE];
    char resp[] = "HTTP/1.0 200 OK\r\n"
                  "Server: webserver-c\r\n"
                  "Content-type: text/html\r\n\r\n"
                  "<html>Hello, world</html>\r\n";

    //open socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        printf("socket not made\n");
        return -1;
    }
    else{
        printf("socket made\n");
    }

    //make connection address
    struct sockaddr_in host_addr;
    int host_addr_len = sizeof(host_addr);

    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(PORT);
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind socket
    int binder = bind(sockfd, (struct sockaddr*)&host_addr, host_addr_len);
    if(binder){
        printf("binding socket error\n");
        return 1;
    } else {
        printf("socket binded..\n");
    }
    
    //listen
    int listening = listen(sockfd, SOMAXCONN);
    if(listening){
        printf("listening error\n");
        return 2;
    } else {
        printf("socket listening..\n");
    }

    //stuff happens here    
    int messages = 0;
    while(true){
        //connect
        int newsockfd = accept(sockfd, (struct sockaddr*)&host_addr, 
                                (socklen_t *)&host_addr_len);
        if(newsockfd < 0){
            printf("server erorr\n");
            return 3;
        } else {
            printf("connection accepted\n");
        }

        //read
        int valread = read(newsockfd, buffer, BUFFER_SIZE);
        if(valread < 0){
            printf("READ ERROR\n");
            return 4;
        }
        printf("%s\n", buffer);

        messages++;
        printf("Messages Received: %d\n", messages);

        //write
        int valwrite = write(newsockfd, resp, strlen(resp));
        if(valwrite < 0){
            printf("WRITE ERROR\n");
            return 5;
        }


        close(newsockfd);
    }




    return 0;
}
