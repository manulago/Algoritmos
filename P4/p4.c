//TITULO: Práctica 4 de Algoritmos

//GRUPO: 3.2
//FECHA: 24/11/2022
//***********************************************************

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define TAM 512000
#define K 1000

typedef struct {
    int vector[TAM];
    int ultimo;
} monticulo;

void crear_monticulo(int v[], int n, monticulo *M);
int eliminar_mayor(monticulo *M);
void Hundir (monticulo *M, int i);
bool MonticuloVacio (monticulo *M); //tuve que cambiar para evitar segmentation fault
void inicializar_Monticulo(monticulo *M);
void print_heap(monticulo *M); //Segmentation fault si pasaba monticulo por parametros
void ascendente(int v[], int n);
void descendente(int v[], int n);
void aleatorio(int v[], int n);
double microsegundos();
void inicializar_semilla();
void test1();
void testCrearMonticulo();
void ord_monticulo(int v[],int n);
void test2();
void test3();
void testOrdMonticulo(void ini(int v[],int n));

int main() {
    inicializar_semilla();
    test1();
    testCrearMonticulo();
    test2();
    test3();
    return 0;
}

void test3(){
    printf("----------------------------------------------------------------");
    printf("\nAlgoritmo de Ordenacion por Monticulos\n");
    printf("----------------------------------------------------------------");
    printf("\nAscendente\n\n");
    printf("\tn\t\tt(n)\t      t(n)/n^0.8\t  t(n)/n*log(n)\t      t(n)/n^1.2");
    printf("\n");
    testOrdMonticulo(&ascendente);
    printf("----------------------------------------------------------------");
    printf("\nDescendente\n\n");
    printf("\tn\t\tt(n)\t      t(n)/n^0.8\t  t(n)/n*log(n)\t      t(n)/n^1.2");
    printf("\n");
    testOrdMonticulo(&descendente);
    printf("----------------------------------------------------------------");
    printf("\nAleatorio\n\n");
    printf("\tn\t\tt(n)\t      t(n)/n^0.8\t  t(n)/n*log(n)\t      t(n)/n^1.2");
    printf("\n");
    testOrdMonticulo(&aleatorio);
    printf("----------------------------------------------------------------");
    printf("\n");
}

void testOrdMonticulo(void ini(int v[],int n)){
    int i,j,v[TAM]; double ta,tb,t,t1,t2,sub,cot,sob;
    for(i=500;i<=512000;i*=2){
        ini(v,i);
        ta=microsegundos();
        ord_monticulo(v,i);
        tb=microsegundos(); t=tb-ta;
        if(t<500) {
            ta = microsegundos();
            for (j = 0; j < K; j++){
                ini(v,i);
                ord_monticulo(v,i);
            }
            tb = microsegundos(); t1=tb-ta;
            ta=microsegundos();
            for(j=0;j<K;j++) ini(v,i);
            tb=microsegundos(); t2=tb-ta;
            t = (t1 - t2) / (double) K;
            sub = t / (double) pow(i, 0.8);
            cot = t/(double)(i*log(i));
            sob = t / (double) pow(i, 1.2);
            printf("(*)%7d %17.3lf%20.7lf%22.7lf%18.7lf\n",
                   i,t,sub,cot,sob);
        }else{
            sub = t / (double) pow(i, 0.8);
            cot = t/(double)(i*log(i));
            sob = t / (double) pow(i, 1.2);
            printf("%10d %17.3lf%20.7lf%22.7lf%18.7lf\n",
                   i,t,sub,cot,sob);
        }
    }
}

