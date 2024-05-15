#include "server.h"
#include <regex.h>
#include <stdlib.h>

#define PORT 8080
#define BUFFER_SIZE 1024

#define HTML "./page/HelloWorld.html"
#define FLOWERS "./page/flowers3.png"
#define CSS "./page/style.css"
#define LOGO "./page/logo.png"

int main(){
    printf("Hello, world!\n");
    //printf("%s\n", file_to_string(HTML));

    //buffer for receiving messages from client
    char buffer[BUFFER_SIZE];
    
    //html response
    char header[] = "HTTP/1.0 200 OK\r\n"
                  "Server: webserver-c\r\n"
                  "Content-type: text/html\r\n\r\n";

    long length;
    char* resp = response(header, HTML, &length);

    //image response
    char imageheader[] = "HTTP/1.0 200 OK\r\n"
                         "Server: webserver-c\r\n"
                         "Content-Type: image/png\r\n\r\n";

    long resp_length;
    char* img_resp = response(imageheader, FLOWERS, &resp_length);
    
    //css response
    char cssheader[] = "HTTP/1.0 200 OK\r\n"
                         "Server: webserver-c\r\n"
                         "Content-Type: text/css\r\n\r\n";

    long css_length;
    char* css_resp = response(cssheader, CSS, &css_length);

    //logo response
    char logoheader[] = "HTTP/1.0 200 OK\r\n"
                         "Server: webserver-c\r\n"
                         "Content-Type: image/png\r\n\r\n";

    long logo_length;
    char* logo_resp = response(logoheader, LOGO, &logo_length);

    //regex 
    regex_t flowers;
    regcomp(&flowers, "flowers3", 0);

    regex_t css;
    regcomp(&css, "style", 0);

    regex_t logo;
    regcomp(&logo, "logo", 0);



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
        if(regexec(&flowers, buffer, 0, NULL, 0) == 0){
            buffer_write(newsockfd, img_resp, resp_length);

        } else if (regexec(&css, buffer, 0, NULL, 0) == 0){
            buffer_write(newsockfd, css_resp, css_length);
        
        } else if (regexec(&logo, buffer, 0, NULL, 0) == 0){
            buffer_write(newsockfd, logo_resp, logo_length);

        } else 
            buffer_write(newsockfd, resp, length);


        close(newsockfd);
    }




    return 0;
}
