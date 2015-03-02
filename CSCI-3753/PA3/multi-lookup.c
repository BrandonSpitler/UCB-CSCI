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

#include "multi-lookup.h"
#include "util.h"

int main(int argc, char* argv[]){

    /* Local Vars */
    FILE* inputfp = NULL;
    FILE* outputfp = NULL;
    char hostname[SBUFSIZE];
    char errorstr[SBUFSIZE];
    char firstipstr[INET6_ADDRSTRLEN];
    int i;
    
    /* Check Arguments */
    if(argc < MINARGS){
	fprintf(stderr, "Not enough arguments: %d\n", (argc - 1));
	fprintf(stderr, "Usage:\n %s %s\n", argv[0], USAGE);
	return EXIT_FAILURE;
    }

    /* Open Output File */
    outputfp = fopen(argv[(argc-1)], "w");
    if(!outputfp){
	perror("Error Opening Output File");
	return EXIT_FAILURE;
    }

    /* Loop Through Input Files */
    for(i=1; i<(argc-1); i++){
	
	/* Open Input File */
	inputfp = fopen(argv[i], "r");
	if(!inputfp){
	    sprintf(errorstr, "Error Opening Input File: %s", argv[i]);
	    perror(errorstr);
	    break;
	}	

	/* Read File and Process*/
	while(fscanf(inputfp, INPUTFS, hostname) > 0){
	
	    /* Lookup hostname and get IP string */
	    if(dnslookup(hostname, firstipstr, sizeof(firstipstr))
	       == UTIL_FAILURE){
		fprintf(stderr, "dnslookup error: %s\n", hostname);
		strncpy(firstipstr, "", sizeof(firstipstr));
	    }
	
	    /* Write to Output File */
	    fprintf(outputfp, "%s,%s\n", hostname, firstipstr);
	}

	/* Close Input File */
	fclose(inputfp);
    }

    /* Close Output File */
    fclose(outputfp);

    return EXIT_SUCCESS;
}
