/*

 ============================================================================

 Name        : AlgoMqm0.c

 Author      : Muhammad Alhadi B.

 Version     :

 Copyright   : Your copyright notice

 Description : TP_Algo in C, ANSI-style

 ============================================================================

 */





#include <stdio.h>

#include <stdlib.h>



#define True 1

#define False 0

#define Exist 1

#define Stop 1

#define Marked 1

#define NotMarked 0





typedef struct node node;

struct node{

    int valor;

    node *next;

}typedef *list;



typedef struct Summit Summit;

struct Summit{

    int Valor,Mark;

    list Successor;

    Summit *Next;

}typedef *Graph;





/*

 *

 */

void creaG(Graph *G);

void creaS(list *l);

void Display(Graph G);

void Search(Graph G,int X);

void addSummit(Graph *G,int sumVal);

void addArc(Graph *G,int sValor,int arcValor);

void creArcDiv(Graph *G,int sumDep,int sumArr);

void delLoops(Graph *G);

int wayEx(Graph G,int Dep,int Arr);

Graph SearchFct(Graph G,int X);

list loopEx(Graph G,int sumValor);

int Circuit(Graph G,int Dep);

void Enqueue(list *Queue,int qValor);

void Dequeue(list *Queue,int *qValor);

int SearchElt(list L,int X);

void initMarks(Graph *G);

int IWE(Graph G,int Dep,int Arr);

/*

 *

 */

int main(int argc, char** argv) {

	Graph Graph= NULL ,Result= NULL;

	list S;

	int X,sumDep,sumArr;

	int Choice;

    do{

    	puts("\n\n\n");

    	puts("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-");

    	puts("\t\t=====Welcome=====\n");

    	puts("1.Create a Graph");

    	puts("2.Search a Summit");

    	puts("3.Search a Summit & return it");

    	puts("4.Add new ARC");

    	puts("5.Test of a WAY EXISTENCE");

    	puts("6.Test of a CIRCUIT");

    	puts("7.Add ARCS with condition");

    	puts("8.Test of a LOOP EXISTENCE");

    	puts("9.Deleting all loops in Graph");

    	puts("10.Add Summit");

    	puts("11.Display");

    	puts("12.Test of an INDIRECT WAY EXISTENCE");

    	puts("0.|_E_X_I_T_|");

    	puts("-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-");

    	scanf("%d",&Choice);

    	switch(Choice){

    	case 1:{

    		creaG(&Graph);

    	        }break;

    	case 2:{

    		puts("What are you searching for?");

    		scanf("%d",&X);

    		Search(Graph,X);

    	    	}break;

    	case 3:{

    		puts("What are you searching for?");

    		scanf("%d",&X);

    		Result= SearchFct(Graph,X);

    		if(Result!=NULL){

    			printf("{%d}-->\t",Result->Valor);

    			            if(Result->Successor!=NULL){S= Result->Successor;

    						while(S!=NULL){

    							printf("=[%d]=\t",S->valor);

    							S= S->next;

    						}

    						printf("\n");}

    		}

    		else puts("N0T F0UND :(");

    	    	}break;

    	case 4:{

    		int nArc,SnArc;

    		puts("The new ARC will be: ");

    		scanf("%d",&nArc);

    		puts("It will be in which Summit: ");

    		scanf("%d",&SnArc);

            addArc(&Graph,SnArc,nArc);

            puts("You can now Display the Graph to show the change.....");

    	    	}break;

    	case 5:{

    		int first,second,Check;

    		puts("Test the existence between?");

    		puts("Enter two summits....");

    		scanf("%d",&first);

    		scanf("%d",&second);

    		Check= wayEx(Graph,first,second);

            if(Check==0)puts("There's no way:(");

            else if(Check==1)printf("Yes there's a way from {%d} to {%d}",first,second);

            else if(Check==2)printf("Yes there's a way but from {%d} to {%d}",second,first);

    	    	}break;

    	case 6:{

    		int Departure;

    		int Answa;

    		initMarks(&Graph);

    		puts("Put the departure valor:");

    		scanf("%d",&Departure);

    		Answa= Circuit(Graph,Departure);

            if(Answa==True)puts("There's a CIRCUIT");

            else puts("There's not a CIRCUIT");

    	    	}break;

    	case 7:{

    		puts("Enter the departure summit:");

    		scanf("%d",&sumDep);

    		puts("Enter the arrival summit:");

    		scanf("%d",&sumArr);

    		creArcDiv(&Graph,sumDep,sumArr);

    		Display(Graph);

    	    	}break;

    	case 8:{

    		int sumCheck;

    		list reply;

    		puts("Enter a Summit to check!");

    		scanf("%d",&sumCheck);

    		reply= loopEx(Graph,sumCheck);

    		if(reply!=NULL)puts("There's a loop Here :D");

    		else puts("There's not a loop Here :D");

    	    	}break;

    	case 9:{

    		puts("We're here about deleting all loops in our Graph....");

    		delLoops(&Graph);

    		puts("It's done you can Display & verify by yourself ;)");

    	    	}break;

    	case 10:{

    		int sumVal;

    		puts("sumVal:");

    		scanf("%d",&sumVal);

    		addSummit(&Graph,sumVal);

    		Display(Graph);

    	    	}break;

    	case 11:{

    		Display(Graph);

    	        }break;

    	case 12:{

    		int Dep,Arr,Result;

    		initMarks(&Graph);

    		puts("Departure?");

    		scanf("%d",&Dep);

    		puts("Arrival?");

    		scanf("%d",&Arr);

    		Result= IWE(Graph,Dep,Arr);

    		if(Result==True)puts("There's a WAY");

    		else puts("There's not a WAY");

    	        }break;

    	}

    }while(Choice!=0);



    return (EXIT_SUCCESS);

}



