#include "persistence.h"
#include "../parser/parser.h"
#include "../hashmap/hashmap.h"

void log_command(const char *command, char *key, char *value){
    FILE *fptr=fopen("data/appendonly.aof", "a");
    if(fptr != NULL){
        if(value != NULL)
            fprintf(fptr, "%s %s %s\n", command, key, value);  //for SET 
        else    
            fprintf(fptr, "%s %s\n", command, key);  //for DELETE
    } else {
        printf("File opening failed...");
    }
    fclose(fptr);
}

void replay(HashTable *table, LRUList *lru) {
    FILE *fptr = fopen("data/appendonly.aof", "r");
    
    if (fptr == NULL) {
        printf("No existing AOF file found. Starting with an empty database...\n");
        return; 
    }

    printf("Replaying AOF to restore state...\n");
    char buffer[BUFFERSIZE];

    while (fgets(buffer, BUFFERSIZE, fptr)) {
        buffer[strcspn(buffer, "\n")] = 0;

        char **words = parseString(buffer);
        if (words == NULL) continue;

        if (strcmp(words[0], "SET") == 0) {
            if (words[1] && words[2]) {
                set(table, lru, words[1], words[2], true);
            }
        } else if (strcmp(words[0], "DEL") == 0) {
            if (words[1]) {
                deleteKey(table, words[1], true); 
            }
        }
        free(words);
    }

    fclose(fptr);
    printf("Recovery complete. Items in memory: %d\n", table->count);
}