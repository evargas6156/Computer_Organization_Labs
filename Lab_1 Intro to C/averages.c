#include <stdio.h>

int main(){

	int curr, sumPos, sumNeg, posNum, negNum;
	curr = 1;
	sumPos = 0;
	sumNeg = 0;
	posNum = 0;
	negNum = 0;

	while(curr != 0){
		printf("Please enter an integer: ");
		scanf("%d",&curr);
		if(curr < 0){
		sumNeg = sumNeg + curr;
		negNum = negNum + 1;
		}else if(curr > 0){
		sumPos =sumPos + curr;
		posNum = posNum + 1;
		}
	}

	if(sumPos != 0){
	printf("Positive average: %d\n", sumPos/posNum);
	}
	if(sumNeg != 0){
	printf("Negative average: %d\n",sumNeg/negNum);
	}

	return 0;
}
