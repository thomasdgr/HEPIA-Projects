#include "common.h"

// This fonction takes a string as input and convert it to a 
// uint16_t. It stops the program with an error message if the
// string does not correspond to an integer fitting an uint16_t
uint16_t string_to_port(const char *str) {
    // Convert input in port number
    errno = 0;
    long int port = strtol(str, NULL, 10); // string to long int
    if (errno != 0)
        die("port value");

    // Check long int fit in uint16 (as it is the returned value)
    if (port > UINT16_MAX) {
        errno = ERANGE;
        die("port value");
    }

    // If port == 0 either no valid numerical value was found or 0 was found
    // none is a valid port
    if (port == 0) {
        fprintf(stderr, "%s is not a valid port\n", str);
        exit(1);
    }

    return port;
}

// This function reads on the file descriptor the total quantity of data
// it quits the program and display an error if the read is not successfull
// see man read for more information
// WARNING: this function does not handle EOF and
// will block as long as the expected quantity of data is available

void read_full(int fd, void* buff, size_t count) { // lire les données du socket
    ssize_t nb_read;    
    do {
         nb_read = read(fd, buff, count); // nb_read -> descripteur de fichier du socket
         if ( nb_read == -1)
            die("socket read");
        count -= nb_read;
        buff +=  nb_read;
    } while(count > 0);
}

// This function write on the file descriptor the total quantity of data
// it quits the program and display an error if the read is not successfull
// see man write for more information
void write_full(int fd, const void* buff, size_t count) { // écrire sur le socket
    ssize_t nb_write;    
    do {
         nb_write = write(fd, buff, count);
         if ( nb_write == -1)
            die("socket read");
        count -= nb_write;
        buff +=  nb_write;
    } while(count > 0);
}