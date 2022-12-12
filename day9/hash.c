#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned long hash_function(char* str) {
    unsigned long i = 0;
    for (int j=0; str[j]; j++)
        i += str[j];
    return i % CAPACITY;
}

Ht_item* create_item(char* key, char* value) {
    Ht_item* item = (Ht_item*) malloc(sizeof(Ht_item));
    item->key = (char*) malloc(strlen(key) + 1);
    item->value = (char*) malloc(strlen(value) + 1);

    strcpy(item->key, key);
    strcpy(item->value, value);

    return item;
}

HashTable* create_table(int size) {
    HashTable* table = (HashTable*) malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item**) calloc(table->size, sizeof(Ht_item*)); 
    for (int i = 0; i < table->size; i++) {
        table->items[i] = NULL; 
    }
    table->overflow_buckets = create_overflow_buckets(table);
    return table;
}

void free_item(Ht_item* item) {
    free(item->key);
    free(item->value);
    free(item);
}

void free_table(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        Ht_item* item = table->items[i];
        free_item(item);
    }
    free(table->overflow_buckets);
    free(table->items);
    free(table);
}

void handle_collision(HashTable* table, unsigned long index, Ht_item* item) {
   Llist* head = table->overflow_buckets[index];

   if (head == NULL) {
       head = allocate_list();
       head->item = item;
       table->overflow_buckets[index] = head;
       return;
   }
   else {
       table->overflow_buckets[index] = list_insert(head, item);
       return;
   }
}

void ht_insert(HashTable* table, char* key, char* value) {
    Ht_item* item = create_item(key, value);

    unsigned long index = hash_function(key);
    
    Ht_item* current_item = table->items[index];

    if (current_item == NULL) {
        if (table->count == table->size) {
            printf("ERROR: HashTable full.\n"); 
            free_item(item);
            return;
        }

        table->items[index] = item;
        table->count++;
    }

    else {
        if (strcmp(current_item->key, key)) {
            strcpy(table->items[index]->value, value);
            return; 
        }
        else {
            handle_collision(table, index, item);
            return;
        }
    }
}


char* ht_search(HashTable* table, char* key) {
    int index = hash_function(key);
    Ht_item* item = table->items[index];
    Llist* head = table->overflow_buckets[index];
    while (item != NULL) {
        if (strcmp(item->key, key) == 0) {
            return  item->value; 
        } 
        if (head == NULL) {
            return NULL; 
        }
        item = head->item;
        head = head->next;
    }
    return NULL;
}


Llist* allocate_list() {
    Llist* list = (Llist*) malloc(sizeof(Llist));
    return list;
}

Llist* list_insert(Llist* list, Ht_item* item) {
    if (!list) {
        Llist* head = allocate_list();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    }
    else if (list->next == NULL) {
        Llist* node = allocate_list();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }

    Llist* temp = list;
    while (temp->next->next) {
        temp = temp->next; 
    }

    Llist* node = allocate_list();
    node->item = item;
    node->next = NULL;
    temp->next = node;

    return list;
}

Ht_item* linkedlist_remove(Llist* list) {
    // Removes the head from the linked list
    // and returns the item of the popped element
    if (!list)
        return NULL;
    if (!list->next)
        return NULL;
    Llist* node = list->next;
    Llist* temp = list;
    temp->next = NULL;
    list = node;
    Ht_item* it = NULL;
    memcpy(temp->item, it, sizeof(Ht_item));
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);
    return it;
}

void free_linkedlist(Llist* list) {
    Llist* temp = list;
    while (list) {
        temp = list;
        list = list->next;
        free(temp->item->key);
        free(temp->item->value);
        free(temp->item);
        free(temp);
    }
}

Llist** create_overflow_buckets(HashTable* table) {
    // Create the overflow buckets; an array of linkedlists
    Llist** buckets = (Llist**) calloc (table->size, sizeof(Llist*));
    for (int i=0; i<table->size; i++){
        buckets[i] = NULL;
    }
    return buckets;
}

void free_overflow_buckets(HashTable* table) {
    // Free all the overflow bucket lists
    Llist** buckets = table->overflow_buckets;
    for (int i=0; i<table->size; i++) {
        free_linkedlist(buckets[i]);
    }
    free(buckets);
}
