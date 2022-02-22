#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include "common.h"

int main(int argc, char *argv[]){
     //Check number of input args
    if(argc != 2){
        fprintf(stderr, "Usage:\n\t%s port\n", argv[0]);
        return 1;
    }

    // Convert input to port number
    uint16_t port = string_to_port(argv[1]);

    int sock = 0, valread;
    struct sockaddr_in serv_addr;

    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        die("socket");
    } 
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0){
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        printf("\nConnection Failed \n");
        return -1;
    }
    //*************************************************************************************
    char msg[100];
    value_t inputUser;
    initmsg_t initmsg;
    read_full(sock, &initmsg, sizeof(initmsg) );

    msg_t msgStruct = {TOO_HIGH, 0};
    do{
        printf("Client input: ");
        if(fgets(msg, sizeof(msg), stdin) != NULL) inputUser = atoi(msg);
        else die("fgets");

        msgStruct.value = inputUser;
        write_full(sock, &msgStruct, sizeof(msgStruct));
        read_full(sock , &msgStruct, sizeof(msgStruct));

        if (msgStruct.cmd == TOO_LOW) printf("c'est plus\n");
        else if (msgStruct.cmd == TOO_HIGH) printf("c'est moins\n");
        
    } while (msgStruct.cmd != WIN && msgStruct.cmd != LOSE);
    return 0;
}
