#include "client.h"

void client(int port, char ip[]){
    int cs=socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in saddr;
    saddr.sin_family=AF_INET;
    inet_aton(ip, &(saddr.sin_addr));
    saddr.sin_port=htons(port);

    connect(cs, (struct sockaddr*)&saddr, sizeof(saddr));

    char data[DATASIZE], buffer[DATASIZE];
    
    // printf("Data received from client: %s", data);
    printf("Enter the data: ");
    fgets(data, DATASIZE, stdin);
    data[strcspn(data, "\n")] = 0;  // Remove trailing newline    
    write(cs, (void*)data, strlen(data));

    read(cs, (void*)buffer, DATASIZE);
    printf("Result: %s\n", buffer);

    close(cs);
}