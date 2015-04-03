#ifndef MULTILOOKUP_H
#define MULTILOOKUP_H

#define MINARGS 3
#define USAGE "<inputFilePath> ... <inputFilePath> <outputFilePath>"
#define SBUFSIZE 1025
#define INPUTFS "%1024s"

#define BUF_SIZE 10

#define MIN_RESOLVER_THREADS 2 //Required lower limit

/*
#define MAX_INPUT_FILES 10
#define MAX_RESOLVER_THREADS 10
#define MAX_NAME_LENGTH 1025
#define MAX_IP_LENGTH INET6_ADDRSTRLEN
*/

void* requester(void* input);

void* resolver(void* output);

#endif
