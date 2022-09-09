#include <stdio.h>
#include <stdlib.h>

struct linkedList{
	int data;
	struct linkedList* address;
};

struct linkedList* firstNode = NULL;

struct linkedList* createNode(int value){
	struct linkedList* newNode = (struct linkedList*)malloc(sizeof(struct linkedList));
	newNode->data = value;
	newNode->address = NULL;
	return newNode;
}

void printLinkedList(){
	struct linkedList* temp = firstNode;
	while(temp != NULL){
		printf("%d\t",temp->data);
		temp = temp->address;
	}
	printf("\n");
}

void deleteNode(int value){
	struct linkedList* temp = firstNode;
	struct linkedList* previousNode = firstNode;
	while(temp != NULL){
		if(temp->data == value){
			if(firstNode->data == value) {
				firstNode = temp->address;
			}else if(temp->address != NULL){
				previousNode->address = temp->address;
			}else{
				previousNode->address = NULL; 
			}	
			free(temp);
			break; 
		}
		previousNode = temp;
		temp = temp->address;
	}
	if(temp != NULL) {
		printf("%d sayisi listeden silindi!\n",value);
	}else {
		printf("%d sayisi listede bulunamadi!\n",value);
	}
}

void addNewNode(int value){
	struct linkedList* newNode = createNode(value);
	if(firstNode == NULL){
		firstNode = newNode;
	}
	else{
		struct linkedList* temp = firstNode;
		while(temp -> address != NULL){
			temp = temp -> address;
		}
		temp -> address = newNode;
	}
	printf("%d sayisi listeye eklendi!\n",value);
}

int main(int argc, char *argv[]) {
	deleteNode(30);
	addNewNode(30);
	deleteNode(30);
	addNewNode(30);
	addNewNode(37);
	addNewNode(34);
	deleteNode(34);
	deleteNode(30);
	addNewNode(55);
	addNewNode(6);
	addNewNode(35);
	addNewNode(55);
	deleteNode(81);
	deleteNode(6);
	deleteNode(55);
	deleteNode(6);
	printLinkedList();
	return 0;
}
