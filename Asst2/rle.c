//rle.c
//Run Length Encoding function to be used in compression files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct CharTag
{
	char ch;

	int amount;

	int digits;

	void * next;

} CharTag;

char* encode (char* input){
	//size of the outputted string based on the input
	int outputSize = 0;

	//size of Linked List
	int llSize = 0;

	//head of linked list
	CharTag* head = (CharTag*)malloc(sizeof(CharTag));

	//create an LL of the unique chars and their frequencys
	CharTag * tmp = head;
	int charCount = 0;
	int i = 0;
	while(i < strlen(input)){

		if(input[i] == input[i + 1]){
			charCount ++;
		}else{
			charCount++;
			
			//printf("%c : %d\n",  input[i], charCount);
			int numberOfDigits = floor(log10(abs(charCount))) + 2;
			outputSize += numberOfDigits;
			//printf("%d\n", numberOfDigits);
			//fill the LL
			tmp -> ch = input[i];
			tmp -> amount = charCount;
			tmp -> digits = numberOfDigits;
			tmp -> next = (CharTag*)malloc(sizeof(CharTag));
			tmp = tmp -> next;
			llSize ++;		
			charCount = 0;
		}
		i++;
	}
	//last node has a zero amount to denot end of list
	//tmp -> amount = 0;

	//Take data from the LL and write it to an ouput string
	char* output = (char *)malloc(outputSize);
	tmp = head;
	int z = 0;
	
	while(tmp -> amount != 0){
		//add char
		//output[z] = tmp -> ch;

		if(tmp -> amount  > 2){ 
			//add numbers
			char numbers[tmp -> digits];
			sprintf(numbers, "%d", tmp -> amount);


			strcat (output , numbers);

			//printf("before letter %s\n", output);

			z += strlen(numbers);

			char letter[2];

			letter[0] = tmp -> ch;
			letter[1] = '\0';

			strcat (output , letter);

			//output[z] = tmp -> ch;

			//printf("after: %s\n", output);

			//z++;

			tmp = tmp -> next;
		}else if(tmp -> amount  == 2){
			//add 2 letters

			char letter[3];

			letter[0] = tmp -> ch;
			letter[1] = tmp -> ch;
			letter[2] = '\0';
			
			strcat (output , letter);

			tmp = tmp -> next;
		}else if(tmp -> amount  == 1){
			//add 1 letter

			
			char letter[2];

			letter[0] = tmp -> ch;
			letter[1] = '\0';

			strcat (output , letter);

			tmp = tmp -> next;
		}

	}	

	return output;

}

char * filenameFormat(char *nameOfFile, char *type){
	char string[250];
	strcpy(string, nameOfFile);
	int i;
	for(i = 0; i < strlen(nameOfFile); i++){
		if(string[i] == '.'){
			string[i] = '_';
		}
	}
	
	char *ptr = string;
	return ptr;
}






