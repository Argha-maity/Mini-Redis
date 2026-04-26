#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 100

#ifndef PERSISTENCE_H
#define PERSISTENCE_H

typedef struct HashTable HashTable;
typedef struct LRUList LRUList;

void replay(HashTable *table, LRUList *lru);
void log_command(const char *command, char *key, char *value);

#endif 