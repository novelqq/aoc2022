#include "hash.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define ROPE_LENGTH 2
int parse_command(const char* input, char* dir, int* num) {
    if(sscanf(input, "%c %d\n", dir, num) != 2) {
        return 0;
    }
    return 1;
}

struct pos {
    int x;
    int y;
};
void moveTail(struct pos* head, struct pos* tail) {
    int dx = head->x - tail->x;
    int dy = head->y - tail->y;
    
    if (abs(dx) <= 1 && abs(dy) <= 1) {
        return; 
    }
    if (abs(dx) > 1 || (abs(dx) + abs(dy)) > 2) {
        tail->x += copysign(1, dx); 
    }
    if (abs(dy) > 1 || (abs(dx) + abs(dy)) > 2) {
        tail->y += copysign(1, dy); 
    }
    
}
int count = 0;
void addposition(HashTable* positions, char* xstr, char* ystr, char* xystr, struct pos * tail) {
    sprintf(xstr, "%d", tail->x);
    sprintf(ystr, "%d", tail->y);
    strcpy(xystr, xstr);
    strcat(xystr, ",");
    strcat(xystr, ystr);
    char* temp;
    if ((temp = ht_search(positions, xystr)) == NULL) {
        count++;
        ht_insert(positions, xystr, "y"); 
    }

}
int main() {
    FILE* file = fopen("test.txt", "r");
    HashTable* positions = create_table(CAPACITY);
    ht_insert(positions, "0,0", "y");
    int num;
    char dir; 
    char xstr[100], ystr[100], xystr[200];
    static char line[100];
    struct pos head = (struct pos) {0, 0};
    struct pos tail = (struct pos) {0, 0};
    //printf("hashmap get {0,0}: %s\n", hashmap_get(positions, "00")); 
    //tail.x = -5;
    //tail.y = 123;
    //addposition(positions, xstr, ystr, xystr, &tail);
    //printf("hashmap get {-5,123}: %s\n", hashmap_get(positions, "-5123")); 
    while (fgets(line, sizeof(line), file)) {
        if (parse_command(line, &dir, &num) == 1) {
            if (dir == 'U') {

                while (num > 0) {
                    head.y += 1;
                    moveTail(&head, &tail);
                    addposition(positions, xstr, ystr, xystr, &tail);
                    num--;
                }
                continue;
            }
            else if (dir == 'D') {

                //printf("D Found\n");
                while (num > 0) {
                    head.y -= 1; 
                    moveTail(&head, &tail);
                    addposition(positions, xstr, ystr, xystr, &tail);
                    num--;
                }
                continue;
            }
            else if (dir == 'L') {

                //printf("L Found\n");
                while (num > 0) {
                    head.x -= 1; 
                    moveTail(&head, &tail);
                    addposition(positions, xstr, ystr, xystr, &tail);
                    num--;
                }
                continue;
            }
            else if (dir == 'R') {

                //printf("R Found\n");
                while (num > 0) {
                    head.x += 1; 
                    moveTail(&head, &tail);
                    addposition(positions, xstr, ystr, xystr, &tail);
                    num--;
                }
                continue;
            }
        }
    }
    fclose(file);
    printf("Positions: %d\n",count);
    free_table(positions);
}