//Summit Creation

void creaG(Graph *G){

	int loop,N;

	char Answ;

	Graph QueueG,Gr;

	list L;

	(*G)=NULL;

    printf("How many of Summits?\n");

    scanf("%d",&N);

    for(loop=1;loop<=N;++loop){

    	if((*G)==NULL){

    		(*G)=(Graph)malloc(sizeof(Summit));

    		printf("Enter Summit N°%d",loop);

    		scanf("%d",&(*G)->Valor);

    		(*G)->Mark= NotMarked;

    		(*G)->Next= NULL;

    		QueueG= (*G);

    		printf("Wanna Create Successors O/N?\n");

    		Answ= getchar();

    		scanf("%c",&Answ);

    		if(Answ=='O'){

    			creaS(&L);

    			(*G)->Successor= L;

    		}

    		else (*G)->Successor= NULL;

    	}

    	else{

    		Gr=(Graph)malloc(sizeof(Summit));

    		printf("Enter Summit N°%d",loop);

    		scanf("%d",&Gr->Valor);

    		Gr->Next= NULL;

    		QueueG->Next= Gr;

    		QueueG= Gr;

    		printf("Wanna Create Successors O/N?\n");

    		getchar();

    		scanf("%c",&Answ);

    		if(Answ=='O'){

    		creaS(&L);

    		Gr->Successor= L;

    		}

    		else Gr->Successor= NULL;

    	}



    }

}



//Successors Creation

void creaS(list *l){

	int loop,N;

	list Queue,L;

	(*l)= NULL;

    printf("How many of Successors do you wanna create?\n");

    scanf("%d",&N);

    for(loop=1;loop<=N;++loop){

    	if((*l)==NULL){

    		(*l)=(list)malloc(sizeof(node));

    		printf("Enter Successor N°%d",loop);

    		scanf("%d",&(*l)->valor);

    		(*l)->next= NULL;

    		Queue= (*l);

    	}

    	else{

    		L=(list)malloc(sizeof(node));

    		printf("Enter Successor N°%d",loop);

    		scanf("%d",&L->valor);

    		L->next= NULL;

    		Queue->next= L;

    		Queue= L;

    	}

    }

}



//Display

void Display(Graph G){

	Graph Queue= G;list S;

	while(Queue!= NULL){

		printf("{%d}-->\t",Queue->Valor);

            if(Queue->Successor!=NULL){S= Queue->Successor;

			while(S!=NULL){

				printf("=[%d]=\t",S->valor);

				S= S->next;

			}

			printf("\n");

            }else printf("\n");



		Queue= Queue->Next;

	}

}

//Searching For Element 'X'

void Search(Graph G,int X){

	int Indice= 1,found= False;

	while((G!= NULL)&&(found!= True)){

		if(G->Valor== X){

			printf("Summit N°%d is the result which is: %d",Indice,G->Valor);

			found= True;

		}

	    G= G->Next;

		++Indice;

	}

	if(found==False) printf("Sorry Element not found!!\n");

}



//Add new Summit

void addSummit(Graph *G,int sumVal){

	//char Answ;

	Graph Gr,Queue;

	//list L;

		Gr=(Graph)malloc(sizeof(Summit));

	    		Gr->Valor= sumVal;

	    		Gr->Next= NULL;

	    	/*	printf("Wanna Create Successors O/N?\n");

	    		getchar();

	    		scanf("%c",&Answ);

	    		if(Answ=='O'){

	    		creaS(&L);

	    		Gr->Successor= L;

	    		}

	    		else Gr->Successor= NULL;*/

	    		if((*G)==NULL)

	    			(*G)= Gr;

	    		else {

	    			Queue= (*G);

	    			while(Queue->Next!= NULL){

	    				Queue= Queue->Next;

	    			}Queue->Next= Gr;

	    		}

}



