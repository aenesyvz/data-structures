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
void prependNode(int value){       
	struct linkedList* newNode = createNode(value);
	if(firstNode == NULL){
		firstNode = newNode;
		newNode->nextAddress = firstNode;
		newNode->prevAddress = firstNode;
		return;
	}
	struct linkedList *temp = firstNode;
	while(temp->nextAddress != firstNode){
		temp = temp->nextAddress;
	}
	newNode->nextAddress = firstNode;
	firstNode->prevAddress = newNode;
	firstNode = newNode;
	firstNode->prevAddress = temp;
	temp->nextAddress = newNode;
}
void appendNode(int value){
	struct linkedList *newNode = createNode(value);
	if(firstNode == NULL){
		prependNode(value);
		return;
	}
	struct linkedList *temp = firstNode;
	while(temp->nextAddress != firstNode){
		temp = temp->nextAddress;
	}
	temp->nextAddress = newNode;
	newNode->prevAddress = temp;
	newNode->nextAddress = firstNode;
	firstNode->prevAddress = newNode;
}
void insertNode(int sequence,int value){
	struct linkedList* temp = firstNode;
	struct linkedList* newNode = createNode(value);
	int counter = 1;
	if(firstNode == NULL){
		prependNode(value);
	}else if(sequence == 0){
		prependNode(value);
	}else{
		while(counter != sequence){
			temp = temp->nextAddress;
			counter++;
		}
		if(temp->nextAddress == firstNode){
			appendNode(value);
		}else{
			newNode->nextAddress = temp->nextAddress;
			temp->nextAddress->prevAddress = newNode;
			newNode->prevAddress = temp;
			temp->nextAddress = newNode;
		}
	}
}
void deleteFirstNode(){
	struct linkedList *temp = firstNode;
	if(firstNode == NULL){
		printf("Listede eleman bulunmamaktadir!\n");
		return;
	}
	while(temp->nextAddress != firstNode){
		temp = temp->nextAddress;
	}
	if(firstNode->nextAddress == firstNode){
		free(firstNode);
		firstNode = NULL;
		return;
	}
	temp->nextAddress = firstNode->nextAddress;
	free(firstNode);
	firstNode = firstNode->nextAddress;
	firstNode->prevAddress = temp;
}
void deleteFromTheEnd(){
	struct linkedList *temp = firstNode;
	if(firstNode == NULL){
		printf("Listede eleman bulunmamaktadir!\n");
		return;
	}
	while(temp->nextAddress->nextAddress != firstNode){
		temp = temp->nextAddress;
	}
	if(firstNode->nextAddress == firstNode){
		free(firstNode);
		firstNode = NULL;
		return;
	}
	free(temp->nextAddress);
	temp->nextAddress = firstNode;
	firstNode->prevAddress = temp;
}
void deleteFromInterval(int sequence){
	int counter = 1;
	if(firstNode == NULL){
		printf("Listede eleman bulunmamaktadir!\n");
		return;
	}
	if(firstNode->nextAddress == firstNode){
		free(firstNode);
		firstNode = NULL;
		return;
	}
	if(sequence == 0){
		deleteFirstNode();
	}else{
		struct linkedList *temp = firstNode;
		while(sequence != counter){
			temp = temp->nextAddress;
			counter++;
		}
		if(temp->nextAddress == firstNode){
			deleteFromTheEnd();
			return;
		}
		free(temp->nextAddress);
		temp->nextAddress = temp->nextAddress->nextAddress;
		temp->nextAddress->prevAddress = temp;
	}
}
struct linkedList *findNode(int sequence){
	int counter = 0;
	struct linkedList *temp = firstNode;
	do{
		if(sequence == counter){
			return temp;
		}
		temp = temp->nextAddress;
		counter++;
	}while(temp != firstNode);
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
		do{
			printf("%d\t",temp->data);
			if(!strcmp(message,"geri")){
				temp = temp->prevAddress;
			}else{
				temp = temp->nextAddress;
			}
		}while(temp != firstNode);
	}else{
		printf("Mesaj olarak 'ileri' veya 'geri' parametresini gonderin!");
	}
	printf("\n");
}
int main(int argc, char *argv[]) {
	printLinkedList(0,"ileri");         
	printLinkedList(0,"geri");          
	deleteFirstNode();                  
	deleteFromInterval(37);             
	deleteFromTheEnd();                 
	prependNode(10);                    
	deleteFirstNode();                  
	appendNode(33);                     
	deleteFromTheEnd();                 
	insertNode(3,1905);                 
	deleteFromInterval(0);              
	prependNode(5);                     
	prependNode(4);                     
	prependNode(2);                     
	appendNode(6);                      
	prependNode(1);                     
	insertNode(2,3);                    
	insertNode(0,0);                    
	insertNode(7,7);                    
	printLinkedList(0,"illeri");        
	printLinkedList(0,"ggeri");         
	printLinkedList(0,"ileri");         
	printLinkedList(0,"geri");          
	printLinkedList(1,"ileri");         
	printLinkedList(7,"geri");          
	deleteFirstNode();                  
	deleteFromTheEnd();                 
	deleteFromInterval(1);              
	deleteFromInterval(2);              
	deleteFromInterval(3);              
	deleteFromInterval(2);              
	deleteFromInterval(0);              
	deleteFromInterval(2);              
	printLinkedList(0,"ileri");         
	printLinkedList(0,"geri");          
	appendNode(37);
	appendNode(55);
	appendNode(34);
	deleteFirstNode();
	insertNode(3,81);
	insertNode(4,5);
	insertNode(3,1905);
	insertNode(0,1923);
	prependNode(1919);
	insertNode(7,43);
	deleteFromTheEnd();
	deleteFromInterval(4);
	deleteFromInterval(2);
	deleteFromInterval(5);
	deleteFromInterval(3);
	deleteFromTheEnd();
	insertNode(100,2);
	deleteFromInterval(111);
	printLinkedList(0,"ileri");         
	printLinkedList(0,"geri");          
	deleteFromTheEnd();
	deleteFirstNode();
	printLinkedList(0,"ileri");
	
	return 0;
}
