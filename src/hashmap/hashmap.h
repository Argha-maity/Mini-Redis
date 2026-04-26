#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>
#include "../lru/lru.h"

#ifndef DATASIZE
#define DATASIZE 100
#endif

typedef struct Node {
    char key[DATASIZE];
    char value[DATASIZE];
    struct DoublyLinkedList *lru_ptr; //for O(1) access
    struct Node *next;
} Node;

typedef struct HashTable {
    int size;
    int count; 
    Node **buckets; // Array of Node pointers
} HashTable;

void set(HashTable *table, LRUList *lru, char *key, char *value, bool skipLog);
char* get(HashTable *table, LRUList *lru, char *key);
HashTable *initHashTable(int n);
void printHashMap(HashTable *table);
void deleteKey(HashTable *table, char *key, bool skipLog);
char existsKey(HashTable *table, char *key);

#endif /* HASHMAP_H */