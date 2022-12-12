#include <stdio.h>
#include <stdlib.h>
int parse_string(const char* input, int* a, int* b, int* c, int* d) {
    if(sscanf(input, "%d-%d,%d-%d\n", a, b, c, d) != 4) {
        return 0;
    }
    return 1;
}
int main() {
    FILE* file = fopen("input.txt", "r");
    static char line[13];
    int start1, start2, end1, end2;
    int count, count2;

    while (fgets(line, sizeof(line), file)) {
        //printf("Line:  %s", line);
        if (parse_string(line, &start1, &end1, &start2, &end2) == 1) {
            //printf("parsed: %d %d %d %d\n", start1, end1, start2, end2);
            if((start1 <= start2 && end1 >= end2) || (start2 <= start1 && end2 >= end1)){
                count++;
            }
            if((start2 <= start1 && start1 <= end2) || (start2 <= end1 && end1 <= end2) || (start1 <= start2 && start2 <= end1) || (start1 <= end2 && end2 <= end1)) {
                count2++;
            }
        }
    }

    printf("Total pairs: %d\n", count);
    printf("Total pairs: %d\n", count2);


}
