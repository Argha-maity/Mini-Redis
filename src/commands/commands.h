#ifndef COMMANDS_H
#define COMMANDS_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include "../hashmap/hashmap.h"
#include "../lru/lru.h"

void handleCommand(int ts, char **words, HashTable *table, LRUList *lru);

#endif