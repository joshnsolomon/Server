#include "server.h"

#define PORT 8080
#define BUFFER_SIZE 1024

#define HTML "./page/HelloWorld.html"

int main(){
    printf("Hello, world!\n");
    //printf("%s\n", file_to_string(HTML));

    //generate reponse
    char buffer[BUFFER_SIZE];
    char header[] = "HTTP/1.0 200 OK\r\n"
                  "Server: webserver-c\r\n"
                  "Content-type: text/html\r\n\r\n";

    char* html = file_to_string(HTML);
    char* resp = concat_strings(header, html);


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