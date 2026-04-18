#include "server.h"

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
        char data[DATASIZE], **words;
        int n=read(ts, (void*)data, DATASIZE - 1); 
        if(n > 0) {
            data[n]='\0';  
            printf("Data received from client: %s\n", data);
            
            words=parseString(data);
            
            if(strcmp(words[0], "SET") == 0){
                set(table, lru, words[1], words[2]);
                printHashMap(table);
                printf("===================\n");
                printLRUList(lru);
                char ch='1';
                write(ts, &ch, 1);
            }
            else if(strcmp(words[0], "GET") == 0){
                char *name=get(table, lru, words[1]);
                printf("The %s(Key)--> %s(Value)\n", words[1], name);
                write(ts, (void*)name, strlen(name));
            }
            free(words);
        }
        close(ts);
    }
    close(ss);
}