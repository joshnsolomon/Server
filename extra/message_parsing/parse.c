#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>


int main(){

    //the message to parse
    printf("Hello World\n"); 
    char buffer[] = "GET /flowers3.png HTTP/1.1\r\n"
                     "Host: localhost:8080\r\n"
                     "Connection: keep-alive\r\n"
                     "sec-ch-ua: \"Chromium\";v=\"121\", \"Not A(Brand\";v=\"99\"\r\n"
                     "DNT: 1\r\n"
                     "sec-ch-ua-mobile: ?0\r\n"
                     "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/121.0.0.0 Safari/537.36\r\n"
                     "sec-ch-ua-platform: \"Windows\"\r\n"
                     "Accept: image/avif,image/webp,image/apng,image/svg+xml,image/*,*/*;q=0.8\r\n"
                     "Sec-Fetch-Site: same-origin\r\n"
                     "Sec-Fetch-Mode: no-cors\r\n"
                     "Sec-Fetch-Dest: image\r\n"
                     "Referer: http://localhost:8080/\r\n"
                     "Accept-Encoding: gzip, deflate, br\r\n"
                     "Accept-Language: en-US,en;q=0.9";
    //printf("%s\n", buffer);

    regex_t pattern;
    regmatch_t match[1];
    regcomp(&pattern, "GET [^$]* HTTP", REG_EXTENDED);
    //regcomp(&pattern, " HTTP", REG_EXTENDED);

    char inputs[25];
    int found = regexec(&pattern, buffer, 1, match, 0);

    printf("Was it found? %d\n", found);

    int start = match[0].rm_so + 4;
    int end = match[0].rm_eo - 5;

    int length = end - start;
    printf("length of match %d\n", length);

    char* file = (char*)malloc(length+1);
    char folder[] = "./page";
    snprintf(file, length+1, "%s", buffer + start);
    char* output = (char*)malloc(length+1 + strlen(folder));
    sprintf(output, "%s%s", folder, file);
    free(file);
    printf("%s\n", output);

    return 0;
}