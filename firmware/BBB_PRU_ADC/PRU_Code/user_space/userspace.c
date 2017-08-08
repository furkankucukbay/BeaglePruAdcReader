// 
// Source Modified by Furkan Küçükbay
// Based on the example provided by Gregory Raven at
// 	https://github.com/Greg-R/pruadc1/user_space
//



#include <fcntl.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv) {
	int  pru_data, pru_activate; // file descriptors
	int bufferSize = 10;
	int bufferByteSize = bufferSize * 4;  //32 bit is 4 bytes.
  	int32_t sinebuf[bufferSize];
	int32_t result = 0;

	time_t start_t, end_t;
	float diff_t = 0.0;
	
	for(int i = 0; i < bufferSize; i = i + 1){
		sinebuf[i] = 0;
	}

	//FILE * fpointer;
	//fpointer = fopen( "data.txt", "w");	


    	//  Now, open the PRU character device.
    	//  Read data from it in chunks and write to the named pipe.
    	ssize_t readpru, prime_char, pru_activate_command;
    
    	//  Open the character device to PRU0.
    	pru_data = open("/dev/rpmsg_pru30", O_RDWR);
    	if (pru_data < 0)
      		printf("Failed to open pru character device rpmsg_pru30.");
    	
	//  The character device must be "primed".
    	prime_char = write(pru_data, "prime", 6);
    	if (prime_char < 0)
      		printf("Failed to prime the PRU0 char device.");

    	//  Now open the PRU1 clock control char device and start the clock.
    	pru_activate = open("/dev/rpmsg_pru31", O_RDWR);
    	pru_activate_command = write(pru_activate, "s", 2);
    	if (pru_activate_command < 0)
      		printf("The pru activate command failed.");

    	//  This is the main data transfer loop.
    	//  Note that the number of transfers is finite.
    	//  This can be changed to a while(1) to run forever.
    	for (int i = 0; i < 100000000; i++) {
		time(&start_t);
		
      		readpru = read(pru_data, sinebuf, bufferByteSize);

		for(int j = 0; j < bufferSize; j = j + 1){

			//if( sinebuf[j] < 52800){
			//	sinebuf[j] = 52800;
			// }

			//result = result + ( (sinebuf[j] - 52800)/920 );

			result =  sinebuf[j];   //- 52800 )/920 ;
			
			printf("%d", result);
			printf("\n");
			result = 0;
			
			//fprintf( fpointer, "%d", sinebuf[j]);
			//fprintf( fpointer, "\n");
		}
		//fprintf( fpointer, "------------------------\n");
		printf( "-----------------\n");
		
		time(&end_t);
		diff_t = (float)( difftime(end_t, start_t) );
		//fprintf( fpointer, "%f", diff_t);
		//fprintf( fpointer, "\n");
		printf( "%f", diff_t);
		printf( " seconds \n\n");	
    	}

    	//fclose(fpointer);;
}
