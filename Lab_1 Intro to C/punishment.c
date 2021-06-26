#include <stdio.h> 

int main(){

	int numLines;
	int typoLine;

	printf("Enter the number of lines for the punishment: ");
	scanf("%d", &numLines);

	if(numLines < 0){
	printf("You entered an incorrect value for the number of lines!\n");
	return 0;

	}

	printf("Enter the line for which we want to make a typo: ");
	scanf("%d", &typoLine);

	if(typoLine < 0 || typoLine > numLines){
	printf("You entered an incorrect value for the line typo!\n");
	return 0;
	}

	for(int i = 1; i < (numLines + 1); i++){
	if(i == typoLine){
		printf("C programming language is the bet!\n");
	}else{
		printf("C programming language is the best!\n");
	}

	}
	return 0;

}
