/*
 * File: multi-lookup.c
 * Author: Taylor Andrews
 * Project: CSCI 3753 Programming Assignment 3
 * Create Date: 03/01/15
 * Description:
 * 	This file contains the multi-threaded
 *      solution to the assignment.
 *  
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h> 

#include "multi-lookup.h"
#include "util.h"
#include "queue.h"

queue buf;

pthread_mutex_t buf_lock;
pthread_mutex_t file_lock;
pthread_mutex_t requester_lock;

int current_requesters;

int main(int argc, char* argv[]){

    /* Check Arguments */
    if (argc < MINARGS) {
	fprintf(stderr, "Not enough arguments: %d\n", (argc - 1));
	fprintf(stderr, "Usage:\n %s %s\n", argv[0], USAGE);
	return EXIT_FAILURE;
    }

    /* Local Vars */
    FILE* outputfp = NULL;

    int i;
    int rc; 
    int num_requesters = argc - 2; //Total number of inputs minus 2 (for executable and output)
    int num_resolvers = sysconf(_SC_NPROCESSORS_ONLN);
    
    current_requesters = num_requesters;

    /* Check Number of Resolvers */
    if (num_resolvers < MIN_RESOLVER_THREADS) {
        num_resolvers = MIN_RESOLVER_THREADS;
	}

    /* Create Arrays for pthreads */
    pthread_t requesters[num_requesters];
    pthread_t resolvers[num_resolvers];

    /* Open Output File */
    outputfp = fopen(argv[(argc-1)], "w");
    if (!outputfp) {
        fprintf(stderr, "Error opening output file \n");
	return EXIT_FAILURE;
    }

    /* Create the Queue */
    if (queue_init(&buf, BUF_SIZE) == QUEUE_FAILURE) {
        fprintf(stderr, "Initializing queue failed \n");
	return EXIT_FAILURE;
    }

    /* Create Mutex */
    if (pthread_mutex_init(&buf_lock, NULL)) {
        fprintf(stderr, "Creating buf mutex failed \n");
	return EXIT_FAILURE;
    }

    if (pthread_mutex_init(&file_lock, NULL)) {
        fprintf(stderr, "Creating file mutex failed \n");
	return EXIT_FAILURE;
    }

    if (pthread_mutex_init(&requester_lock, NULL)) {
        fprintf(stderr, "Creating requester mutex failed \n");
	return EXIT_FAILURE;
    }

    /* Spawn Requeters */
    for (i = 0; i < num_requesters; i++) {
      rc = pthread_create(&requesters[i], NULL, requester, argv[i+1]);
	if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
	    exit(EXIT_FAILURE);
	}
    }

    /* Spawn Resolvers */
    for (i = 0; i < num_resolvers; i++) {
      rc = pthread_create(&resolvers[i], NULL, resolver, (void*)outputfp);
	if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
	    exit(EXIT_FAILURE);
	}
    }

    /* Wait for Threads */
    for (i = 0; i < num_requesters; i++) {
        pthread_join(requesters[i], NULL);
    }
    
    for (i = 0; i < num_resolvers; i++) {
        pthread_join(resolvers[i], NULL);
    }

    /* Close Output File */
    if (fclose(outputfp)) {
        fprintf(stderr, "Error closing output file \n");
    }

    /* Cleanup Queue */
    queue_cleanup(&buf);

    /* Cleanup Mutex */
    if (pthread_mutex_destroy(&buf_lock)) {
        fprintf(stderr, "Destroying buf mutex failed \n");
    } 

    if (pthread_mutex_destroy(&file_lock)) {
        fprintf(stderr, "Destroying file mutex failed \n");
    }
    
    if (pthread_mutex_destroy(&requester_lock)) {
        fprintf(stderr, "Destroying requester mutex failed \n");
    }

    return EXIT_SUCCESS;
}

void* requester(void* input) {
    FILE* inputfp;

    char* payload;
    char hostname[SBUFSIZE];

    /* Open File */
    inputfp = fopen((char*)input, "r");

    if (!inputfp) {
        fprintf(stderr, "Error opening input file \n");

	pthread_mutex_lock(&requester_lock);
	current_requesters--;
	pthread_mutex_unlock(&requester_lock);

	return NULL;
    }   

    while (fscanf(inputfp, INPUTFS, hostname) > 0) {
        pthread_mutex_lock(&buf_lock);
	while (queue_is_full(&buf)) {
  	    pthread_mutex_unlock(&buf_lock);
	    if(usleep(rand() % 100)) {
	        fprintf(stderr, "Error sleeping thread \n");
	    }
	    pthread_mutex_lock(&buf_lock);
	}
	
	if (!queue_is_full(&buf)) {
	    payload = malloc(sizeof(hostname));
	    strcpy(payload, hostname);
	    
	    if (queue_push(&buf, (void*) payload) == QUEUE_FAILURE) {
	        fprintf(stderr, "Queue push failed \n");
	    }
	}
	else {
	    fprintf(stderr, "Error accessing thread \n");
	}

	pthread_mutex_unlock(&buf_lock);
    }

    /* Close file */;
    if (fclose(inputfp)) {
        fprintf(stderr, "Error closing input file \n");
    }

    pthread_mutex_lock(&requester_lock);
    current_requesters--;
    pthread_mutex_unlock(&requester_lock);

    return NULL;
}

void* resolver(void* output) {
    FILE* outputfp = output;

    char* hostname;

    node_t* headptr;
    node_t* temp;

    pthread_mutex_lock(&buf_lock);
    while (current_requesters || !queue_is_empty(&buf)) {
        if ((hostname = (char*)queue_pop(&buf)) == NULL) {
	    fprintf(stderr, "Queue pop failed \n");
        }
	pthread_mutex_unlock(&buf_lock);

	headptr = malloc(sizeof(node_t));
	headptr->next = NULL;

	if (extended_dnslookup(hostname, headptr, INET6_ADDRSTRLEN) == UTIL_FAILURE) {
		fprintf(stderr, "dnslookup error: %s\n", hostname);
	}

	pthread_mutex_lock(&file_lock);
	fprintf(outputfp, "%s", hostname);

	/* Handle Printing Edge Cases */
	if (headptr->next == NULL) {
	    fprintf(outputfp, ",");
	}
	else {
	    int j = 0;
	    while (headptr->next != NULL) {
	        if (j % 3 == 0)
	            fprintf(outputfp, ",%s", headptr->data);
		j++;
		temp = headptr; 
		headptr = headptr->next;
		free(temp); //Free the allocated memory
	    }
	}
	fprintf(outputfp, "\n");
	pthread_mutex_unlock(&file_lock);

	/* Cleanup Allocated Memory */
	free(headptr);
	free(hostname);

	pthread_mutex_lock(&buf_lock);
    }
    pthread_mutex_unlock(&buf_lock);

    return NULL;
}
