#include "commands.h"

void handleCommand(int ts, char **words, HashTable *table, LRUList *lru){
    if(strcmp(words[0], "SET")==0){
        set(table, lru, words[1], words[2]);
        printHashMap(table);
        printf("===================\n");
        printLRUList(lru);
        char ch='1';
        write(ts, &ch, 1);
    } else if(strcmp(words[0], "GET")==0){
        char *name=get(table, lru, words[1]);
        printf("The %s(Key)--> %s(Value)\n", words[1], name);
        write(ts, (void*)name, strlen(name));
    } else if(strcmp(words[0], "DEL")==0){
        deleteKey(table, words[1]);
        char ch='1';
        write(ts, &ch, 1);
    } else if(strcmp(words[0], "EXISTS")==0){
        char ch=existsKey(table, words[1]);
        write(ts, &ch, 1);
    } else if((strcmp(words[0], "Total")==0) && (strcmp(words[1], "Keys")==0)){
        char ch=table->count+'0';
        printf("Total Keys: %d\n", table->count);
        write(ts, &ch, 1);
    } else if((strcmp(words[0], "Hashmap")==0) && (strcmp(words[1], "Size")==0)){
        char ch=table->size+'0';
        printf("HashTable Size: %d\n", table->size);
        write(ts, &ch, 1);
    } else if((strcmp(words[0], "LRU")==0) && (strcmp(words[1], "Size")==0)){
        char ch=lru->size+'0';
        printf("HashTable Size: %d\n", lru->size);
        write(ts, &ch, 1);
    }
}