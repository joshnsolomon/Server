#include <stdio.h>
#include <sys/socket.h>

int main(){
    printf("Hello, world!\n");

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
        printf("socket error\n");
    else
        printf("socket success\n");
    return 0;
}
