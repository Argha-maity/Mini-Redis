#include "server.h"

void* handleClient(void* arg){
    ThreadArgs *args = (ThreadArgs*)arg;

    int ts=args->cs;
    HashTable *table=args->table;
    LRUList *lru=args->lru;
    char data[DATASIZE], **words;

    int n = read(ts, data, DATASIZE-1);
    if(n > 0){
        data[n]='\0';
        words=parseString(data);
        handleCommand(ts, words, table, lru);
        free(words);
    }
    close(ts);
    free(args); 
    return NULL;
}

void server(int port, char ip[], HashTable *table, LRUList *lru){
    int ss=socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in saddr, caddr;
    saddr.sin_family=AF_INET;
    inet_aton(ip, &(saddr.sin_addr));
    saddr.sin_port=htons(port);

    bind(ss, (struct sockaddr*)&saddr, sizeof(saddr));

    listen(ss, 5); 
    printf("Server is running...\n");

    socklen_t clen=sizeof(caddr);
    
    while(1){ 
        int ts=accept(ss, (struct sockaddr*)&caddr, &clen);   

        pthread_t thrd;

        ThreadArgs *args=malloc(sizeof(ThreadArgs));
        args->cs=ts;
        args->table=table;
        args->lru=lru;

        pthread_create(&thrd, NULL, handleClient, args);
        pthread_detach(thrd);
    }
    close(ss);
}