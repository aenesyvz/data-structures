#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include <Windows.h>
#define N 10

int musteri = 0;
int idAraba = 0;
int musteriSiraNo;
char renk[N][37] = {"Beyaz","Platinum Gri","Metalik Gri","Kirmizi","Atlantik Mavi","Limon Sari","Kizil Kahve","Fume","Derin Siyah","Metalik Kavansit Mavisi"};

struct araba{
	int id;
	char marka[20];
	char model[20];
	char paket[20];
	char renk[37];
	char tip[20];
	int fiyat;
	int musteri_sayisi;
	int talep_sayisi;
	struct araba *next;
};

struct araba *firstAraba = NULL;

struct node{
	int numara;
	int siraNo;
	char marka[20];
	char model[20];
	char paket[20];
	char renk[37];
	char tip[20];
	int fiyat;
	struct node *next;
};typedef struct node node;

struct node *nodem = NULL;

struct queue{
	struct node *node;
	struct araba *araba;
	struct queue *next;
};

struct queue *rear = NULL;
struct queue *front = NULL;

struct agac{
	struct araba *araba;
	struct agac *sag;
	struct agac *sol;
};

struct agac *yeniDugum(struct araba *arabam){
	struct agac *temp = (struct agac*)malloc(sizeof(struct agac));
	temp->araba = arabam;
	temp->sag = NULL;
	temp->sol = NULL;
	return temp;
}

struct agac *elemanEkle(struct agac *dugum,struct araba *temp){
	if(dugum == NULL){
		return yeniDugum(temp);
	}else if(temp->fiyat < dugum->araba->fiyat){
		dugum->sol = elemanEkle(dugum->sol,temp);
	}else{
		dugum->sag = elemanEkle(dugum->sag,temp);
	}
	return dugum;
}

void arabaBilgileriniYaz(struct araba *araba){
	printf("\n---------------------------\n");
	printf("Id:\t%d\n",araba->id);
	printf("Marka:\t%s\n",araba->marka);
	printf("Model:\t%s\n",araba->model);
	printf("Paket:\t%s\n",araba->paket);
	printf("Tip:\t%s\n",araba->tip);
	printf("Fiyat:\t%d\n",araba->fiyat);
	printf("\n---------------------------\n");
}

void fiyatArtan(struct agac *firstNode){
	if(firstNode != NULL){
		fiyatArtan(firstNode->sol);
		arabaBilgileriniYaz(firstNode->araba);
		fiyatArtan(firstNode->sag);
	}
} 

void fiyatAzalan(struct agac *firstNode){
	if(firstNode != NULL){
		fiyatAzalan(firstNode->sag);
		arabaBilgileriniYaz(firstNode->araba);
		fiyatAzalan(firstNode->sol);
	}
}

void createTree(){
	struct agac *firstNode = NULL;
	struct araba *temp = firstAraba;
	if(temp == NULL){
		printf("Listede araba bulunmamaktadir!\n");
		return;
	}
	while(temp != NULL){
		firstNode = elemanEkle(firstNode,temp);
		temp = temp->next;
	}
	int secim;
	printf("FIYATINA GORE ARTAN LISTESI => 1\n");
	printf("FIYATINA GORE AZALAN LISTESI => 2\n");
	scanf("%d",&secim);
	if(secim == 1){
		fiyatArtan(firstNode);
	}else{
		fiyatAzalan(firstNode);
	}
}

