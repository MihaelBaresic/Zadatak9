#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _bTree;
typedef struct _bTree* Position;
typedef struct _bTree {
	int el;
	Position Lchild;
	Position Rchild;

}bTree;


Position createEl(int);
Position addEl(int, Position);
void menu(Position);
Position findMinRight(Position);
int deleteAll(Position);
Position find(int,Position);
Position deleteEl(int, Position);
void printAll(Position);

int main()
{
	Position Root=NULL;
	menu(Root);

	return EXIT_SUCCESS;
}

Position createEl(int el) {
	Position K;
	K = (Position)malloc(sizeof(bTree));
	if (!K)
		printf("Memory allocation failed!");

	K->el = el;
	K->Lchild = NULL;
	K->Rchild = NULL;

	return K;
}

void menu(Position root)
{
	Position current = root;
	int option;
	int number;
	Position temp;

	

	while (1) {
		
		puts("\nChoose:\n");
		puts("(0) To exit\n");
		puts("(1) To add new number in binary tree\n");
		puts("(2) To find number\n");
		puts("(3) To delete number\n");
		puts("(4) To print current tree in order: \n");
		scanf("%d", &option);

		switch (option) {
		case 0:
			deleteAll(current);
			return EXIT_SUCCESS;
			break;
		case 1:
			printf("Enter number to add: ");
			scanf("%d",&number);
			
			if (find(number, root) == NULL)
				root = addEl(number, root);
			else
				printf("Number already exists in tree you can't add it twice!\n");
			break;
		case 2:
			printf("Enter number to find: ");
			scanf("%d",&number);
			temp = find(number, root);

			if (temp != NULL)
				printf("Number exists!\n");
			else
				printf("Number doesn't exist!\n");

			break;
		case 3:
			printf("Enter number to delete: ");
			scanf("%d",&number);
			

			if (find(number, root) != NULL) {
				root = deleteEl(number, root);
				printf("Number deleted!");

			}
			else
				printf("Number doesn't exists in tree you can't delete it!\n");

			break;
		case 4:
			printf("Current Tree in order: \n");
			printAll(root);
			if (root == NULL)
				printf("Binary tree is empty!");
			break;
		default:
			puts("Choose only numbers from 0-4!\n");
			break;
		}

	}
}

Position find(int el, Position current) {

	if (NULL == current)
		return NULL;

	if (el < current->el)
		return find(el, current->Lchild);
	else if (el > current->el)
		return find(el, current->Rchild);
	else
		return current;


}

Position addEl(int el, Position current) {

	if (NULL == current)
		current = createEl(el);

	if (el < current->el)
		current->Lchild = addEl(el, current->Lchild);
	else if (el > current->el)
		current->Rchild = addEl(el, current->Rchild);
	
	return current;

}

Position deleteEl(int el,Position current) {

	if (NULL == current)
		return EXIT_SUCCESS;
	else if (el < current->el) 
		current->Lchild = deleteEl(el, current->Lchild);
	else if(el > current->el)
		current->Rchild = deleteEl(el, current->Rchild);
	else if (current->Lchild != NULL && current->Rchild != NULL) {
		Position Temp = findMinRight(current->Rchild);
		current->el = Temp->el;
		current->Rchild = deleteEl(current->el, current->Rchild);
	}
	else {
		if (NULL == current->Lchild)
			current = current->Rchild;

		else if (NULL != current->Lchild)
			current = current->Lchild;
	}

	return current;
}

int deleteAll(Position current) {
	if (NULL == current)
		return EXIT_SUCCESS;


	deleteAll(current->Lchild);
	deleteAll(current->Rchild);
	free(current);

	return EXIT_SUCCESS;
}

Position findMinRight(Position current) {
	if (NULL == current)
		return NULL;
	else if (NULL == current->Lchild)
		return current;
	else
		return findMinRight(current->Lchild);
	
}

void printAll(Position current) {

	if (current != NULL) {
		printAll(current->Lchild);
		printf("%d  ", current->el);
		printAll(current->Rchild);
	}

}
