#ifndef HASH_H
#define HASH_H

#define CAPACITY 50000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Llist Llist;
typedef struct Ht_item Ht_item;
typedef struct HashTable HashTable ;

struct Llist {
    Ht_item* item;
    Llist* next;
};



struct Ht_item {
    char* key;
    char* value;
};


struct HashTable {
    Ht_item** items;
    Llist** overflow_buckets;
    int size;
    int count;
};

Llist* allocate_list();

unsigned long hash_function(char * str);
Ht_item* create_item(char* key, char* value);
HashTable* create_table(int size); 
void free_item(Ht_item* item);
void free_table(HashTable* table);
void handle_collision(HashTable* table, unsigned long index, Ht_item* item);
void ht_insert(HashTable* table, char* key, char* value);
char* ht_search(HashTable* table, char* key);
Ht_item* linkedlist_remove(Llist* list);
void free_linkedlist(Llist* list);
Llist* list_insert(Llist* list, Ht_item* item);
Llist** create_overflow_buckets(HashTable* table);
void free_overflow_buckets(HashTable* table);
#endif
