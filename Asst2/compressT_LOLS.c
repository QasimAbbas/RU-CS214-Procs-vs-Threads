//compressT_LOLS.c
//compressT_LOLS(<file to compress>, <number of parts>)
//uses threads to split compression of file into a specific number of parts
#include "rle.c"
#include <stdlib.h>
#include <pthread.h>
#include <math.h>


char * fileName;

//struct for holding arguments for compressToFile
typedef struct args
{
	char * input;
	int segSize;
	int place;
	int iteration;	
} args;

//uses rle encoding on input string, then writes the code to a new file
void compressToFile(void* arguments){
	//retrieve and encode input

	args* in = (args *) arguments;
	
	char* segment = (char*)malloc(in->segSize + 1);

	strncpy(segment, in->input + in->place, in->segSize);

	printf("Segment: %s\n", segment);

	char * encoded = encode(segment);

	printf("Encoded: %s\n", encoded);

	//now write encoded to file
	//contruct the new file's name
	int fileNameSize = sizeof(fileName) + 3;
	
	char * number = (char*)malloc(3);
	char * newFileName = (char*)(malloc(fileNameSize));
	
	strcpy(newFileName, fileName); 
	sprintf(number, "%d", in->iteration + 1);
	strcat(newFileName, "_LOLS");
	strcat(newFileName, number);
	char *formatName = filenameFormat(newFileName, NULL);
	strcpy(newFileName, formatName);
	printf("File name: %s\n", newFileName);

	//create a new file with the name
	FILE *file;
	file = fopen(newFileName, "w+");
	printf("File opened\n");
	fprintf(file, encoded);

	fclose(file);

	free(newFileName);
	free(number);
	return;
}

int main(int argc, char *argv[]){
	
	int threadCount;	//number of threads specified

		//specified file name

	FILE * file;		//file with uncompressed input

	int docLength;		//character length of file

	char * input;		//uncompressed string

	int segSize;		//size of uncompressed string segments
	//get comand line args
	if (argc == 3){
		fileName = argv[1];
		threadCount = atoi(argv[2]);
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

	/*create threads*/
	pthread_t pth[threadCount];		//array of thread pointers
	int place = 0; 					//used to save index where process leaves off/starts again
	int i;
	for(i = 0; i < threadCount; i++){
		segSize = floor(docLength/threadCount);

		args* arguments =  (args*)malloc(sizeof(args));

		arguments->input = input;
		arguments->segSize = segSize;
		arguments->place = place;
		arguments->iteration = i;

		//make thread
		pthread_create(&pth[i], NULL, compressToFile,arguments);

		place += segSize;
	}

	//wait for threads to finish
    
	printf("Waiting on process\n");

	for(i = 0; i < threadCount; i++){
		pthread_join(pth[i],NULL);
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








