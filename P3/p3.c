//TITULO: Práctica 3 de Algoritmos

//GRUPO: 3.2
//FECHA: 07/11/2022
//***********************************************************

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define K 100

struct nodo {
    int elem;
    int num_repeticiones;
    struct nodo *izq, *der;
};
typedef struct nodo *posicion;
typedef struct nodo *arbol;

void inicializar_semilla();
void aleatorio(int v[], int n);
double microsegundos();

static struct nodo *crearNodo(int e);
arbol insertar(int e, arbol a);
arbol creararbol();
int esarbolvacio(arbol);
posicion buscar(int, arbol);
arbol eliminararbol(arbol);
posicion hijoizquierdo(arbol);
posicion hijoderecho(arbol);
int elemento(posicion);
int numerorepeticiones(posicion);
int altura(arbol a);
void visualizar(arbol a);
void testfunctions();
arbol meditions(int select,int i,int indice,arbol a,double vi[],double vb[]);
void controlmed();

int main(){
    inicializar_semilla();
    printf("----------------------------------------------------------------");
    testfunctions();
    controlmed();
    controlmed();
    controlmed();
    return 0;
}
void controlmed(){
    int i,elems=7,indice,max=elems*2; double vi[max],vb[max],sub,cot,sob;
    printf("----------------------------------------------------------------");
    for(i=8000,indice=0;indice<max;i*=2,indice+=2){
        arbol a=creararbol();
        a= meditions(0,i,indice,a,vi,vb);
        meditions(1,i,indice,a,vi,vb);
    }
    printf("\n\t     n\t\tt_ins(n)\tt_bus(n)\n");
    for(i=8000,indice=0;indice<max;i*=2,indice+=2)
        printf("\t%6d%18.3f%16.3f\n",i,vi[indice],vb[indice]);
    printf("----------------------------------------------------------------");
    printf("\nInserción de n elementos");
    printf("\n\tn\t\tt(n)\t      t(n)/n^1.06\t   t(n)/n^1.23\t      t(n)/n^1.4"
           "      t(n)/nlog(n)\n");
    for(i=8000,indice=0;indice<max;i*=2,indice+=2){
        sub=vi[indice]/(double)(pow(i,1.06));
        cot=vi[indice]/(double)pow(i, 1.23);
        sob=vi[indice]/(double)(pow(i,1.4));
        if(vi[indice+1]==1)
            printf("(*)%7d %17.3lf%20.7lf%22.7lf%18.7lf%18.7lf\n",
                   i,vi[indice],sub,cot,sob,vi[indice]/(double)(i*log(i)));
        else
            printf("%10d %17.3lf%20.7lf%22.7lf%18.7lf%18.7lf\n",
                   i,vi[indice],sub,cot,sob,vi[indice]/(double)(i*log(i)));
    }
    printf("----------------------------------------------------------------");
    printf("\nBúsqueda de n elementos");
    printf("\n\tn\t\tt(n)\t      t(n)/n^0.98\t   t(n)/n^1.23\t      t(n)/n^1.4"
           "      t(n)/nlog(n)\n");
    for(i=8000,indice=0;indice<max;i*=2,indice+=2){
        sub=vb[indice]/(double)(pow(i,0.98));
        cot=vb[indice]/(double)pow(i, 1.23);//1.187);
        sob=vb[indice]/(double)(pow(i,1.4));
        if(vb[indice+1]==1)
            printf("(*)%7d %17.3lf%20.7lf%22.7lf%18.7lf%18.7lf\n",
                   i,vb[indice],sub,cot,sob,vi[indice]/(double)(i*log(i)));
        else
            printf("%10d %17.3lf%20.7lf%22.7lf%18.7lf%18.7lf\n",
                   i,vb[indice],sub,cot,sob,vb[indice]/(double)(i*log(i)));
    }
    printf("----------------------------------------------------------------");
    printf("\n");
}
//select 0 -> insert / select 1 -> search
arbol meditions(int select,int i,int indice,arbol a,double vi[],double vb[]){
    int v[i],j,k; double ta,tb,t,t1,t2; arbol b;
    if(select==0){
        aleatorio(v,i); a=creararbol();
        ta=microsegundos();
        for(j=0;j<i;j++) a=insertar(v[j],a);
        tb=microsegundos();
        t=tb-ta; vi[indice]=t; vi[indice+1]=0;
        if(t<500){
            /*a= eliminararbol(a);*/ ta=microsegundos(); //Mismo numero de eliminaciones
            for(j=0;j<K;j++){
                a= eliminararbol(a);
                aleatorio(v,i);
                for(k=0;k<i;k++) a=insertar(v[k],a);
            } tb=microsegundos(); t1=tb-ta; b=creararbol();
            for(j=0;j<K;j++)
                {aleatorio(v,i); for(k=0;k<i;k++) b= insertar(v[k],b);}
            ta=microsegundos();
            eliminararbol(b); for(j=0;j<K;j++) aleatorio(v,i);
            tb=microsegundos(); t2=tb-ta; t=(t1-t2)/(double)K;
            vi[indice]=t; vi[indice+1]=1;
        }return a;
    }else{
        aleatorio(v,i);
        ta=microsegundos();
        for(j=0;j<i;j++) buscar(v[j],a);
        tb=microsegundos();
        t=tb-ta; vb[indice]=t; vb[indice+1]=0;
        if(t<500){
            ta=microsegundos();
            for(j=0;j<K;j++){
                aleatorio(v,i);
                for(k=0;k<i;k++) buscar(v[k],a);
            }
            tb=microsegundos(); t1=tb-ta;
            ta=microsegundos(); for(j=0;j<K;j++) aleatorio(v,i);
            tb=microsegundos(); t2=tb-ta; t=(t1-t2)/(double)K;
            vb[indice]=t; vb[indice+1]=1;
        } return eliminararbol(a);
    }
}