void testCrearMonticulo(){
    int i,j,v[TAM]; monticulo M; double ta,tb,t,sub,cot,sob;
    printf("----------------------------------------------------------------");
    printf("\nCreacion monticulo de n elementos");
    printf("\n\tn\t\tt(n)\t      t(n)/n^0.8\t   t(n)/n^0.99\t      t(n)/n^1.2"
           "\t    t(n)/n\n");
    for(i=500;i<=512000;i*=2){
        ascendente(v,i);
        ta=microsegundos();
        crear_monticulo(v,i,&M);
        tb=microsegundos(); t=tb-ta;
        if(t<500) {
            ta = microsegundos();
            for (j = 0; j < K; j++) crear_monticulo(v, i, &M);
            tb = microsegundos();
            t = (tb - ta) / (double) K;
            sub = t / (double) pow(i, 0.8);
            cot = t / (double) pow(i,0.99);
            sob = t / (double) pow(i, 1.2);
            printf("(*)%7d %17.3lf%20.7lf%22.7lf%18.7lf%18.7lf\n",
                   i,t,sub,cot,sob,t/(double)i);
        }else{
            sub = t / (double) pow(i, 0.8);
            cot = t / (double) pow(i,0.99);
            sob = t / (double) pow(i, 1.2);
            printf("%10d %17.3lf%20.7lf%22.7lf%18.7lf%18.7lf\n",
                   i,t,sub,cot,sob,t/(double)i);
        }
    }
    printf("----------------------------------------------------------------");
    printf("\n");
}

void ord_monticulo(int v[],int n){
    int i; monticulo M;
    crear_monticulo(v,n,&M);
    for(i=n-1;i>=0;i--)
        v[i]= eliminar_mayor(&M);
}

void inicializar_Monticulo(monticulo *M){
    M->ultimo = -1;
}

void crear_monticulo(int v[], int n, monticulo *M){
    int i;
    for(i=0;i<n;i++)
        M->vector[i]=v[i];
    M->ultimo=n-1;
    for(i=n/2;i>=0;i--)
        Hundir(M,i+1);
}

void Hundir (monticulo *M, int i){
    int hijoder,hijoizq,j;
    do {
        hijoizq = 2 * i;
        hijoder = 2 * i + 1;
        j = i;
        if (hijoder <= M->ultimo+1 && M->vector[hijoder-1] > M->vector[i-1]) {
            i = hijoder;
        }
        if (hijoizq <= M->ultimo+1 && M->vector[hijoizq-1] > M->vector[i-1]) {
            i = hijoizq;
        }
        int aux = 0;
        aux = M->vector[i-1];
        M->vector[i-1] = M->vector[j-1];
        M->vector[j-1] = aux;
    }while(j != i);
}

int eliminar_mayor(monticulo *M){
    int x=-1;
    if (MonticuloVacio(M)){
        printf("Error: Montículo vacío");
    }else{
        x = M->vector[0];
        M->vector[0] = M->vector[M->ultimo];
        M->ultimo -= 1;
    } if (M->ultimo > -1){
        Hundir(M, 1);
    }return x;
}

bool MonticuloVacio (monticulo *M){
    return M->ultimo == -1;
}
void print_heap(monticulo *M){
    int i;
    printf("[");
    for(i=0;i<=M->ultimo;i++)
        printf(" %d ",M->vector[i]);
    printf("]\n");
}
void inicializar_semilla() {
    srand(time(NULL));
}
double microsegundos(){
    struct timeval t;
    if(gettimeofday(&t,NULL)<0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}
void ascendente(int v[], int n){
    int i;
    for (i=0; i < n; i++)
        v[i] = i;
}
void descendente(int v[], int n){
    int i;
    for (i=0; i<n; i++)
        v[i] = (n-1)-i;
}
void aleatorio(int v[], int n){
    int i, m=2*n +1;

    for(i=0; i < n; i++){
        v[i] = (rand() % m) - n;
    }
}

void test1(){
    printf("----------------------------------------------------------------");
    printf("\n");
    int v[25],i;
    monticulo M;
    printf("[");
    for(i=0;i<25;i++){
        v[i]=i-12;
        printf(" %d ",v[i]);
    }
    printf("]\n");
    inicializar_Monticulo(&M);
    crear_monticulo(v,25,&M);
    print_heap(&M);
    eliminar_mayor(&M);
    print_heap(&M);
    printf("----------------------------------------------------------------");
    printf("\n");
}
void test2(){
    printf("----------------------------------------------------------------");
    int i,n=25,v[n];
    for(i=n;i>=0;i--)
        v[n-i]=i-n/2-1;
    printf("\nVector ordenado descendentemente:\n[");
    for(i=0;i<n;i++)
        printf(" %d ",v[i]);
    printf("]\nVector ordenado mediante Ordenacion por monticulos\n[");
    ord_monticulo(v,n);
    for(i=0;i<n;i++)
        printf(" %d ",v[i]);
    printf("]\n");
    printf("----------------------------------------------------------------");
    printf("\n");
}
