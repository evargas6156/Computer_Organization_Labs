# include <stdio.h>


int main(){
	int x, y, *px, *py;
	x = 0;
	y = 0;
	int arr[10];
	for(int i = 0; i < 10; i++){
		arr[i] = i;
	}
	px = &x;
	py = &y;
	printf("Value of x: %d\n", x);
	printf("Value of y: %d\n", y);
	printf("Address of x: %p\n", &x);
	printf("Address of y: %p\n", &y);
	printf("Value of px:  %p\n", px);
	printf("Value of py:  %p\n", py);
	printf("Address of px: %p\n", &px);
	printf("Address of py: %p\n", &py);
	printf("Value of arr[0]: %d\n", arr[0]);

	for(int i = 0; i < 10; i++){
		printf("Value at index %d using arr name pointer: %d\n",i , *(arr + i));

	}
	printf("Address of arr[0]:     %p\n", &arr[0]);
	printf("Address arr points to: %p\n", arr);
	printf("Address of arr:        %p\n", &arr);
	return 0;
}
