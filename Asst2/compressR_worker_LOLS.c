#include <math.h>
#include "rle.c"
#include <stdlib.h>
#include <unistd.h>

typedef struct args
{
	char * input;
	int segSize;
	int place;
	int iteration;	
} args;

char *fileName;
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
	
	//fprintf(file, "%s", encoded);

	fclose(file);

	free(newFileName);
	free(number);
	return;
}

int main(int argc, char *argv[]){
	
    printf("INSIDE THE WORKER\n");
    
    
    args *valIntoStruct = (args *)malloc(sizeof(args));
    
    valIntoStruct->input = argv[0];
	    printf("WORKER INPUT %s\n", valIntoStruct->input);
    valIntoStruct->segSize = atoi(argv[1]);
	    printf("WORKER SEGSIZE %i\n", valIntoStruct->segSize);
    valIntoStruct->place = atoi(argv[2]);
	    printf("WORKER PlACE %i\n", valIntoStruct->place);
    valIntoStruct->iteration = atoi(argv[3]);
		printf("WORKER ITERATION %i\n", valIntoStruct->iteration);
	
	fileName = argv[4];
	printf("FILE NAME %s\n", fileName);
	
	if(fileName != NULL){
		
    	compressToFile(valIntoStruct);
	}
	
	free(valIntoStruct);
	
    return 0;   
    
}