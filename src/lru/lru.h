#ifndef LRU_H
#define LRU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DATASIZE
#define DATASIZE 100
#endif

typedef struct DoublyLinkedList {
    char key[DATASIZE];
    struct DoublyLinkedList *prev;
    struct DoublyLinkedList *next;
} DoublyLinkedList;

typedef struct LRUList {
    DoublyLinkedList *head; // Most Recently Used (MRU)
    DoublyLinkedList *tail; // Least Recently Used (LRU)
    int size;
    int maxSize;
} LRUList;

/* Function prototypes implemented in lru.c */
DoublyLinkedList *createNode(char *key);
void moveToHead(LRUList *list, DoublyLinkedList *node);
DoublyLinkedList* addToHead(LRUList *list, char *key);
char* removeTail(LRUList *list);
LRUList *initLRUList(int n);
void printLRUList(LRUList *list);

#endif /* LRU_H */