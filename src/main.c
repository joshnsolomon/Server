#include "server.h"
#include <regex.h>

#define PORT 8080
#define BUFFER_SIZE 1024

#define HTML "./page/HelloWorld.html"
#define FLOWERS "./page/flowers3.jpg"

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

    char imageheader[] = "HTTP/1.0 200 OK\r\n"
                         "Content-Type: image/jpeg\r\n"
                         "Content-Length: 50000\r\n\r\n";
    char* flowers = file_to_string(FLOWERS);
    char* img_resp = concat_strings(imageheader, flowers);

    //regex 
    regex_t re;
    regcomp(&re, "flowers3", 0);



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
        if(regexec(&re, buffer, 0, NULL, 0) == 0){
            buffer_write(newsockfd, img_resp);
            printf("**************************** they want the flowers ************************************************");
        }
        else 
            buffer_write(newsockfd, resp);

        close(newsockfd);
    }




    return 0;
}
