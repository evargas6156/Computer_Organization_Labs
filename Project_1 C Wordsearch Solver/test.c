#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//a function that finds if a string is a substring of another and returns index 
//at which it is found, if not found returns -1
int subStringFinder(char* substring, char* string){
	//find lengths of both strings 
	int subLen = strlen(substring);
	int strLen = strlen(string);
	int i, j;
	//iterate through string and look for the substring
	for(i = 0; i <= (strLen - subLen); i++){
		//look for the substring starting at each index of the string 
		for(j = 0; j < subLen; j++){
			//if the current index doesnt match current substring index, break loop
			if( *(string + i + j) != *(substring + j) ){
				break;
			}
		}
		//if j eventually reaches the end of the substring then it is actually a substring
		//so return its index i at which it is found
		if(j == subLen){
				return i;
		}
		
	}
	//after both loops it isnt found, return -1 
	return -1;
}

void upperCase(char* string){
	int length = strlen(string);
	for(int i = 0; i < length; i++){
		if((*(string + i) >= 97) && (*(string + i) <= 122)){
			*(string + i) = (char)(*(string + i) - 32);
		}
	}
	
}

void reverseString(char* string){
	int length = strlen(string);
	char temp; 
	for(int i = 0; i < ((length)/2); i++){
		temp = *(string + i);
		*(string + i) = *(string + length - i - 1);
		*(string + length - i - 1) = temp;
	}
}




int main(int argc, char **argv) {
	
	//char* string = (char*)malloc(20 * sizeof(char));
	char string[] = "ruuvgeorgiaqvda"; //(char*)malloc(20 * sizeof(char))
	//char* substring = (char*)malloc(20 * sizeof(char));
	char substring[] = "georgia";
	int found = subStringFinder(substring, string);
	
	if(found == -1){
		printf("Not a substring\n");
	}else{
		printf("Is a substring, first found at index: %d\n", found);
	}
	printf("%s\n",substring);
	
	reverseString(substring);
	//*(substring + 3) = 'A';
	printf("%s\n",substring);
	upperCase(substring);
	printf("%s\n",substring);
	
	
	
	return 0;
}