#include "server/server.h"
#include "hashmap/hashmap.h"
#include "lru/lru.h"
#include "persistence/persistence.h"

int main(){
    int size=3;
    HashTable *table=initHashTable(size);
    LRUList *lru=initLRUList(size);
    replay(table, lru);
    sleep(10);
    server(1234, "127.0.0.1", table, lru);
    return 0;
}