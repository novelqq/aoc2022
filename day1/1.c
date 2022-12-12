#include <stddef.h>
#include <stdio.h>

int main() {
    FILE* f = fopen("./input.txt","r");
    int buf[2048];
    size_t read = 0;
    int curr = 0;
    while ((read = fread(buf, sizeof(int), 2048, f)) > 0) {
        for (size_t i = 0; i < read; i++) {
            printf("buf[i]: %d\n", buf[i]);
        } 
    }
}
