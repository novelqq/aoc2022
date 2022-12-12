#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int parse_string(const char* input) {
    static char chars[5];
    int count;
    if((count = sscanf(input, "%s %s %s %s\n", &chars[0], &chars[1], &chars[2], &chars[3]) != 1)) {
        //printf("scanf count: %d\n", count);
        //printf("chars: %c, %c, %c, %c\n", chars[0], chars[1], chars[2], chars[3]);
        return 0;
    }
    for (int i = 0; i <= 4; i++) {
        for (int k = i+1; k <= 4; k++) {
            if (strncmp(&chars[i], &chars[k], 1) == 0) {
                //printf("these match: %c, %c\n", chars[i], chars[k]);
                return 0;
            } 
        }
    }
    return 1;
}
int parse_string2(const char* input) {
    static char chars[14];
    int count;
    if((count = sscanf(
                    input, 
                    "%s %s %s %s %s %s %s %s %s %s %s %s %s, %s\n", 
                    &chars[0], 
                    &chars[1], 
                    &chars[2], 
                    &chars[3], 
                    &chars[4], 
                    &chars[5], 
                    &chars[6],
                    &chars[7],
                    &chars[8],
                    &chars[9],
                    &chars[10],
                    &chars[11],
                    &chars[12],
                    &chars[13]) != 1)) 
    {
        //printf("scanf count: %d\n", count);
        //printf("chars: %c, %c, %c, %c\n", chars[0], chars[1], chars[2], chars[3]);
        return 0;
    }
    for (int i = 0; i <= 13; i++) {
        for (int k = i+1; k <= 13; k++) {
            if (strncmp(&chars[i], &chars[k], 1) == 0) {
                //printf("these match: %c, %c\n", chars[i], chars[k]);
                return 0;
            } 
        }
    }
    return 1;
}
int main() {
    FILE* file = fopen("input.txt", "r");
    static char line[15], step[2];
    fpos_t pos;
    int count = 14;
    fgetpos(file, &pos);
    while (fgets(line, sizeof(line), file)) {
        //printf("Line: %s\n", line);
        //printf("pos: %d\n", count);

        if(parse_string2(line) == 1) {
            printf("Marker after position %d.\n", count);
            return 1;
        }
                fsetpos(file, &pos);
        fgets(step, sizeof(step), file);
        fgetpos(file, &pos);
        count++;
    }
    printf("No marker found.\n");
}
