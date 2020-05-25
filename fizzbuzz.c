/* ---------------------------------------------------------------------------- */ 
/* NAME : Brendan Beecham							*/	
/* FILE : fizzbuzz.c								*/
/* PROGRAM PURPOSE :								*/
/* 	The program accepts user input as integers through the command line.	*/
/* 	Then the program will print out "Fizz" if the sum of the inputs is a	*/
/* 	multiple of 3. Additionally, the program will print out "Buzz" if the	*/
/* 	sum of the inputs is a multiple of 2. This will continue until the	*/
/* 	program is terminated.							*/
/* TO RUN :									*/
/* 	'./fizzbuzz <integer>'							*/
/* ____________________________________________________________________________ */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

void multipleOf2(int sum) {
	if(sum % 2 != 0) { return; }
	
	char *buf = "Fizz\n";
	write(1, buf, strlen(buf));
}

void multipleOf3(int sum) {
	if(sum % 3 != 0) { return; }

	char *buf = "Buzz\n";
	write(1, buf, strlen(buf));
}

int main(int argc, char **argv) {

	write(1, "Starting FizzBuzz with an input timeout of 5 seconds!\n", 54);
	char temp[10];	
	int input, multipleOf;
	int sum = 0;
	char *buf = "Enter a new integer: ";

	fd_set rfds;
	struct timeval tv;
	int retval, maxfd;

	while(1) {
		memset(&temp, 0, sizeof(temp));		//clear char input buffer

		FD_ZERO(&rfds);
		FD_SET(0, &rfds);		//add stdin to set

		tv.tv_sec = 5;		//timeout of 5 seconds
		tv.tv_usec = 0;		//zeroes out millisecond timeout value

		write(1, buf, strlen(buf));
		retval = select(1, &rfds, NULL, NULL, &tv);	//select waits for input from stdin
		if( retval == -1 ) {
			perror("select()");
			exit(-1);
		}

		if( FD_ISSET(0, &rfds) ) {

			read(0, temp, 10);
			if( strcmp( temp, "exit\n") == 0 ) { 	//check for the exit protocol
				write(1, "...exiting\n\n", 12);
				exit(0); 
			}

			input = atoi(temp);

			sum += input;		//add new input int to existing sum
		
			multipleOf2(sum);	//calls functions to check sum against multiples of 2 and 3
			multipleOf3(sum);
		
			sum = 0;	//reset sum for consecutive rounds
			sleep(1);

		} else {
			write(1, "\nGame timed out\n\n", 17);
			exit(0);
		}
	}
}
