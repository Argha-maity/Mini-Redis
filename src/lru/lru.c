#include "lru.h"

LRUList *initLRUList(int n){
    LRUList *cache=(LRUList*)malloc(sizeof(LRUList));
    cache->head=NULL;
    cache->tail=NULL;
    cache->maxSize=n;
    cache->size=0;
    return cache;
}

DoublyLinkedList *createNode(char *key){
    DoublyLinkedList *newNode = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    strcpy(newNode->key, key);
    newNode->prev=NULL;
    newNode->next=NULL;
    return newNode;
}

void moveToHead(LRUList *list, DoublyLinkedList *node){
    if (list->head == node) 
        return;

    //Detach from current position
    if(node->prev != NULL) 
        node->prev->next=node->next;
    if(node->next != NULL) 
        node->next->prev = node->prev;
    if(list->tail == node) 
        list->tail = node->prev;

    //Insert at head
    node->next=list->head;
    node->prev=NULL;
    if(list->head != NULL) 
        list->head->prev = node;
    list->head=node;
    if(!list->tail) 
        list->tail = node;
}

DoublyLinkedList* addToHead(LRUList *list, char *key){
    DoublyLinkedList *newNode = createNode(key);
    newNode->next=list->head;

    if(list->head != NULL) 
        list->head->prev=newNode;
    list->head=newNode;
    if(!list->tail) 
        list->tail = newNode;

    list->size++;
    
    return newNode;
}

char* removeTail(LRUList *list){
    if(!list->tail) 
        return NULL;

    DoublyLinkedList *oldTail = list->tail;

    char *keyToRemove = malloc(DATASIZE);
    strcpy(keyToRemove, oldTail->key);

    if(list->head == list->tail){
        list->head = NULL;
        list->tail = NULL;
    }else{
        list->tail = oldTail->prev;
        if(list->tail)
            list->tail->next = NULL;
    }

    free(oldTail);
    list->size--;
    return keyToRemove;
}

void printLRUList(LRUList *list){
    printf("====LRU VISUALIZATION===\n");
    if (!list->head) {
        printf("List is empty\n");
        return;
    }
    
    printf("LRU List (MRU -> LRU): ");
    DoublyLinkedList *current = list->head;
    int position = 1;
    
    while (current) {
        printf("[%d:%s]", position, current->key);
        if (current->next) {
            printf(" <-> ");
        }
        current = current->next;
        position++;
    }
    
    printf("\nHead (MRU): %s\n", list->head ? list->head->key : "NULL");
    printf("Tail (LRU): %s\n", list->tail ? list->tail->key : "NULL");
    printf("---\n");
}

// int main() {
//     LRUList *cache = initLRUList(3);
    
//     printf("=== LRU Cache Simulation (Max Size: %d) ===\n\n", cache->maxSize);
    
//     // Add elements to the cache
//     addToHead(cache, "A");
//     addToHead(cache, "B");
//     addToHead(cache, "C");
//     printLRUList(cache);
    
//     printf("4. Accessing 'A' (moving to head):\n");
//     // Find node with key 'A' and move to head
//     DoublyLinkedList *current = cache->head;
//     while (current && strcmp(current->key, "A") != 0) {
//         current = current->next;
//     }
//     if (current) {
//         moveToHead(cache, current);
//     }
//     printLRUList(cache);
    
//     printf("5. Adding 'D' (cache is full, should remove LRU):\n");
//     if (cache->head && (cache->head->next && cache->head->next->next)) {
//         // Check if cache is full (size >= maxSize)
//         int size = 0;
//         current = cache->head;
//         while (current) {
//             size++;
//             current = current->next;
//         }
        
//         if (size >= cache->maxSize) {
//             char *removed = removeTail(cache);
//             printf("Removed LRU element: %s\n", removed);
//         }
//     }
//     addToHead(cache, "D");
//     printLRUList(cache);
    
//     printf("6. Accessing 'B' (moving to head):\n");
//     current = cache->head;
//     while (current && strcmp(current->key, "B") != 0) {
//         current = current->next;
//     }
//     if (current) {
//         moveToHead(cache, current);
//     }
//     printLRUList(cache);
    
//     printf("7. Adding 'E' (should remove LRU):\n");
//     int size = 0;
//     current = cache->head;
//     while (current) {
//         size++;
//         current = current->next;
//     }
    
//     if (size >= cache->maxSize) {
//         char *removed = removeTail(cache);
//         printf("Removed LRU element: %s\n", removed);
//     }
//     addToHead(cache, "E");
//     printLRUList(cache);
    
//     free(cache);
//     return 0;
// }