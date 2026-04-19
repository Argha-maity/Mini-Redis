#include "hashmap.h"

HashTable *initHashTable(int n){
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));
    table->size = n;
    table->count = 0;
    table->buckets = (Node**)malloc(sizeof(Node*) * n);

    for (int i = 0; i < n; i++) {
        table->buckets[i] = NULL;
    }

    return table;
}

unsigned long calculateHash(char str[]){
    unsigned long hash = 5381;
    int c;
    
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    return hash;
}

void deleteKey(HashTable *table, char *key){
    unsigned int index = calculateHash(key) % table->size;

    Node *temp = table->buckets[index];
    Node *prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            if (prev == NULL) {
                table->buckets[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            table->count--;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void set(HashTable *table, LRUList *lru, char *key, char *value) {
    unsigned int index = calculateHash(key) % table->size;
    Node *temp = table->buckets[index];

    //the key already exists
    while(temp != NULL) {
        if(strcmp(temp->key, key) == 0) {
            strcpy(temp->value, value);
            moveToHead(lru, temp->lru_ptr);
            return;
        }
        temp = temp->next;
    }

    if (table->buckets[index] != NULL) {
        printf("Collision occur, Key '%s' is joining bucket %d which already has data.\n", key, index);
    }

    if(lru->size >= lru->maxSize){
        char *keyToEvict = removeTail(lru);  //remove from LRU list
        if(keyToEvict != NULL){
            printf("Evicting Least Recently Used key: %s\n", keyToEvict);
            deleteKey(table, keyToEvict);   //delete from hashmap
            free(keyToEvict);
        }
    }

    //key doesn't exist
    Node *newNode=(Node*)malloc(sizeof(Node));
    strcpy(newNode->key, key);
    strcpy(newNode->value, value);

    newNode->lru_ptr=addToHead(lru, key);

    newNode->next=table->buckets[index];
    table->buckets[index] = newNode;
    table->count++;
}

char* get(HashTable *table, LRUList *lru, char *key) {
    unsigned int index = calculateHash(key)%table->size;
    Node *temp = table->buckets[index];

    while (temp != NULL) {
        if(strcmp(temp->key, key) == 0) {
            moveToHead(lru, temp->lru_ptr);
            return temp->value;
        }
        temp = temp->next;
    }
    return NULL;
}

char existsKey(HashTable *table, char *key){
    unsigned int index=calculateHash(key)%table->size;
    Node *ptr=table->buckets[index];
    while(ptr!=NULL){
        if(strcmp(ptr->key, key) == 0)
            return '1';
        ptr=ptr->next;
    }
    return '0';
}

void printHashMap(HashTable *table) {
    printf("\n========== HASHMAP VISUALIZATION ==========\n");
    printf("Table Size: %d | Total Entries: %d | Load Factor: %.2f\n", table->size, table->count, (float)table->count / table->size);
    printf("===========================================\n");
    
    for (int i = 0; i < table->size; i++) {
        printf("Bucket [%2d]: ", i);
        
        if (table->buckets[i] == NULL) {
            printf("NULL\n");
        } else {
            Node *temp = table->buckets[i];
            int node_count = 0;
            
            while (temp != NULL) {
                printf("→ [%s: %s] ", temp->key, temp->value);
                temp = temp->next;
                node_count++;
            }
            printf("(%d node%s)\n", node_count, node_count > 1 ? "s" : "");
        }
    }
    printf("===========================================\n\n");
}

// void testCollisions(HashTable *table) {
//     printf("\n--- TESTING COLLISION HANDLING ---\n");
//     set(table, "abc", "value1");     // These might collide based on hash
//     set(table, "cba", "value2");     // depending on your hash function
//     set(table, "bac", "value3");
// }

// void testUpdates(HashTable *table) {
//     printf("\n--- TESTING VALUE UPDATES ---\n");
//     printf("Before update: %s\n", get(table, "user:1"));
//     set(table, "user:1", "Updated Argha");
//     printf("After update:  %s\n", get(table, "user:1"));
// }

// void testNonExistent(HashTable *table) {
//     printf("\n--- TESTING NON-EXISTENT KEYS ---\n");
//     char *result = get(table, "nonexistent");
//     if (result == NULL) {
//         printf("Key 'nonexistent' not found (NULL returned) ✓\n");
//     } else {
//         printf("Found: %s\n", result);
//     }
// }

// int main() {
//     int size = 10;
//     HashTable *table = initHashTable(size);
    
//     // printf("\nSetting initial keys...\n");
//     // set(table, "user:1", "Argha");
//     // set(table, "user:2", "Gemini");
//     // set(table, "project", "Mini-Redis");
//     // set(table, "language", "C");
    
//     // printHashMap(table);    
//     return 0;
// }