//Add new Arc

void addArc(Graph *G,int sValor,int arcValor){

	Graph QueueG,pointer,pntr=(*G),pntr2=(*G);

	list QueueL,L;

	int Check= False;

	L=(list)malloc(sizeof(node));

	L->valor= arcValor;

	L->next= NULL;

	if((*G)==NULL) printf("0p::Impossible!!\n");

	else{

		QueueG= (*G);

		while((QueueG!= NULL)&&(Check==False)){

			if((sValor==QueueG->Valor)&&(QueueG->Successor==NULL)){

				QueueG->Successor= L;

				Check= True;

			}

			else if ((sValor==QueueG->Valor)&&(QueueG->Successor!=NULL)){

				QueueL= QueueG->Successor;

				while(QueueL->next!=NULL){

					QueueL= QueueL->next;

				}QueueL->next= L;

				Check= True;

			}

			QueueG= QueueG->Next;

		}

	}

	if(Check==False){

		addSummit(&(*G),sValor);

		pointer= SearchFct(pntr,sValor);

		pointer->Successor= L;

		pointer= NULL;

	}

	pointer= SearchFct(pntr2,arcValor);

	if(pointer==NULL) addSummit(&(*G),arcValor);

	}





//Search.....

Graph SearchFct(Graph G,int X){

	int found= False;

	Graph sumSrchd,QueueG;

	if(G==NULL) return NULL;

	else{

		QueueG= (G);

		while((QueueG!=NULL)&&(found!=True)){

			if(QueueG->Valor==X){

				sumSrchd= QueueG;

				found= True;

			}

			QueueG= QueueG->Next;

		}return sumSrchd;

	}

}



//Circuit.....

int Circuit(Graph G,int Dep){

	Graph auX,pointerG;

	list Queue,pointerL;

	int ansW= False,elt2Check,list2Check,Test= False;

	auX= SearchFct(G,Dep);

	if(auX==NULL){

		puts("There's no Summit");

		ansW= False;

	}

	else{

		auX->Mark= Marked;

		pointerL=auX->Successor;

		while(pointerL!= NULL){

			Enqueue(&Queue,pointerL->valor);

			pointerL= pointerL->next;

		}

		while(Test!= True){

			Dequeue(&Queue,&elt2Check);

			pointerG= SearchFct(G,elt2Check);

			if(pointerG->Mark!=Marked){

			pointerG->Mark= Marked;

			list2Check= SearchElt(pointerG->Successor,Dep);

			if(list2Check==Exist){

				Test= True;

				ansW= True;

			}

			else{

				pointerL= pointerG->Successor;

				while(pointerL!=NULL){

					Enqueue(&Queue,pointerL->valor);

					pointerL= pointerL->next;

				}

			}

			if(Queue==NULL)	Test= True;

			}

			else Test= True;

		}

	}



	return ansW;

}





//Create arcs such as the are divisors of their summits

void creArcDiv(Graph *G,int sumDep,int sumArr){

	Graph Dep,Arr;

	Graph pointer= (*G);

	Dep= SearchFct(*G,sumDep);

	if (Dep==NULL) addSummit(&(*G),sumDep);

	Arr= SearchFct(pointer,sumArr);

	if (Arr==NULL) addSummit(&(*G),sumArr);

	if ((sumDep % sumArr)==0) addArc(&*G,sumDep,sumArr);

	if ((sumArr % sumDep)==0) addArc(&*G,sumArr,sumDep);

}



//Does loop exist???

list loopEx(Graph G,int sumValor){

	list check= NULL,auxL;

	Graph auxG= G;

	if(auxG==NULL) check= NULL;

	else {

		while(auxG!=NULL){

			auxL=auxG->Successor;

			if(auxG->Valor==sumValor){

				if(auxL==NULL) check= NULL;

				else {

					while(auxL!=NULL){

						if(auxL->valor==auxG->Valor) check= auxG->Successor;

						auxL= auxL->next;

					}

				}

			}

			auxG= auxG->Next;

		}

	}

	return check;

}



//Does exist a way???

