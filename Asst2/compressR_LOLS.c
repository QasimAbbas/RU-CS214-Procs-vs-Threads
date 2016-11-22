//compressR_LOLS.c
//compressR_LOLS(<file to compress>, <number of parts>)
//uses processes to split compression of file into a specific number of parts
#include "rle.c"
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>

char * fileName;
//struct for holding arguments for compressToFile

int main(int argc, char *argv[]){
	
	int childCount;	//number of threads specified
		//specified file name

	FILE * file;		//file with uncompressed input

	int docLength;		//character length of file

	char * input;		//uncompressed string

	int segSize;		//size of uncompressed string segments
	//get comand line args
	if (argc == 3){
		fileName = argv[1];
		childCount = atoi(argv[2]);
	}else{
		printf("ERROR not enough arguments\n");
		return 0;
	}

	/*get uncompressed string from file*/
	file = fopen(fileName, "r");

	docLength = get_file_length(file);

	input = (char*)malloc(docLength);

	fgets(input, docLength + 1, file);

	fclose(file);

	printf("Input : %s\n", input);

	//
	
	int place = 0; 					//used to save index where process leaves off/starts again
	int i;
	
	//Creating child process
	for(i = 0; i < childCount; i++){
		pid_t child_pid = fork();
		
		segSize = floor(docLength/childCount);
		
		//Configuring Arguments for Child Processes
	    char *argPassing[5];
		printf("INPUT %s\n", input);
		argPassing[0] = input;
		char *str1 = malloc(sizeof(char*));
		char *str2 = malloc(sizeof(char*));
		char *str3 = malloc(sizeof(char*));
		
		sprintf(str1, "%d", segSize);
		argPassing[1] = str1;
		sprintf(str2, "%d", place);
		argPassing[2] = str2;
		sprintf(str3, "%d", i);
		argPassing[3] = str3;
	
		argPassing[4] = fileName;
		
		
		//Initializing the Child Processes to work on Compress_R_Worker_LOLS
		printf("PASSING TO THE WORKER\n");
		if(child_pid != 0){
			
		}else{
			execvp("./compressR_worker_LOLS", argPassing);
			exit(0);
		}
		
		free(str1);
		free(str2);
		free(str3);
		place += segSize;
	}

    
	printf("Waiting on process\n");
	/* Wait for children to exit. */
	int child_status;
	pid_t pid;
	int c = childCount;
	while (c > 0) {
	  pid = wait(&child_status);
	  printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, child_status);
	  --c;  // TODO(pts): Remove pid from the pids array.
	}

	printf("process done\n");
	return 0;

}

int get_file_length( FILE *file ) {
    fpos_t position; 
    int length; 

    fgetpos( file, &position ); // save previous position in file

    if ( fseek( file, 0, SEEK_END ) // seek to end
        || ( length = ftell( file ) ) == -1 ) { // determine offset of end
        perror( "Finding file length" ); // handle overflow
    }

    fsetpos( file, &position ); // restore position

    return length;
}








