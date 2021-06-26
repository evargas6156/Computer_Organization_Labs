#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// DO NOT INCLUDE OTHER LIBRARY!

// Declarations of the two functions you will implement
// Feel free to declare any helper functions
void printPuzzle(char** arr, int n);
void searchPuzzle(char** arr, int n, char** list, int listSize);
int subStringFinder(char* substring, char* string);
void upperCase(char* string);
void searchHorizontally(char*** arr, int n, char** list, int listSize);
void reverseString(char* string);
void lowerCaseGrid(char*** arr, int row, int column);
void searchVertically(char** colArr, int n, char** list, int listSize, char*** arr);
void searchDiagonallyLeftToRight(char** diagArr, int diagn, char** list, int listSize, char*** arr, int n);
void searchDiagonallyRightToLeft(char** diagArr, int diagn, char** list, int listSize, char*** arr, int n);

// Main function, DO NOT MODIFY!!!	
int main(int argc, char **argv) {
    int bSize = 15;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
		return 2;
	}
    int i, j;
    FILE *fptr;
    char **block = (char**)malloc(bSize * sizeof(char*));
	char **words = (char**)malloc(50 * sizeof(char*));

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

	// Read puzzle block into 2D arrays
    for(i=0; i<bSize; i++){
        *(block+i) = (char*)malloc(bSize * sizeof(char));

        fscanf(fptr, "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n", *(block+i), *(block+i)+1, *(block+i)+2, *(block+i)+3, *(block+i)+4, *(block+i)+5, *(block+i)+6, *(block+i)+7, *(block+i)+8, *(block+i)+9, *(block+i)+10, *(block+i)+11, *(block+i)+12, *(block+i)+13, *(block+i)+14 );
    }
	fclose(fptr);

	// Open file for reading word list
	fptr = fopen("states.txt", "r");
	if (fptr == NULL) {
        printf("Cannot Open Words File!\n");
        return 0;
    }
	
	// Save words into arrays
	for(i=0; i<50; i++){
		*(words+i) = (char*)malloc(20 * sizeof(char));
		fgets(*(words+i), 20, fptr);		
	}
	
	// Remove newline characters from each word (except for the last word)
	for(i=0; i<49; i++){
		*(*(words+i) + strlen(*(words+i))-2) = '\0';	
	}
	
	// Print out word list
	printf("Printing list of words:\n");
	for(i=0; i<50; i++){
		printf("%s\n", *(words + i));		
	}
	printf("\n");
	
	// Print out original puzzle grid
    printf("Printing puzzle before search:\n");
    printPuzzle(block, bSize);
	printf("\n");

	// Call searchPuzzle to find all words in the puzzle
	searchPuzzle(block, bSize, words, 50);
	printf("\n");
	
	// Print out final puzzle grid with found words in lower case
    printf("Printing puzzle after search:\n");
    printPuzzle(block, bSize);
	printf("\n");
	
    return 0;
}

void printPuzzle(char** arr, int n){
	// This function will print out the complete puzzle grid (arr). It must produce the output in the SAME format as the samples in the instructions.
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%c ", *(*(arr + i) + j));
		}
		printf("\n");
	}


}

