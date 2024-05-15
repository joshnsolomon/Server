#include <stdio.h>



int main(){

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

    printf("%s\n", buffer);

    return 0;
}