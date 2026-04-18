#include "parser.h"

char **parseString(char str[]){
    char **words=malloc(sizeof(char*) * 10);  
    int count = 0;
    char *token;
    
    token=strtok(str, " ");
    while(token != NULL && count < 10) {
        words[count++] = token;
        token=strtok(NULL, " ");
    }
    
    // for(int i=0; i<count; i++) {
    //     printf("Word %d: %s\n", i, words[i]);
    // }
    return words;
}

// int main(){
//     char str[]="GET name";
//     char **words=parseString(str);

//     for (int i = 0; i < 3; i++) {
//         if(words[i]!=NULL)
//             printf("Word %d: %s\n", i, words[i]);
//     }
//     return 0;
// }