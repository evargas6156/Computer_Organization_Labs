#include<stdio.h>

int newBars(int numBars, int n);
int maxBars(int n, int price, int money);

int maxBars(int n, int price, int money){
	int maxBar;
    int purchasedBars = money/price;
	if(purchasedBars == 0){
		return 0;
	}else{
		printf("You first buy %d bars.\n", purchasedBars);
	
		maxBar = purchasedBars + newBars(purchasedBars, n);
		return maxBar;
	}
}

int newBars(int numBars, int n){
	int freeBars;
    if(numBars < n){
		return 0;
	}else{
		freeBars = numBars/n;
		printf("Then, you will get another %d bars.\n", freeBars);
		return freeBars + newBars(freeBars, n);
	}
}

int main(){
    int price;
	int n;
	int money; 
	int maxBar;
	
    printf("Welcome to BobCat Candy, home of the famous BobCat Bars!\n");
	printf("Please enter the price of a BobCat Bar: \n");
	scanf("%d", &price);
	while(price <= 0){
		printf("Please enter a price greater than zero!\n");
		scanf("%d", &price);
	}
	
	printf("Please enter the number of wrappers needed to exchange for a new bar: \n");
	scanf("%d", &n);
	while(n <= 1){
		printf("Please enter a number of wrappers greater than one!\n");
		scanf("%d", &n);
	}
	
	printf("How much do you have?\n");
	scanf("%d", &money);
	while(money < 0){
		printf("Please enter an amount of money greater than or equal to zero!\n");
		scanf("%d", &money);
	}
	
	printf("Good! Let me run the number...\n");
    maxBar = maxBars(n, price, money);
	
	printf("With $%d, you will recieve a maximum of %d BobCat Bars!\n", money, maxBar);
	
    return 0;
}