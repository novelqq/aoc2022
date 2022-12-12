#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 10000
#define MAX_FILES 5000
int parse_dirname(const char* input, char* dir_name) {
    if(sscanf(input, "$ cd %s\n", dir_name) != 1)  {
        return 0;
    }
    return 1;
}
int parse_lsdir(const char* input, char* dir_name) {
    if (sscanf(input, "dir %s\n", dir_name) != 1) {
        return 0;
    }
    return 1;
}

int parse_file(const char* input, char* file_name, unsigned long long int* file_size) {
    printf("input: %s\n", input); 
    char* ptr;
    unsigned long long int number = strtol(input, &ptr, 10);
    printf("strtol number: %llu\n", number);
    if (sscanf(input, "%llu %s\n", file_size, file_name) != 2) {
        return 0; 
    }
    *file_size = number;
    printf("Filesize:  %llu, FileName: %s\n", *file_size, file_name);
    return 1;
}
typedef struct {
    char name[256];
    int size; 
} fFile;
typedef struct dir {
    char name[256];
    struct dir* parent;
    struct dir* children[MAX_CHILDREN];
    fFile files[MAX_FILES];
    int file_index, child_index;
    unsigned long long int size;
    struct dir* next;
} Dir;

fFile* createFile(char* name, int size) {
    fFile* file = malloc(sizeof(fFile));
    strcpy(file->name, name);
    file->size = size;
    return file;
}
Dir* createDir(char* name, Dir* parent) {
    Dir* dir = malloc(sizeof(Dir));
    dir->parent = parent;
    strcpy(dir->name, name);
    dir->file_index = 0;
    dir->child_index = 0;
    dir->size = 0;
    dir->next = 0;
    return dir;
}
int main() {
    FILE* file = fopen("input.txt", "r");
    static char line[1000];
    char *tokens[4];
    char* token;
    int token_index;
    char dir_name[256];
    char file_name[256];
    unsigned long long int file_size = 0;
    Dir* current_dir = createDir("/", NULL);
    Dir* root = current_dir;
    printf("Name of Dir: %s\n", current_dir->name);
    
    Dir* dirtracker = root;
    while (fgets(line, sizeof(line), file)) {
        printf("Current Dir: %s\n", current_dir->name);
        printf("Line: %s\n", line);
        //printf("strncmp: %d\n", strncmp(line, "dir", strlen("dir")));
        if (strncmp(line, "dir", strlen("dir")) == 0) {
            printf("dir found\n");
            if (parse_lsdir(line, dir_name) == 0) {
                printf("ERROR with parse_lsdir\n");
                return -1;
            }
            Dir* temp = createDir(dir_name, current_dir);
            current_dir->children[current_dir->child_index] = temp;
            current_dir->child_index++;
            dirtracker->next = temp;
            dirtracker = dirtracker->next;

        }
        else if(strncmp(line, "$ cd /\n", strlen("$ cd /")) == 0) {
            printf("c deez /\n");
            current_dir = root;
        }
        else if (strncmp(line,"$ ls\n", strlen("$ ls")) == 0) {
            printf("ls deez nuts\n");
            continue; 
        }
        else if (strncmp(line, "$ cd ..", strlen("$ cd ..")) == 0) {
            if(current_dir->parent != NULL) {
                printf("going up dir\n");
                current_dir = current_dir->parent;
            }
        }
        else if (strncmp(line, "$ cd", strlen("$ cd")) == 0) {
            printf("cd into dir\n");
            if (parse_dirname(line, dir_name) == 0) {
                printf("ERROR with parse_dirname\n");
                return -1;
            }
            for (int i = 0; i < current_dir->child_index; i++) {
                printf("looking at children[%d] with name: %s comparing with dir_name: %s\n", i, current_dir->children[i]->name, dir_name);
                if (strncmp(current_dir->children[i]->name, dir_name, strlen(dir_name)) == 0) {
                    current_dir = current_dir->children[i]; 
                    printf("cd to %s\n", current_dir->name);
                } 
            }
        }
        else if (strncmp(line, "dir", strlen("dir")) == 0) {
            printf("dir found\n");
            if (parse_lsdir(line, dir_name) == 0) {
                printf("ERROR with parse_lsdir\n");
                return -1;
            }
            Dir* temp = createDir(dir_name, current_dir);
            current_dir->children[current_dir->child_index] = temp;
            current_dir->child_index++;
            dirtracker->next = temp;
            dirtracker = dirtracker->next;
        }
        else {
            printf("ELSE\n");
            // probably a file xDDDDDD
            if (parse_file(line, file_name, &file_size) == 0) {
                // probably found some garbo newline
                continue;
            }
            printf("filesize: %llu\n", file_size);

            fFile* temp = createFile(file_name, file_size);
            printf("filesize: %llu\n", file_size);
            current_dir->files[current_dir->file_index] = *temp;
            printf("filesize: %llu\n", file_size);
            current_dir->file_index++;
            Dir* curr = current_dir;
            printf("filesize: %llu\n", file_size);
            while (curr != NULL) {
                curr->size += file_size;
                curr = curr->parent;
            }
        }
    }

    // now traverse the traverse the tree
    Dir* curr = root;
    unsigned long long int smallest = (unsigned long long int) -1;
    unsigned long long int sum = 0;
    unsigned long long int space_needed = 30000000 - (70000000 - root->size);
    while (curr != NULL) {
        printf("curr->size: %llu\n", curr->size);
        if (curr->size <= 100000) {
            sum += curr->size;
        }
        if (curr->size >= space_needed && curr->size < smallest) {
            smallest = curr->size; 
        }
        Dir* temp = curr;
        curr = curr->next;
        /*for (int i = 0; i < temp->file_index; i++) {
            fFile* f = &temp->files[i];
            free(f); 
        }*/
        free(temp);
    }

    printf("The sum is : %llu\n", sum);
    printf("The best file to delete is: %llu\n", smallest);
}
