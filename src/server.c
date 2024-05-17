#include "server.h"
#include <stdlib.h>
#include <regex.h>

int setup(int* sockfd, struct sockaddr_in* host_addr, int port){

    //make socket
    *sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(*sockfd == -1){
        perror("socket not made");
        return -1;
    }
    else{
        printf("socket made\n");
    }
    int option = 1;

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
        printf("socket listening..\n\n\n");
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
    }

    return newsockfd;
}

int buffer_read(int socket, char* buffer, int buffersize){
    int valread = read(socket, buffer, buffersize);
    if(valread < 0){
        perror("READ ERROR");
        return 4;
    }
    print_nLines(buffer, 3);
    return 0; 
}

int buffer_write(int socket, void* resp, long len){
        int valwrite = write(socket, resp, len);
        if(valwrite < 0){
            perror("WRITE ERROR\n");
            return 5;
        }
    return 0;
}

char* file_to_string(const char* path){
    FILE* file = fopen(path,"rb");
    if(file == NULL)
        perror("file read error");

    //get size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    //allocate memory for string
    char* fileContent = (char*)malloc(fileSize+1); //for term char
    if(fileContent == NULL)
        perror("file malloc failed");
    
    fread(fileContent, 1, fileSize, file);
    fileContent[fileSize] = '\0';
    fclose(file);

    return fileContent;
}

char* concat_strings(char* str1, char* str2){
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    char* output = (char*)malloc(len1 + len2 + 1);

    strcpy(output, str1);
    strcat(output, str2);

    return output;
}

void print_nLines(char* buffer, int n){
    FILE* stream = fmemopen(buffer, strlen(buffer),"r");
    char* line = malloc(1024);
    int i = 0;
    while(fgets(line, 1024, stream) && i < n){
        printf("%s", line);
        i++;
    }
    printf("\n");
    free(line);
    fclose(stream);
}

char* file_to_buffer(const char* path, long* length){
    FILE* image = fopen(path, "rb");

    fseek(image, 0, SEEK_END);
    *length = ftell(image);
    fseek(image, 0, SEEK_SET);

    char* buffer = (char*)malloc(*length * sizeof(char));

    fread(buffer, sizeof(char), *length, image);

    fclose(image);

    return buffer;
}

char* response(const char* path, long* resp_length){
    
    char header[] = "HTTP/1.0 200 OK\r\n"
                  "Server: webserver-c\r\n\r\n";
    
    
    long length = 0;
    char* payload = file_to_buffer(path, &length);
    *resp_length =  strlen(header) + length;
    char* response = (char*)malloc(*resp_length);

    memcpy(response, header, strlen(header));
    memcpy(response+strlen(header), payload, length);

    free(payload);

    return response;
}

char* parse(const char* buffer){
    regex_t pattern;
    regmatch_t match[1];
    regcomp(&pattern, "GET [^$]* HTTP", REG_EXTENDED);

    
    int found = regexec(&pattern, buffer, 1, match, 0);

    int start = match[0].rm_so + 4;
    int end = match[0].rm_eo - 5;

    int length = end - start;

    char* file = (char*)malloc(length+1);
    char folder[] = "./page";
    snprintf(file, length+1, "%s", buffer + start);
    char* output = (char*)malloc(length+1 + strlen(folder));
    sprintf(output, "%s%s", folder, file);
    free(file);
    return output;   
}

