/*  /
   / SIGINT handler for Blitzmax
  /  (c) Copyright Si Dunford [Scaremonger], April 2025
*/

#include <brl.mod/blitz.mod/blitz.h>

#include<stdio.h>
#include <signal.h>
#include <sys/uio.h>
#include <unistd.h>

typedef void (*sighandler_t)(int);

void sigint_default( int signal ) {
	if(signal==SIGINT)
		printf( "Default SIGINT\n" );
}

sighandler_t setsignal( sighandler_t handler ) {
	return signal( SIGINT, handler );
}

