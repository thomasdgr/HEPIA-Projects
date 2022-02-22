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

#define MIN_VALUE 0
#define MAX_VALUE 255
#define NB_TRIES 200

// Le client pense à un nombre et le serveur doit le trouver
// sachant que le nombre est choisi aléatoirement entre 0 et 255
// le serveur a 200 essais pour trouver le nombre on doit donc envoyer
// un premier message vers le serveur en lui disant entre quoi et quoi se trouve
// notre nombre random.


// get a random value between min and max
// urandom is read up to moment where valid
// value is obtained. Theoretically this function
// could loop for ever
value_t get_random_value(value_t min, value_t max) { // c'est du uint8_t
    // Open random generator
    int fd = open("/dev/urandom", O_RDONLY);
    if( fd == -1 )
        die("/dev/urandom");

    // Read from random generator as long as value is not in range
    value_t value;
    do {
        read_full(fd, &value, sizeof(value));
    } while( value < min || value > max );

    close(fd);

    return value;
}

// Manages each client on a different socket
// retruns 0 if the client lost and different value otherwise
int process_client(int socket, struct sockaddr_in client) {

    // Get random number in range
    value_t value = get_random_value(MIN_VALUE, MAX_VALUE);
    printf("Selected value for client %d: %d\n", socket, value);

    // Send init message to client
    initmsg_t initmsg = { MIN_VALUE, MAX_VALUE };
    write_full(socket, &initmsg, sizeof(initmsg));

    // As long as the client does not exeed the maximum number tries
    // or found the correct answer, read proposition and send answer
    long int proposition = 0;
    msg_t msg = {TOO_LOW, value};
    while ( msg.cmd != LOSE &&  msg.cmd != WIN ) {
        // Read client proposition
        read_full(socket, &msg, sizeof(msg));
        proposition++;

        printf("Client %d proposes %d\n", socket, msg.value);

        // Check proposition against true value
        if(msg.value == value) {
            msg.cmd = WIN;
        } else {
            if(proposition < NB_TRIES) {
                if(msg.value < value)
                    msg.cmd = TOO_LOW;
                else
                    msg.cmd = TOO_HIGH;
            } else
                msg.cmd = LOSE;
        }
                
        // Send answer
        msg.value = value;
        write_full(socket, &msg, sizeof(msg));
    } ;

    printf("Client %d ", socket);
    if(msg.cmd == WIN)
        printf("wins !!!\n");
    else
        printf("miserably lost...");
    printf("\n");

    return msg.cmd == WIN;
}

// The server takes one parameter: the port on which it will listen
// it then attaches to any interface available
int main(int argc, char *argv[]) {

    //Check number of input args
    if(argc != 2) {
        fprintf(stderr, "Usage:\n\t%s port\n", argv[0]);
        return 1;
    }

    // Convert input to port number
    uint16_t port = string_to_port(argv[1]);

    // Create a TCP/IP socket on which the server will listen for connexions
    int socket_wait = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_wait == -1)
        die("socket");

    // Associate address and port number with socket
    struct sockaddr_in server_addr;
    memset( &server_addr, 0, sizeof(server_addr) );
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);
    if( bind(socket_wait, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1 )
        die("bind");
    
    // Mark socket as a listenning socket
    if( listen(socket_wait, 5) == -1)
        die("listen");

    // Wait and accept connections as they come
    int socket_proc; // processing socket which will be used for communication with the client
    struct sockaddr_in client_addr;
    while(1) {
        
        // Wait for client
        socklen_t client_addr_length = sizeof(client_addr);
        socket_proc = accept(socket_wait, (struct sockaddr*) &client_addr, &client_addr_length);
        if (socket_proc > 0) {
            // Client connected print information about client ip
            char ip[INET_ADDRSTRLEN];
            if( inet_ntop(AF_INET, &client_addr.sin_addr, ip, sizeof(ip)) != NULL )
                printf("Client %d connected with ip %s:%d\n", socket_proc, ip, ntohs(client_addr.sin_port));
            else
                printf("Client connected but could not retreive address !!!\n");

            // Fork to process client
            pid_t pid = fork();
            if (pid == -1) { //error
                die("fork");
            }
            else if (pid == 0) { //child
                //Fork again to daemonize (i.e. let the parent die and get process 1 as father)
                pid = fork();
                if (pid == -1) { //error
                    die("fork2");
                }
                else if (pid == 0) { // grand child
                    int res = process_client(socket_proc, client_addr);
                    close(socket_proc);
                    return  res;
                }
                return 0; // the second parent dies
            }

            // This stage is reached by the server (i.e. first parent) only
            int status;
            waitpid(pid, &status, 0);
            close(socket_proc);
        }
        else
            perror("accept");
    }
}
