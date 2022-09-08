#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)


struct listNode {
	int data;
	char string[21];
	struct listNode *nextPtr; 
}; 
typedef struct listNode ListNode; 
typedef ListNode *ListNodePtr; 

void insert(ListNodePtr *sPtr, int value,char string1[21]);
char deleted(ListNodePtr *sPtr, int value, char string1[21]);
int isEmpty(ListNodePtr sPtr);
void printList(ListNodePtr currentPtr);
void instructions(void);

int main(void)
{
	ListNodePtr startPtr = NULL;
	unsigned int choice; 
	int item;
	char st[21];
	instructions(); 
	printf("%s", "? ");
	scanf("%u", &choice);

	while (choice != 3) {
		switch (choice) {
		case 1:
			printf("%s", "Enter a word(less than 20 letters): ");
			scanf("%s", st);

			printf("%s", "Enter a number: ");
			scanf("\n%d", &item);

			insert(&startPtr, item,st);
			printList(startPtr);
			break;

		case 2: // delete an element
			  // if list is not empty
			if (!isEmpty(startPtr)) 
			{
				printf("%s", "Enter character to bedeleted: ");
				scanf("\n%d", &item);
				// if character is found, remove it
				if (deleted(&startPtr, item,st))
				{ 
					printf("%d %s deleted.\n", item,st);
					printList(startPtr);
				} 
				else 				
					printf("%d not found.\n\n", item);				
			}
			else {
				puts("List is empty.\n");
			} 
			break;

		default:
			puts("Invalid choice.\n");
			instructions();
			break;
		} 

		printf("%s", "? ");
		scanf("%u", &choice);
	} 
	puts("End of run.");
} 



// display program instructions to user
void instructions(void)
{
	puts("Enter your choice:\n"
		" 1 to insert an element into the list.\n"
		" 2 to delete an element from the list.\n"
		" 3 to end.");
} 


// insert a new value into the list in sorted order
void insert(ListNodePtr*sPtr, int value, char string1[21])
{
	ListNodePtr newPtr = NULL; // pointer to new node
	ListNodePtr previousPtr = NULL; // pointer to previous node in list
	ListNodePtr currentPtr = NULL; // pointer to current node in list

	newPtr = (ListNode *)malloc(sizeof(ListNode)); 

	if (newPtr != NULL) { // is space available
		newPtr->data = value; // place value in node
		newPtr->nextPtr = NULL; // node does not link to another node
		for (int j = 0; j < 21; j++) {
			newPtr->string[j] = string1[j];
			if (string1[j] == '\0') {
				break;
			}

		}
		previousPtr = NULL;
		currentPtr = *sPtr;

		// loop to find the correct location in the list
		while (currentPtr != NULL && value<currentPtr->data) {
			previousPtr = currentPtr; // walk to ...
			currentPtr = currentPtr->nextPtr; // ... next node
		} // end while

		// insert new node at beginning of list
		if (previousPtr == NULL) {
			newPtr->nextPtr = *sPtr;
			*sPtr = newPtr;
		} // end if
		else { // insert new node between previousPtr and currentPtr
			previousPtr->nextPtr = newPtr;
			newPtr->nextPtr = currentPtr;
		} 
	} 

	else {
		printf("%d not inserted. No memory available.\n", value);
	} 
} 




// delete a list element
char deleted(ListNodePtr*sPtr, int value, char string1[21])
{
	ListNodePtr previousPtr; // pointer to previous node in list
	ListNodePtr currentPtr; // pointer to current node in list
	ListNodePtr tempPtr; // temporary node pointer

	// delete first node 
	if (value == (*sPtr)->data) {
		tempPtr = *sPtr; // hold onto node being removed
		*sPtr = (*sPtr)->nextPtr; // de-thread the node
		free(tempPtr); // free the de-threaded node
		return value;
	} 

	else {
		previousPtr = *sPtr;
		currentPtr = (*sPtr)->nextPtr;
		// loop to find the correct location in the list
		while (currentPtr != NULL && currentPtr->data != value) {
			previousPtr = currentPtr; // walk to ...
			currentPtr = currentPtr->nextPtr; // ... next node
		} 
	// delete node at currentPtr
		if (currentPtr != NULL) {
			tempPtr = currentPtr;
			previousPtr->nextPtr = currentPtr->nextPtr;
			free(tempPtr);
			return value;
		} 
	} 
	return '\0';
} 

 
  
  // return 1 if the list is empty, 0 otherwise
int isEmpty(ListNodePtr sPtr)
{
	return sPtr == NULL;
} // end function isEmpty



// print the list
void printList(ListNodePtr currentPtr) {

	// if list is empty
	if (isEmpty(currentPtr)) {
		puts("List is empty.\n");
	}
	else {
		puts("The list is:");

		while (currentPtr != NULL) {
			printf("%d", currentPtr->data);
			printf("%s", currentPtr->string);
			printf("-->");
			currentPtr = currentPtr->nextPtr;
		}
		puts("NULL\n");
	}
}



