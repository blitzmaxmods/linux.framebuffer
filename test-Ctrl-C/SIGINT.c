#include <brl.mod/blitz.mod/blitz.h>

#include<stdio.h>
#include <signal.h>
#include <sys/uio.h>
#include <unistd.h>

typedef void (*sighandler_t)(int);

//signal_handler() {
//	print "SIGINT received"
//	os.exit(0)
//}

//os.set_signal os.SIGNAL_INT, signal_handler();
//print "Press Ctrl-C to exit

void sigint_default( int signal ) {
	if(signal==SIGINT)
		printf( "Default SIGINT\n" );
}

//sighandler_t os_sigint( int signal, sighandler_t handler ) {
//	return( sigaction( SIGINT, handler ) );
//}

//os_sigint( SIGINT, sigint_default );

sighandler_t setsig( sighandler_t handler ) {
//	return signal( SIGINT, sigint_default );
	return signal( SIGINT, handler );
}