void searchPuzzle(char** arr, int n, char** list, int listSize){
	// This function checks if arr contains words from list. If a word appears in arr, it will print out that word and then convert that word entry in arr into lower case.
	// Your implementation here
	
	
	
	char **columnBlock = (char**)malloc(n * sizeof(char*));
	int numDiagRows = (2*n) - 1;
	char **diagonalBlock = (char**)malloc(numDiagRows * sizeof(char*));
	char **diagonalBlockTwo = (char**)malloc(numDiagRows * sizeof(char*));
	int k;
	
	//create the vertical string block
	for(int i = 0; i < n; i++){
		*(columnBlock + i) = (char*)malloc(n * sizeof(char));
		for(int j = 0; j < n; j++){
			*(*(columnBlock + i) + j) = *(*(arr + j) + i);
		}
	}
	
	int currLength = 1;
	int currCol = 1;
	int currRow = n;
	int col, row;
	
	//create the diagonal right to left and left to right string blocks
	for(int i = 1; i <= numDiagRows; i++){
		*(diagonalBlock + i - 1) = (char*)malloc(currLength * sizeof(char));
		*(diagonalBlockTwo + i - 1) = (char*)malloc(currLength * sizeof(char));
		if(i < n){
			row = currRow;
			for(int j = 0; j < currLength; j++){
				*(*(diagonalBlock + (i - 1)) + j) = *(*(arr + (row - 1)) + j);
				*(*(diagonalBlockTwo + (i - 1)) + j) = *(*(arr + (row - 1)) + (n - j - 1));
				row++;
			}
			//printf("CurrRow: %d\n", currRow);
			currRow--;
			//printf("Currlength: %d\n\n", currLength);
			currLength++;
			
		}else{
			col = currCol;
			for(int j = 0; j < currLength; j++){
				*(*(diagonalBlock + (i - 1)) + j) = *(*(arr + j) + (col - 1));
				*(*(diagonalBlockTwo + (i - 1)) + j) = *(*(arr + j) + (n - col));//rtgtrtrgtrgtr
				col++;
			}
			//printf("CurrCol: %d\n", currCol);
			currCol++;
			//printf("Currlength: %d\n\n", currLength);
			currLength--;
		}
	}
	
	
	
	
	searchVertically(columnBlock, n, list, listSize, &(arr));
	
	searchHorizontally(&(arr), n, list, listSize);
	
	searchDiagonallyLeftToRight(diagonalBlock, numDiagRows, list, listSize, &(arr), n);
	
	searchDiagonallyRightToLeft(diagonalBlockTwo, numDiagRows ,list ,listSize, &(arr), n);
	
	
}


void searchHorizontally(char*** arr, int n, char** list, int listSize){
	int currentFound;
	int currentFoundReverse;
	char * currString = (char*)malloc(20 * sizeof(char));
	char * currStringReverse = (char*)malloc(20 * sizeof(char));
	char * currRow = (char*)malloc(20 * sizeof(char));
	for(int i = 0; i < listSize; i++){
		//add current list item to the current string variable 
		strcpy(currString,  *(list + i));
		upperCase(currString);
		
		for(int j = 0; j < n; j++){
			//add current grid row to curr row variable 
			strcpy(currRow, *((*arr) + j));
			upperCase(currRow);
			
			//search for the string in that row 
			currentFound = subStringFinder(currString, currRow);
			
			//reverse the word and search to fins words from right to left
			strcpy(currStringReverse, currString);
			reverseString(currStringReverse);
			currentFoundReverse = subStringFinder(currStringReverse, currRow);
			
			//if found print out the word and change its char's on grind to lowerrcase 
			if(currentFound >= 0 || currentFoundReverse >= 0){
				printf("Word found: %s\n", *(list + i));
				for(int k = 0; k < strlen(currString); k++){
					if(currentFound >= 0){
						lowerCaseGrid(arr, j, (k + currentFound));             
					}else if (currentFoundReverse >= 0){
						lowerCaseGrid(arr, j, (k + currentFoundReverse));       
					}
				}
				
				//break;
			}
		}
		
	}
}



void searchVertically(char** colArr, int n, char** list, int listSize, char*** arr){
	int currentFound;
	char* currString = (char*)malloc(20 * sizeof(char));
	char* currCol = (char*)malloc(20 * sizeof(char));
	for(int i = 0; i < listSize; i++){
		//copy current list item to currstring variable 
		strcpy(currString, *(list + i));
		upperCase(currString);
		
		for(int j = 0; j < n; j++){
			//copy current column string into currcol var 
			strcpy(currCol, *(colArr + j));
			upperCase(currCol);
			
			//search for currstring in currcol
			currentFound = subStringFinder(currString, currCol);
			
			//if found print word and change grid chars to lowercase
			if(currentFound >= 0){
				printf("Word found: %s\n", *(list + i));
				for(int k = 0; k < strlen(currString); k++){
					if(currentFound >= 0){
						lowerCaseGrid(arr,(k + currentFound) , j);
					}
					
				}
				//break;
			}
		}
		
	}
	
}

