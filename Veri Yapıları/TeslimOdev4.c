#include <stdio.h>
#include <stdlib.h>
struct node1{
	int data1;
	struct node1 *next1;
}*top1=NULL,*p1=NULL,*np1=NULL;
struct node2{
	int data2;
	struct node2 *next2;
}*top2=NULL,*p2=NULL,*np2=NULL;
struct node3{
	int data3;
	struct node3 *next3;
}*top3=NULL,*p3=NULL,*np3=NULL;
int topData;                       //düðüm datalarýný atamak için
int counter = 0;                   //Hamle sayýsý bulmak için
void push1(int data){
	np1 = (struct node1*)malloc(sizeof(struct node1));
	np1->data1 = data;
	np1->next1 = NULL;
	if(top1 == NULL){
		top1 = np1;
	}else{
		np1->next1 = top1;
		top1 = np1;
	}
}
int pop1(){
	int b=999;
	if(top1 == NULL){
		return b;
	}else{
		p1 = top1;
		top1 = top1->next1;
		topData = p1->data1;
		free(p1);
		return topData;
	}
}
void push2(int data){
	np2 = (struct node2*)malloc(sizeof(struct node2));
	np2->data2 = data;
	np2->next2 = NULL;
	if(top2 == NULL){
		top2 = np2;
	}else{
		np2->next2 = top2;
		top2 = np2;
	}
}
int pop2(){
	int b=999;
	if(top2 == NULL){
		return b;
	}else{
		p2 = top2;
		top2 = top2->next2;
		topData = p2->data2;
		free(p2);
		return topData;
	}
}
void push3(int data){
	np3 = (struct node3*)malloc(sizeof(struct node3));
	np3->data3 = data;
	np3->next3 = NULL;
	if(top3 == NULL){
		top3 = np3;
	}else{
		np3->next3 = top3;
		top3 = np3;
	}
}
int pop3(){
	int b=999;
	if(top3 == NULL){
		return b;
	}else{
		p3 = top3;
		top3 = top3->next3;
		topData = p3->data3;
		free(p3);
		return topData;
	}
}
int topOfStack(){                             //üsten elemaný silinecek düðümü bulma
	if(top1 != NULL && top1->data1 == 1 )
        return 1;
    else if (top2 != NULL && top2->data2 == 1)
        return 2;
    else if (top3 != NULL && top3->data3 == 1)
        return 3;
}
void display1(){
	if(counter != 0)
		printf("--------------- %d. Hamle ----------------\n",counter);
	struct node1 *p1;
	p1 = top1;
	printf("Tower 1 ->\t");
	while(p1 != NULL){
		printf("%d ",p1->data1);
		p1 = p1->next1;
	}
	printf("\n");
}
void display2(){
	struct node2 *p2;
	p2 = top2;
	printf("Tower 2 ->\t");
	while(p2 != NULL){
		printf("%d ",p2->data2);
		p2 = p2->next2;
	}
	printf("\n");
}
void display3(){
	struct node3 *p3;
	p3 = top3;
	printf("Tower 3 ->\t");
	while(p3 != NULL){
		printf("%d ",p3->data3);
		p3 = p3->next3;
	}
	printf("\n");
}
void play(int n){
    int i, x, a, b;
    for (i = 0; i < (pow(2,n)); i++){
        display1();                             //listele
        display2();
        display3();
        x = topOfStack();
        if (i % 2 == 0){
            if (x == 1){
                push3(pop1());
            }else if (x == 2){
                push1(pop2());
            }else if (x == 3){
                push2(pop3());
            }
        }else{
            if (x == 1){
                a = pop2();
                b = pop3();
                if (a < b && b != 999){
                    push3(b);
                    push3(a);
            	}else if (a > b && a != 999){
                    push2(a);
                    push2(b);
                }else if (b == 999){
                    push3(a);
                }else if (a == 999){
                    push2(b);
                }
            }else if (x == 2){
                a = pop1();
                b = pop3();
                if (a < b && b != 999){
                    push3(b);
                    push3(a);
                }else if (a > b && a != 999){
                    push1(a);
                    push1(b);
                }else if (b == 999){
                    push3(a);
                }else if (a == 999){
                    push1(b);
                }
            }else if (x == 3){
                a = pop1();
                b = pop2();
                if (a < b && b != 999){
                    push2(b);
                    push2(a);
                }else if (a > b && a != 999){
                    push1(a);
                    push1(b);
                }else if (b == 999){
                    push2(a);
                }else if (a == 999){
                    push1(b);
                }
            }
        }
        counter++;
    }
}
void manager(){
	int n,i;
	printf("Kac adet disk olsun ?: ");
	scanf("%d",&n);
	for(i=n;i>=1;i--){
		push1(i);
	}
	play(n);
}
int main(int argc, char *argv[]) {
	manager();
	return 0;
}
