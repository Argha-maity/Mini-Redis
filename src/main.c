#include "server/server.h"
#include "hashmap/hashmap.h"
#include "lru/lru.h"

int main(){
    int size=3;
    HashTable *table=initHashTable(size);
    LRUList *lru=initLRUList(size);
    server(1234, "127.0.0.1", table, lru);
    return 0;
}