void searchDiagonallyLeftToRight(char** diagArr, int diagn, char** list, int listSize, char*** arr, int n){
	int currentFound;
	char* currString = (char*)malloc(20 * sizeof(char));
	char* currDiag = (char*)malloc(20 * sizeof(char));
	for(int i = 0; i < listSize; i++){
		//copy current list item into currstring
		strcpy(currString, *(list + i));
		upperCase(currString);
		
		//varibles to keep track of grid posotion 
		int currCol = 1;
		int currRow = n;
		int col, row;
		for(int j = 1; j <= diagn; j++){
			if(j < n){
				//if less than halfway point save current row
				row = currRow;
				currRow--;
			}else{
				//after halfway point save current column
				col = currCol;
				currCol++;
			}
			//copy the current diagonal string into currDiag
			strcpy(currDiag, *(diagArr + j - 1));
			upperCase(currDiag);
			
			//search for the current string in the current diagonal string
			currentFound = subStringFinder(currString, currDiag);
			
			//if its found print the word out and set grid char's to lowercase
			if(currentFound >= 0){
				printf("Word found: %s\n", *(list + i));
				for(int k = 0; k < strlen(currString); k++){
					if(j < n){
						lowerCaseGrid(arr,(currentFound + row - 1 + k)  , (currentFound + k));
					}else{
						lowerCaseGrid(arr, (currentFound + k), (currentFound + col - 1 + k));
					}
					
				}
				//break;
			}
		}
		
	}
	
}

void searchDiagonallyRightToLeft(char** diagArr, int diagn, char** list, int listSize, char*** arr, int n){
	int currentFound;
	char* currString = (char*)malloc(20 * sizeof(char));
	char* currDiag = (char*)malloc(20 * sizeof(char));
	for(int i = 0; i < listSize; i++){
		//copy current list item into currstring
		strcpy(currString, *(list + i));
		upperCase(currString);
		
		//variables to keep track of current grid position 
		int currCol = n;
		int currRow = n;
		int col, row;
		for(int j = 1; j <= diagn; j++){
			if(j < n){
				//if less than halfway point save current row 
				row = currRow;
				currRow--;
			}else{
				//if after halfway point save current column
				col = currCol;
				currCol--;
			}
			//copy the current diagonal string into currdiag
			strcpy(currDiag, *(diagArr + j - 1));
			upperCase(currDiag);
			
			//search for the current string in the current diagonal string 
			currentFound = subStringFinder(currString, currDiag);
			
			//if its found print the word and change its grid char's to lowercase 
			if(currentFound >= 0){
				printf("Word found: %s\n", *(list + i));
				for(int k = 0; k < strlen(currString); k++){
					if(j < n){
						lowerCaseGrid(arr,(row + currentFound - 1 + k)  , (n - currentFound - 1 - k));
					}else{
						lowerCaseGrid(arr, (currentFound + k), (currCol - currentFound - k));
					}
					
				}
				//break;
			}
		}
		
	}
	
}


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

//a fucntion to turn a string to uppercase 
void upperCase(char* string){
	int length = strlen(string);
	for(int i = 0; i < length; i++){
		if((*(string + i) >= 97) && (*(string + i) <= 122)){
			*(string + i) = (char)(*(string + i) - 32);
		}
	}
	
}

//a funvtion to reverse a string 
void reverseString(char* string){
	int length = strlen(string);
	char temp; 
	for(int i = 0; i < ((length)/2); i++){
		temp = *(string + i);
		*(string + i) = *(string + length - i - 1);
		*(string + length - i - 1) = temp;
	}
}

// a function to turn a point in a grid of char's to lowercase
void lowerCaseGrid(char*** arr, int row, int column){
	if((*(*((*arr) + row) + column) >= 65) && (*(*((*arr) + row) + column) <= 90)){
		*(*((*arr) + row) + column) = (char)(       *(*((*arr) + row) + column)    + 32);
	}
}
