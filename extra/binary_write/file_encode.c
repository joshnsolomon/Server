#include <stdio.h>

#define FLOWERS "../page/flowers3.jpg"

int main(){
    printf("hello\n");


    FILE* flowers = fopen(FLOWERS,"rb");
    FILE* output = fopen("flower_output.jpg","wb");

    fseek(flowers, 0, SEEK_END);
    long length = ftell(flowers);
    fseek(flowers, 0, SEEK_SET);

    printf("FILE LENGTH: %ld\n", length); 

    char buffer[length];

    fread(buffer, sizeof(char), length, flowers);
    fwrite(buffer, sizeof(char), length, output);


    fclose(flowers);
    fclose(output);


    return 0;
}