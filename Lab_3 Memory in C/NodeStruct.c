
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct Node {
    int iValue;
    float fValue ;
    struct Node *next;
};

int main() {

    struct Node *head = (struct Node*) malloc(sizeof(struct Node));
    head->iValue = 5;
    head->fValue = 3.14;
	
	// Insert extra code here
	printf("Address of head: %p\n", head);
	printf("Value of head i value: %d\n", head->iValue);
	printf("Value of head f value: %f\n", head->fValue);
	printf("Address of iValue: %p\n", &(head->iValue));
	printf("Address of fvalue: %p\n", &(head->fValue));
	printf("Address of next: %p\n", &(head->next));
	
	return 0;
}
