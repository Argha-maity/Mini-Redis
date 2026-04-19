#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include "../parser/parser.h"
#include "../hashmap/hashmap.h"
#include "../commands/commands.h"

#define DATASIZE 100

typedef struct ThreadArgs{
    int cs;
    HashTable *table;
    LRUList *lru;
}ThreadArgs;

#ifndef SERVER_H
#define SERVER_H

void server(int port, char ip[], HashTable *table, LRUList *lru);

#endif