static struct nodo *crearNodo(int e){
    struct nodo *p = malloc(sizeof(struct nodo));
    if (p==NULL){
        printf("Memoria agotada\n");
        exit(EXIT_FAILURE);
    }
    p->elem=e;
    p->num_repeticiones=1;
    p->izq=NULL;
    p->der=NULL;
    return p;
}

arbol insertar(int e, arbol a){
    if (a == NULL){
        return crearNodo(e);
    }else if (e< a->elem){
        a->izq = insertar (e,a->izq);
    }else if (e > a->elem){
        a->der = insertar (e, a->der);
    }else{
        a->num_repeticiones++;
    }
    return a;
}

arbol creararbol(){
    return NULL;
}
int esarbolvacio(arbol a){
    return a == NULL;
}
posicion buscar(int e, arbol a){
    if (esarbolvacio(a)){
        return NULL;
    }else if (e == elemento(a)) {
        return a;
    }else if (e < elemento(a))
        return buscar(e, hijoizquierdo(a));
    else return buscar(e, hijoderecho(a));
}

arbol eliminararbol(arbol a) {
    if (a == NULL) {
        return a;
    } else {
        if (hijoizquierdo(a) != NULL) {
            a->izq = eliminararbol(hijoizquierdo(a));
        }
        if (hijoderecho(a) != NULL) {
            a->der = eliminararbol(hijoderecho(a));
        }
        free(a);
        return NULL;
    }
}

int numerorepeticiones(posicion p){
    return p->num_repeticiones;
}

posicion hijoizquierdo (arbol a){
    return a->izq;
}
posicion hijoderecho(arbol a){
    return a->der;
}

int altura (arbol a) {
    int aizq,ader;
    if (esarbolvacio(a))
        return -1;
    else if(esarbolvacio(hijoizquierdo(a))&& esarbolvacio(hijoderecho(a))){
        return 0;
    }else{
        aizq=altura(hijoizquierdo(a));
        ader=altura(hijoderecho(a));
        if(aizq>ader) return 1+aizq;
        else return 1+ader;
    }
}

int elemento(posicion p){
    return p->elem;
}

void visualizar(arbol a){
    if (!esarbolvacio(a)) {
        if(!esarbolvacio(hijoizquierdo(a))){
            printf("(");
            visualizar(hijoizquierdo(a));
            printf(")");
        }
        printf(" %d ", a->elem);
        if(!esarbolvacio(hijoderecho(a))){
            printf("(");
            visualizar(hijoderecho(a));
            printf(")");
        }
    }else printf("()");
}

void testfunctions(){
    int i,numr;posicion busc;
    arbol a = creararbol();
    printf("\narbol vacio: ");
    visualizar(a);
    printf("\naltura del arbol: %d\n", altura(a));
    a = insertar(3,a);
    a = insertar(1,a);
    a = insertar(2,a);
    a = insertar(5,a);
    a = insertar(4,a);
    a = insertar(5,a);
    printf("inserto un 3\ninserto un 1\ninserto un 2\n");
    printf("inserto un 5\ninserto un 4\ninserto un 5\n");
    visualizar(a);
    printf(".");
    printf("\naltura del arbol: %d\n", altura(a));
    for(i=1;i<7;i++){
        busc = buscar(i,a);
        if(busc==NULL) numr=0; else numr= numerorepeticiones(busc);
        printf("busco %d -> repetido %d veces\n",i,numr);
    }
    printf("borro todos los nodos liberando la memoria:\n");
    a = eliminararbol(a);
    printf("arbol vacio: ");
    visualizar(a);
    printf(".");
    printf("\naltura del arbol: %d\n", altura(a));
}

void inicializar_semilla() {
    srand(time(NULL));
}
void aleatorio(int v[], int n){
    int i, m=2*n +1;

    for(i=0; i < n; i++){
        v[i] = (rand() % m) - n;
    }
}
double microsegundos(){
    struct timeval t;
    if(gettimeofday(&t,NULL)<0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
