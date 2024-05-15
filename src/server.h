#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>


int setup(int* sockfd, struct sockaddr_in* host_addr, int port);
int server_connect(int* sockfd, struct sockaddr_in* host_addr);
int buffer_read(int socket, char* buffer, int buffersize);
int buffer_write(int socket, void* resp, long len);
char* file_to_string(const char* path);
char* concat_strings(char* str1, char* str2);
char* file_to_buffer(const char* path, long* length);
char* response(const char* header, const char* path, long* resp_length);

#endif