int wayEx(Graph G,int Dep,int Arr){

	int Check= 0;

	int ifExist=0;

	list S1,S2;

	Graph Head1= G,Head2= G;

	if(G==NULL) Check= 0;

	else{

		while((Head1!=NULL)&&(ifExist!=Exist)){

			if(Head1->Valor==Dep){

				if(Head1->Successor!=NULL){

					S1=Head1->Successor;

					while(S1!=NULL){

						if(S1->valor==Arr) {

							Check= Exist;

							ifExist= Exist;

				}S1= S1->next;

				}

				}

			}Head1= Head1->Next;

		}

		while((Head2!=NULL)&&(ifExist==0)){

					if(Head2->Valor==Arr){

						if(Head2->Successor!=NULL){

							S2= Head2->Successor;

							while(S2!=NULL){

								if(S2->valor==Dep) {

									Check= 2;

									ifExist= Exist;

						}S2= S2->next;

						}

						}

					}Head2= Head2->Next;

				}

	}



	return Check;

}



//Deleting loops

void delLoops(Graph *G){

	Graph pointer= (*G),Gr;

	list ifExist,Indice1,Indice2;

 	int GrVal;

	Indice1=(list)malloc(sizeof(node));

	Indice2=(list)malloc(sizeof(node));

	while(pointer!=NULL){

		Gr= pointer;

		GrVal= pointer->Valor;

		ifExist= loopEx(Gr,GrVal);

		if(ifExist!=NULL){

			Indice1= pointer->Successor;

			if(Indice1->valor==pointer->Valor){

				pointer->Successor= Indice1->next;

				free(Indice1);

			}

			else{

				Indice2= Indice1;

				while((Indice2->next!=NULL)&&(Indice2->next->valor!=pointer->Valor)){

					Indice2= Indice2->next;

				}

				Indice1= Indice2;

				Indice2= Indice2->next;

				if(Indice2->next==NULL){

					Indice1->next= NULL;

					free(Indice2);

				}

				else{

					Indice1->next= Indice2->next;

					free(Indice2);

				}

			}

		}pointer= pointer->Next;

	}



}



//Enqueue......

void Enqueue(list *Queue,int qValor){

	list pointer= (*Queue),aux;

	aux=(list)malloc(sizeof(node));

	aux->valor= qValor;

	aux->next= NULL;

	if(pointer==NULL){

		*Queue= aux;

		}

	else{

		while(pointer->next!=NULL){

			pointer= pointer->next;

		}pointer->next= aux;

		pointer= aux;

		}

}



//Dequeue......

void Dequeue(list *Queue,int *qValor){

	list pointer;

	if((*Queue)==NULL) puts("Impossible Queue's empty");

	else{

		(*qValor)= (*Queue)->valor;

		pointer= (*Queue);

		(*Queue)= (*Queue)->next;

		free(pointer);

	}

}



//Searching for Element on lists.....

int SearchElt(list L,int X){

	int found= False,eltSrchd;

	list QueueG;

	if(L==NULL) eltSrchd= 0;

	else{

		QueueG= (L);

		while((QueueG!=NULL)&&(eltSrchd!=Exist)){

			if(QueueG->valor==X){

				eltSrchd= Exist;

			}

			QueueG= QueueG->next;

		}

	}return eltSrchd;

}



//Initializing Marks

void initMarks(Graph *G){

	Graph initMark= (*G);

	while(initMark!=NULL){

				initMark->Mark= NotMarked;

				initMark= initMark->Next;

			}

}



//Indirect Way Existence .....

int IWE(Graph G,int Dep,int Arr){

	Graph auX,pointerG;

		list Queue,pointerL;

		int ansW= False,elt2Check,list2Check,Test= False;

		auX= SearchFct(G,Dep);

		if(auX==NULL){

			puts("There's no Summit");

			ansW= False;

		}

		else{

			auX->Mark= Marked;

			list2Check= SearchElt(auX->Successor,Arr);

			if(list2Check==Exist){

								Test= True;

								ansW= True;

							}

			else{

				pointerL=auX->Successor;

				while(pointerL!= NULL){

				Enqueue(&Queue,pointerL->valor);

				pointerL= pointerL->next;

			}

			}

			while(Test!= True){

				Dequeue(&Queue,&elt2Check);

				pointerG= SearchFct(G,elt2Check);

				if(pointerG->Mark!=Marked){

				pointerG->Mark= Marked;

				if(pointerG->Successor!=NULL){

					list2Check= SearchElt(pointerG->Successor,Arr);

									if(list2Check==Exist){

										Test= True;

										ansW= True;

									}

									else{

										pointerL= pointerG->Successor;

										while(pointerL!=NULL){

											Enqueue(&Queue,pointerL->valor);

											pointerL= pointerL->next;

										}

									}

				}

				if(Queue==NULL)	Test= True;

				}

				else Test= True;

			}

		}



		return ansW;

}



///
