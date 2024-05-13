#include "server.h"

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

    //setup
    int sockfd;
    struct sockaddr_in host_addr;
    setup(&sockfd, &host_addr, PORT);


    //stuff happens here    
    int messages = 0;
    while(true){
        int newsockfd = server_connect(&sockfd, &host_addr);

        //read
        buffer_read(newsockfd, buffer, BUFFER_SIZE);
        messages++;
        printf("Messages Received: %d\n", messages);


        //write
        buffer_write(newsockfd, resp);

        close(newsockfd);
    }




    return 0;
}
