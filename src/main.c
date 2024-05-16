#include "server.h"
#include <regex.h>
#include <stdlib.h>

#define PORT 8080
#define BUFFER_SIZE 1024

#define HTML "./page/HelloWorld.html"

int main(){
    printf("Hello, world!\n");

    //buffer for receiving messages from client
    char buffer[BUFFER_SIZE];


    //setup
    int sockfd;
    struct sockaddr_in host_addr;
    setup(&sockfd, &host_addr, PORT);


    //stuff happens here    
    int messages = 0;
    long resp_length;
    while(true){
        int newsockfd = server_connect(&sockfd, &host_addr);

        //read
        buffer_read(newsockfd, buffer, BUFFER_SIZE);
        messages++;
        printf("Messages Received: %d\n\n\n", messages);

        //write
        char* file = parse(buffer); // file name
        char* resp;
        if (strcmp(file, "./page/")  == 0){ //initial request
            resp = response(HTML, &resp_length);
            buffer_write(newsockfd,resp, resp_length);

        } else if(access(file, F_OK) == 0){ //wants a file
            resp = response(file, &resp_length);
            buffer_write(newsockfd,resp, resp_length);

        } else { //file not found
            printf("FILE DOES NOT EXIST**********************   ->%s\n", file);
            //SEND ERROR HERE??
        }
            

        free(file);
        free(resp);
        close(newsockfd);
    }




    return 0;
}
