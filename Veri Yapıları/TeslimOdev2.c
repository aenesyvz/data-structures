#include <stdio.h>
#include <stdlib.h>
struct linkedList{
	int data;
	struct linkedList *prevAddress;
	struct linkedList *nextAddress;
};
struct linkedList *firstNode = NULL;
struct linkedList *createNode(int value){
	struct linkedList *newNode = (struct linkedList*)malloc(sizeof(struct linkedList));
	newNode->data = value;           
	newNode->prevAddress = NULL;	 
	newNode->nextAddress = NULL;     
	return newNode;
}
void prependNode(int value){        //Baþtan ekle
	struct linkedList* newNode = createNode(value);
	if(firstNode == NULL){
		firstNode = newNode;
		return;
	}
	firstNode->prevAddress = newNode;
	newNode->nextAddress = firstNode;
	firstNode = newNode;
}
void appendNode(int value){        //Sondan ekle
	struct linkedList* newNode = createNode(value);
	if(firstNode == NULL){
		prependNode(value);
	}else{
		struct linkedList *temp = firstNode;
		while(temp->nextAddress != NULL){
			temp = temp->nextAddress;
		}
		newNode->prevAddress = temp;
		temp->nextAddress = newNode;
	}
}
void insertNode(int key,int value){  //Araya (key in olduðu) yere ekle
	struct linkedList* temp = firstNode;
	struct linkedList* newNode = createNode(value);
	struct linkedList* prevNode = NULL;
	if(firstNode == NULL){
		prependNode(value);
	}else if(firstNode->data == key){
		prependNode(value);
	}else{
		while(temp != NULL){
			if(temp->data == key){
				prevNode = temp->prevAddress;
				break;
			}
			temp = temp->nextAddress;
		}
		if(temp != NULL){
			temp->prevAddress = newNode;
			newNode->nextAddress = temp;
			newNode->prevAddress = prevNode;
			prevNode->nextAddress = newNode;
		}
	}
}
void deleteFirstNode(){          //Baþtan sil
	if(firstNode == NULL){
		printf("Liste bostur!\n");
		return;
	}
	if(firstNode->nextAddress == NULL){
		free(firstNode);
		firstNode = NULL;
		return;
	}
	struct linkedList* nextNode = firstNode->nextAddress;
	free(firstNode);
	nextNode->prevAddress = NULL;
	firstNode = nextNode;
}
void deleteFromTheEnd(){         //Sondan sil
	if(firstNode == NULL){
		printf("Liste bostur!\n");
		return;
	}
	if(firstNode->nextAddress == NULL){
		deleteFirstNode();
		return;
	}
	struct linkedList *temp = firstNode;
	while(temp->nextAddress != NULL){
		temp = temp->nextAddress;
	}
	struct linkedList* prevNode = temp->prevAddress;
	free(temp);
	prevNode->nextAddress = NULL;
}
void deleteFromInterval(int value){   //Aradan sil
	if(firstNode == NULL){
		printf("Liste bostur!\n");
		return;
	}
	if(firstNode->data == value){
		deleteFirstNode();
		return;
	}
	struct linkedList *temp = firstNode;
	while(temp != NULL){
		if(temp->data == value){
			break;
		}
		temp = temp->nextAddress;
	}
	if(temp == NULL){
		return;
	}
	if(temp->nextAddress == NULL){
		deleteFromTheEnd();
		return;
	}
	struct linkedList* nextNode = temp->nextAddress;
	struct linkedList* prevNode = temp->prevAddress;
	free(temp);
	prevNode->nextAddress = nextNode;
	nextNode->prevAddress = prevNode;
	
}
struct linkedList *findNode(int sequence){
	int counter = 0;
	struct linkedList *temp = firstNode;
	while(temp != NULL){
		if(sequence == counter){
			return temp;
		}
		temp = temp->nextAddress;
		counter++;
	}
	printf("Hatali bir sira degeri girdiniz!");
	return temp = NULL;
}
void printLinkedList(int sequence,char message[]){
	if(firstNode == NULL){
		printf("Listede eleman bulunmamaktadir!\n");
		return;
	}
	struct linkedList *temp = findNode(sequence);
	if(!strcmp(message,"geri") || !strcmp(message,"ileri")){
		while(temp != NULL){
			printf("%d\t",temp->data);
			if(!strcmp(message,"geri")){
				temp = temp->prevAddress;
			}else{
				temp = temp->nextAddress;
			}
		}
	}else{
		printf("Mesaj olarak 'ileri' veya 'geri' parametresini gonderin!");
	}
	printf("\n");
}
int main(int argc, char *argv[]) {
	printLinkedList(2,"ileri"); 
	deleteFromInterval(37);       
	deleteFirstNode();            
	deleteFromTheEnd();           
	insertNode(3,37);
	deleteFromInterval(37);
	appendNode(55);
	deleteFromTheEnd();
	prependNode(30);
	deleteFirstNode();
	appendNode(1923);
	prependNode(1919);
	insertNode(1923,1453);
	insertNode(1453,1071);
	insertNode(1919,1905);
	prependNode(34);
	appendNode(1041);
	printLinkedList(0,"ileri");
	printLinkedList(6,"geri");
	printLinkedList(3,"geri");
	printLinkedList(3,"ileri");
	printLinkedList(37,"ileri");
	printLinkedList(35,"ggeri");
	printLinkedList(3,"iileri");
	deleteFromInterval(37);  
	deleteFirstNode();
	deleteFirstNode();
	deleteFromTheEnd();
	deleteFromInterval(1923);
	deleteFromInterval(1453);
	deleteFromInterval(1919);
	insertNode(19149,37);////
	insertNode(1071,2021);
	insertNode(2021,630);
	insertNode(1071,1494);
	insertNode(630,1566);
	insertNode(1494,2030);
	deleteFromInterval(2021);
	deleteFromInterval(2021);
	deleteFromInterval(1071);
	printLinkedList(0,"ileri");	
	printLinkedList(3,"geri");
	return 0;
}

