#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int visl;
    int visr;
    int visu;
    int visd;
    int height;
} tree_t;
static tree_t map[99][99];

int getScenicScore(int x, int y) {
    int u = y+1;
    int ucount = 0;
    while (u < 99) {
        ucount++;
        if (map[x][u].height >= map[x][y].height) {
            break; 
        } 
        u++;
    }
    int d = y-1;
    int dcount = 0;
    while (d >= 0) {
        dcount++; 
        if (map[x][d].height >= map[x][y].height) {
            break; 
        }
        d--;
    }
    int l = x+1;
    int lcount = 0;
    while (l < 99) {
        lcount++;
        if (map[l][y].height >= map[x][y].height) {
            break;
        } 
        l++;
    }
    int r = x-1;
    int rcount = 0;
    while (r >= 0) {
        rcount++;
        if (map[r][y].height >= map[x][y].height) {
            break;
        }
        r--;
    }

    return ucount * dcount * rcount * lcount;
}
int main() {
    FILE* file = fopen("input.txt", "r");

    int x = 0;
    int y = 0;
    char tree[2];

    while (fgets(tree, sizeof(tree), file)) {
        printf("Tree: %s\n", tree);
        if (strncmp(tree, "\n", strlen("\n")) == 0) {
            x++;
            y = 0;
        }
        else {
            map[x][y] = (tree_t) { 0, 0, 0, 0, atoi(tree)};

            printf("map[%d][%d]: %d\n", x, y, map[x][y].height);
            y++;
        }
    }
    
    for (int i = 0; i < 99; i++) {
        
        int max_l = -1;
        int max_r = -1;
        for (int k = 0; k < 99; k++) {
            if (map[i][98 - k].height > max_r) {
                max_r = map[i][98 - k].height;
                map[i][98 - k].visr = 1;
            }
            if (map[i][k].height > max_l) {
                max_l = map[i][k].height;
                map[i][k].visl = 1;
            }
        }
    }

    for (int k = 0; k < 99; k++) {
        int max_u = -1;
        int max_d = -1;
        for (int i = 0; i < 99; i++) {
            if (map[98 - i][k].height > max_d) {
                max_d = map[98 - i][k].height;
                map[98 - i][k].visd = 1;
            }     
            if (map[i][k].height > max_u) {
                max_u = map[i][k].height;
                map[i][k].visu = 1;
            }
        }
    }

    int vis_count = 0;
    int max_scenic = -1;
    for (int i = 0; i < 99; i++) {
        for (int k = 0; k < 99; k++) {
            if (map[i][k].visu == 1 || map[i][k].visd == 1 || map[i][k].visl == 1 || map[i][k].visr == 1) {
                vis_count++;
            } 
            int scenic = getScenicScore(i, k);
            if (scenic > max_scenic) {
                max_scenic = scenic; 
            }
        } 
    }

    printf("Visible Trees: %d\n", vis_count);
    printf("Max scenic Tree: %d\n", max_scenic);

}