int kontrolEt(char marka[],char model[],char paket[],char tip[]){
	struct araba *temp = firstAraba;
	while(temp != NULL){
		if(!strcmp(temp->marka,marka) && !strcmp(temp->model,model) && !strcmp(temp->paket,paket) && !strcmp(temp->tip,tip)){
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}

struct araba *arabaOlustur(){
	struct araba *newAraba = (struct araba*)malloc(sizeof(struct araba));
	int fiyat;
	char marka[20],model[20],paket[20],tip[20];
	printf("Arabanin markasini giriniz: ");
	scanf("%s",marka);
	printf("Arabanin modelini giriniz: ");
	scanf("%s",model);
	printf("Arabanin paketini giriniz: ");
	scanf("%s",paket);
	printf("Arabanin tipini giriniz: ");
	scanf("%s",tip);
	printf("Arabanin fiyatini giriniz: ");
	scanf("%d",&fiyat);
	if(kontrolEt(marka,model,paket,tip)){
		return newAraba = NULL;
	}
	newAraba->id = ++idAraba;
	strcpy(newAraba->marka,marka);
	strcpy(newAraba->model, model);
	strcpy(newAraba->paket,paket);
	strcpy(newAraba->renk,"");
	strcpy(newAraba->tip,tip);
	newAraba->fiyat = fiyat;
	newAraba->next = NULL;
	newAraba->musteri_sayisi = 0;
	newAraba->talep_sayisi = 0;
	return newAraba;
}

void basaArabaEkle(){
	struct araba* newNode = arabaOlustur();
	if(newNode == NULL){
		printf("\nHata! Girdiginiz bilgilere sahip araba zaten var!\n");
		return;
	}
	if(firstAraba == NULL){
		firstAraba = newNode;
		printf("%s %s %s arabasi listeye eklendi!\n",newNode->marka,newNode->model,newNode->paket);
		return;
	}
	newNode->next = firstAraba;
	firstAraba = newNode;
	printf("%s %s %s arabasi listeye eklendi!\n",newNode->marka,newNode->model,newNode->paket);
}

void sonaArabaEkle(){
	if(firstAraba == NULL){
		basaArabaEkle();
		return;
	}
	struct araba* newNode = arabaOlustur();
	if(newNode == NULL){
		printf("\nHata! Girdiginiz bilgilere sahip araba zaten var!\n");
		return;
	}
	struct araba* temp = firstAraba;
	while(temp -> next != NULL){
		temp = temp -> next;
	}
	temp -> next = newNode;
	printf("%s %s %s arabasi listeye eklendi!\n",newNode->marka,newNode->model,newNode->paket);
}

int arabaSayisi(){
	int sayac = 0;
	struct araba* temp = firstAraba;
	while(temp != NULL){
		sayac++;
		temp= temp->next;
	}
	return sayac;
}

void arayaArabaEkle(){
	int sira;
	printf("\nEklenecek araba kacinci sirada olsun: ");
	scanf("%d",&sira);
	sira = sira - 1;
	
	if(firstAraba == NULL || sira == 0){
		basaArabaEkle();
		return;
	}
	if(arabaSayisi() <= sira){
		sonaArabaEkle();
		return;
	}
	int sayac = 0;
	struct araba* temp = firstAraba;
	struct araba* prev = firstAraba;
	struct araba* newNode = arabaOlustur();
	if(newNode == NULL){
		printf("\nHata! Girdiginiz bilgilere sahip araba zaten var!\n");
		return;
	}
	while(temp->next != NULL){
		if(sayac == sira){
			break;
		}
		sayac++;
		prev = temp;
		temp = temp->next;
	}
	if(temp == NULL){
		sonaArabaEkle();
		return;
	}
	if(temp != NULL){
		prev->next = newNode;
		newNode->next = temp;
	}
	printf("%s %s %s arabasi listeye eklendi!\n",newNode->marka,newNode->model,newNode->paket);
}

void arabaEkle(){
	int secim;
	printf("Basa araba ekle => 1\n");
	printf("Araya araba ekle => 2\n");
	printf("Sona araba ekle => 3\n");
	printf("Seciminiz: ");
	scanf("%d",&secim);
	if(secim == 1){
		basaArabaEkle();
	}else if(secim == 2){
		arayaArabaEkle();
	}else{
		sonaArabaEkle();
	}
}
void arabaSil(int id){
	struct araba* temp = firstAraba;
	struct araba* previousNode = firstAraba;
	while(temp != NULL){
		if(temp->id == id){
			if(firstAraba->id == id) {
				firstAraba = temp->next;
			}else if(temp->next != NULL){
				previousNode->next = temp->next;
			}else{
				previousNode->next = NULL; 
			}	
			free(temp);
			break; 
		}
		previousNode = temp;
		temp = temp->next;
	}
	if(temp != NULL) {
		printf("%d nolu araba listeden silindi!\n",id);
	}else {
		printf("%d nolu olan bir araba listede bulunamadi!\n",id);
	}
}

struct araba *findAraba(int id){
	struct araba *temp = firstAraba;
	while(temp != NULL){
		if(temp->id == id){
			return temp;
		}
		temp = temp->next;
	}
	return temp = NULL;
}


void arabaGuncelle(int id){
	struct araba *temp = findAraba(id);
	if(temp == NULL){
		printf("%d nolu olan bir araba listede bulunamadi!\n",id);
	}
	if(temp != NULL){
		char marka[20],model[20],paket[20],tip[20];
		int fiyat;
		printf("Arabanin markasini giriniz: ");
		scanf("%s",marka);
		printf("Arabanin modelini giriniz: ");
		scanf("%s",model);
		printf("Arabanin paketini giriniz: ");
		scanf("%s",paket);
		printf("Arabanin tipini giriniz: ");
		scanf("%s",tip);
		printf("Arabanin fiyatini giriniz: ");
		scanf("%d",&fiyat);
		
		strcpy(temp->marka,marka);
		strcpy(temp->model, model);
		strcpy(temp->paket,paket);
		strcpy(temp->renk,"");
		strcpy(temp->tip,tip);
		temp->fiyat = fiyat;
		printf("Guncelleme islemi basarili!\n");
	}	
}

void printLinkedList(){
	struct araba* temp = firstAraba;
	if(temp == NULL){
		printf("Araba listesi bostur!\n");
		return;
	}
	while(temp != NULL){
		arabaBilgileriniYaz(temp);
		temp= temp->next;
	}
	printf("---------------------------------\n");
}

void idNumaralariniGuncelle(){
	int sayac = 0;
	struct araba *temp = firstAraba;
	while(temp != NULL){
		temp->id = ++sayac;
		temp = temp->next;
	}
}

void markaAra(){
	char marka[20];
	printf("Aramak istediginiz markayi giriniz: ");
	scanf("%s",marka);
	struct araba *temp = firstAraba;
	while(temp != NULL){
		if(!strcmp(marka,temp->marka)){
			arabaBilgileriniYaz(temp);
		}
		temp = temp->next;
	}
	if(temp != NULL){
		printf("\nListede bulunan tum %s markasi olan arabalar listelenmistir!\n",marka);
	}
}

void markaModelAra(){
	char marka[20],model[20];
	printf("Aramak istediginiz arabanin markasini giriniz: ");
	scanf("%s",marka);
	printf("Aramak istediginiz arabanin modelini giriniz: ");
	scanf("%s",model);
	struct araba *temp = firstAraba;
	while(temp != NULL){
		if(!strcmp(marka,temp->marka) && !strcmp(model,temp->model)){
			arabaBilgileriniYaz(temp);
		}
		temp = temp->next;
	}
	if(temp != NULL){
		printf("\nListede bulunan tum %s markasi %s model olan arabalar listelenmistir!\n",marka,model);
	}
}

void tipAra(){
	char tip[20];
	printf("Aramak istediginiz araba tipini giriniz: ");
	scanf("%s",tip);
	struct araba *temp = firstAraba;
	while(temp != NULL){
		if(!strcmp(tip,temp->tip)){
				arabaBilgileriniYaz(temp);
		}
		temp = temp->next;
	}
	if(temp != NULL){
		printf("\nListede bulunan tum %s tipli olan arabalar listelenmistir!\n",tip);
	}
}

void fiyatAra(){
	int min,max;
	printf("Alt tutar giriniz: ");
	scanf("%d",&min);
	printf("Ust tutar giriniz: ");
	scanf("%d",&max);
	struct araba *temp = firstAraba;
	while(temp != NULL){
		if(temp->fiyat <= max && temp->fiyat >= min){	
			arabaBilgileriniYaz(temp);
		}
		temp = temp->next;
	}
	if(temp != NULL){
		printf("\nListede bulunan arabalardan alt tutar : %d TL ust tutar : %d TL arasinda olan arabalar listelenmistir!\n",min,max);
	}
}

void siraGuncelle(char marka[],char model[],char paket[],char tip[]){
	int sayac = 0;
	struct node *temp = nodem;
	while(temp != NULL){
		if(!strcmp(temp->marka,marka) && !strcmp(temp->model,model) && !strcmp(temp->paket,paket) && !strcmp(temp->tip,tip)){
			temp->siraNo = ++sayac;
		}
		temp = temp->next;
	}
}


void talepGuncelle(char marka[],char model[],char paket[],char tip[]){
	struct araba *temp = firstAraba;
	while(temp != NULL){
		if(!strcmp(temp->marka,marka) && !strcmp(temp->model,model) && !strcmp(temp->paket,paket) && !strcmp(temp->tip,tip)){
			temp->talep_sayisi--;
		}
		temp = temp->next;
	}
} 

void musteriSil(int id){
	char marka[20],model[20],paket[20],tip[20];
	struct node *temp = nodem;
	struct node* previousNode = nodem;
	while(temp != NULL){
		if(temp->numara == id){
			if(nodem->numara == id) {
				nodem = temp->next;
			}else if(temp->next != NULL){
				previousNode->next = temp->next;
			}else{
				previousNode->next = NULL; 
			}	
			strcpy(marka,temp->marka);
			strcpy(model,temp->model);
			strcpy(paket,temp->paket);
			strcpy(tip,temp->tip);
			free(temp);
			break; 
		}
		previousNode = temp;
		temp = temp->next;
	}
	if(temp != NULL) {
		printf("%d numarali musteri listeden silindi!\n",id);
		siraGuncelle(marka,model,paket,tip);
		talepGuncelle(marka,model,paket,tip);
	}else {
		printf("%d numarali musteri listede bulunamadi!\n",id);
	}
}

void printSale(struct node *node,struct araba *araba){
	printf("-------------------------------------------------------------------------------------------\n");
	printf("Musteri-%d  %s %s %s %s renkli araba icin %d. sirada\n",++musteri,araba->marka,araba->model,araba->paket,node->renk,node->siraNo);
	printf("Musteri-%d  %s %s %s teslim edildi odenen tutar : %d\n",musteri,araba->marka,araba->model,araba->paket,araba->fiyat);
	printf("--------------------------------------------------------------------------------------------\n");
}

void enqueue(struct node *node,struct araba *araba,int renkId){
	strcpy(node->renk,renk[renkId]);
	
	if(rear == NULL) {
		rear = (struct queue*)malloc(sizeof(struct queue));
		rear->araba = araba;
		node->siraNo = ++araba->talep_sayisi;
		rear->node = node;
		rear->next = NULL;
		front = rear;
	}
	else {
		struct queue *temp = (struct queue*)malloc(sizeof(struct queue));
		rear->next = temp;
		temp->araba = araba;
		node->siraNo = ++araba->talep_sayisi;
		temp->node = node;
		temp->next = NULL;
		rear = temp;
	}
	araba->musteri_sayisi++;
}

void dequeue() {
	struct queue *front_temp = front;
	if(front_temp == NULL) {
		printf("Kuyruk bos\n");
	}
	else {
		if(front_temp->next != NULL) {
			front_temp = front_temp->next;
			printSale(front->node,front->araba);
			free(front);
			front = front_temp;
		}
		else {
			printSale(front->node,front->araba);
			free(front);
			front = NULL;
			rear = NULL;
		}
	}
}

struct node *nodeOlustur(struct araba *araba){
	struct node *newNode = (struct node*)malloc(sizeof(struct node));
	strcpy(newNode->marka,araba->marka);
	strcpy(newNode->model,araba->model);
	strcpy(newNode->paket,araba->paket);
	strcpy(newNode->renk,araba->renk);
	strcpy(newNode->tip,araba->tip);
	newNode->fiyat = araba->fiyat;
	newNode->numara = musteriSiraNo;
	newNode->siraNo = araba->talep_sayisi;
	newNode->next = NULL;
	return newNode;
}

void ekleMusteri(struct araba *araba,int renkId){
	struct node* newNode = nodeOlustur(araba);
	strcpy(newNode->renk,renk[renkId]); 
	if(nodem == NULL){
		nodem = newNode;
	}
	else{
		struct node* temp = nodem;
		while(temp -> next != NULL){
			temp = temp -> next;
		}
		temp -> next = newNode;
	}
}

void musteriListele(){
	struct node *temp = nodem;
	if(temp == NULL){
		printf("Musteri bulunmamaktadir!\n");
		return;
	}
	while(temp != NULL){
		printf("%d. musteri araba marka: %s model :%s paket : %s renk: %s tip : %s fiyat :%d sira: %d\n",temp->numara,temp->marka,temp->model,temp->paket,temp->renk,temp->tip,temp->fiyat,temp->siraNo);
		temp = temp->next;
	}
}

void istatistikler(){
	struct araba *temp = firstAraba;
	while(temp != NULL){
		printf("%s %s %s arabasina talep sayisi %d\n",temp->marka,temp->model,temp->paket,temp->musteri_sayisi);
		temp = temp->next;
	}
}

void simulasyon(){
	if(firstAraba == NULL){
		printf("Listede araba bulunmamaktadir!\n");
		return;
	}
	int i,kisi,rastgele1,rastgele2;
	printf("Kac kisilik simulasyon yapilacaktir: ");
	scanf("%d",&kisi);
	int arabaSayi = arabaSayisi();
	struct araba *temp;
	for(i=1;i<=kisi;i++){
		rastgele1 = rand()%arabaSayi + 1;
		rastgele2 = rand()%N;
		temp = findAraba(rastgele1);
		enqueue(nodeOlustur(temp),temp,rastgele2);
		musteriSiraNo++;
		ekleMusteri(temp,rastgele2);
	}
	for(i=1;i<=kisi;i++){
		dequeue();
	}
	printf("\n-----------------------------------------\n");
	istatistikler();	
}

void anaMenu(){
	printf("\t\t\t\tARABA BAYIISI UYGULAMASINA HOS GELDINIZ!\n");
	printf("\t\t\t\t========================================\n");
	printf("\t\t\t\t============ BAYII MENUSU ==============\n");
	printf("\n\t\t\t\tARAC EKLE => 1");
	printf("\n\t\t\t\tARAC GUNCELLE => 2");
	printf("\n\t\t\t\tARAC SIL => 3");
	printf("\n\t\t\t\tARACLARI LISTELE => 4");
	printf("\n\t\t\t\tSATIS SIMULASYONU => 5");
	printf("\n\t\t\t\tMARKAYA GORE ARAMA => 6");
	printf("\n\t\t\t\tMARKA-MODELE GORE ARAMA => 7");
	printf("\n\t\t\t\tARABA TIPINE GORE ARAMA => 8");
	printf("\n\t\t\t\tFIYATA GORE ARAMA => 9");
	printf("\n\t\t\t\tFIYATINA GORE LISTELEME => 10");
	printf("\n\t\t\t\tMUSTERI LISTELEME => 11");
	printf("\n\t\t\t\tARABALARI TESLIM ET => 12");
	printf("\n\t\t\t\tCIKIS YAP => 0");
	printf("\n\t\t\t\t========================================\n");
		
	int secim;
	printf("\nLutfen gerceklestirmek istediginiz islemi seciniz: ");
	scanf("%d",&secim);
	
	int id;
	
	switch(secim)
	{
		case 1:
			system("CLS");
			printf("\n=>ARAC EKLE\n");
			printf("\n===========\n");
			arabaEkle();
			idNumaralariniGuncelle();
			printf("\n\n");
			break;
		case 2:
			system("CLS");
			printf("\n=>ARAC GUNCELLE\n");
			printf("\n===============\n");
			printf("Guncellemek istediginiz arabanin id ini giriniz: ");
			scanf("%d",&id);
			arabaGuncelle(id);
			printf("\n\n");
			break;
		case 3:
			system("CLS");
			printf("\n=>ARAC SIL");
			printf("\n==========\n");
			printf("silmek istediginiz arabanin id ini giriniz: ");
			scanf("%d",&id);
			arabaSil(id);
			idNumaralariniGuncelle();
			printf("\n\n");
			break;
		case 4:
			system("CLS");
			printf("\n=>ARABALARI LISTELE");
			printf("\n===================\n");
			printLinkedList();
			printf("\n\n");
			break;
		case 5:
			system("CLS");
			printf("\n=>SATIS SIMULASYONU");
			printf("\n===================\n");
			simulasyon();
			printf("\n\n");
			break;
		case 6:
			system("CLS");
			printf("\n=>MARKAYA GORE ARAMA");
			printf("\n====================\n");
			markaAra();
			printf("\n\n");
			break;
		case 7:
			system("CLS");
			printf("\n=>MARKA-MODELE GORE ARAMA");
			printf("\n=========================\n");
			markaModelAra();
			printf("\n\n");
			break;
		case 8:
			system("CLS");
			printf("\n=>ARABA TIPINE GORE ARAMA");
			printf("\n=========================\n");
			tipAra();
			printf("\n\n");
			break;
		case 9:
			system("CLS");
			printf("\n=>FIYATA GORE ARAMA");
			printf("\n===================\n");
			fiyatAra();
			printf("\n\n");
			break;
		case 10:
			system("CLS");
			printf("\n=>FIYATINA GORE LISTELEME");
			printf("\n=========================\n");
			createTree();
			printf("\n\n");
			break;
		case 11:
			system("CLS");
			printf("\n=>MUSTERI LISTELEME");
			printf("\n===================\n");
			musteriListele();
			printf("\n\n");
			break;
		case 12:
			system("CLS");
			printf("\n=>ARABALARI TESLIM ET");
			printf("\n=====================\n");
			printf("Hangi numaralý musteriye araba teslim edilecek veya listeden silinecektir: ");
			scanf("%d",&id);
			musteriSil(id);
			printf("\n\n");
			break;
		case 0:
			printf("\nCikis yaptiniz\n");
			break;
	}
	if(secim >= 1 && secim <13){
		anaMenu();
	}else if(!secim){
		return;
	}else{
		printf("Hata!!!!\n");
		anaMenu();
	}
}

int main(void){
	srand(time(NULL));
	printf("\n---------------------------------- YTCCAR ADMIN YONETIM PANELI  ----------------------------------\n\n");
	anaMenu();
}























