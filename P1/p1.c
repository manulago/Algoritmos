//TITULO: Práctica 1 de Algoritmos

//GRUPO: 3.2
//FECHA: 20/09/2022
//***********************************************************

#include <stdio.h>
#include <sys/time.h>
#include <math.h>

#define N 10000

int fib1(int n){
	if(n<2)
		return n;
	else
		return fib1(n-1)+fib1(n-2);
}

int fib2(int n){
	int i=1,j=0,k;
	for(k=1;k<=n;k++){
		j=i+j;
		i=j-i;
	}
	return j;
}

int fib3(int n){
	int i=1,j=0,k=0,h=1,t=0;
	while(n>0){
		if(n%2!=0){
			t=j*h;
			j=i*h+j*k+t;
			i=i*k+t;
		}
		t=h*h;
		h=2*k*h+t;
		k=k*k+t;
		n=n/2;

	}
	return j;
}


void tfib1(){
	struct timeval st, et;
	int i,j;
	float elapsed,sub,cot,sob;
	printf("Fibonacci 1\n");
	printf("\t\tn\t\tt(n)\tt(n)/1.1^n\tt(n)/1.61^n       t(n)/2^n\n");
	for(i=2;i<=32;i=i*2){
		gettimeofday(&st,NULL);
		fib1(i);
		gettimeofday(&et,NULL);
    	elapsed = ((et.tv_sec-st.tv_sec) * 1000000) + (et.tv_usec-st.tv_usec);
    	if(elapsed<500.000){
    		elapsed=0.000;
    		for(j=0;j<N;j++){
    			gettimeofday(&st,NULL);
				fib1(i);
				gettimeofday(&et,NULL);
    			elapsed+=((et.tv_sec-st.tv_sec)*1000000)+(et.tv_usec-st.tv_usec);
    		}
    		elapsed = elapsed/N;;
    		sub=elapsed/(float)pow(1.1,i);
    		cot=elapsed/(float)pow(1.61,i);
    		sob=elapsed/(float)pow(2,i);
    		printf("(*)%14d%19.3f%14.6f%16.6f%16.6f\n",i,elapsed,sub,cot,sob);
    	}
    	else{
    		sub=elapsed/(float)pow(1.1,i);
    		cot=elapsed/(float)pow(1.61,i);
    		sob=elapsed/(float)pow(2,i);
    		printf("%17d%19.3f%14.6f%16.6f%16.6f\n",i,elapsed,sub,cot,sob);
    	}
	}
}
void tfib2(){
	struct timeval st, et;
	int i,j;
	float elapsed,sub,cot,sob;
	printf("Fibonacci 2\n");
	printf("\t\tn\t\tt(n)\tt(n)/n^0.8          t(n)/n\tt(n)/n*log(n)\n");
	for(i=1000;i<=10000000;i=i*10){
		gettimeofday(&st,NULL);
		fib2(i);
		gettimeofday(&et,NULL);
    	elapsed = ((et.tv_sec-st.tv_sec) * 1000000) + (et.tv_usec-st.tv_usec);
    	if(elapsed<500.000){
    		elapsed=0.000;
    		for(j=0;j<N;j++){
    			gettimeofday(&st,NULL);
				fib2(i);
				gettimeofday(&et,NULL);
    			elapsed+=((et.tv_sec-st.tv_sec)*1000000)+(et.tv_usec-st.tv_usec);
    		}
    		elapsed = elapsed/N;;
    		sub=elapsed/(float)pow(i,0.8);
    		cot=elapsed/(float)i;
    		sob=elapsed/(float)(i*log(i));
    		printf("(*)%14d%19.3f%14.6f%16.6f%16.6f\n",i,elapsed,sub,cot,sob);
    	}
    	else{
    		sub=elapsed/(float)pow(i,0.8);
    		cot=elapsed/(float)i;
    		sob=elapsed/(float)(i*log(i));
    		printf("%17d%19.3f%14.6f%16.6f%16.6f\n",i,elapsed,sub,cot,sob);
    	}
	}
}
void tfib3(){
	struct timeval st, et;
	int i,j;
	float elapsed,sub,cot,sob;
	printf("Fibonacci 3\n");
	printf("\t\tn\t\tt(n)\tt(n)/sq(log n)\tt(n)/log(n)\tt(n)/n^0.5\n");
	for(i=1000;i<=10000000;i=i*10){
		gettimeofday(&st,NULL);
		fib3(i);
		gettimeofday(&et,NULL);
    	elapsed = ((et.tv_sec-st.tv_sec) * 1000000) + (et.tv_usec-st.tv_usec);
    	if(elapsed<500.000){
    		elapsed=0.000;
    		for(j=0;j<N;j++){
    			gettimeofday(&st,NULL);
				fib3(i);
				gettimeofday(&et,NULL);
    			elapsed+=((et.tv_sec-st.tv_sec)*1000000)+(et.tv_usec-st.tv_usec);
    		}
    		elapsed = elapsed/N;;
    		sub=elapsed/(float)sqrt(log(i));
    		cot=elapsed/(float)log(i);
    		sob=elapsed/(float)pow(i,0.5);
    		printf("(*)%14d%19.3f%14.6f%16.6f%16.6f\n",i,elapsed,sub,cot,sob);
    	}
    	else{
    		sub=elapsed/(float)sqrt(log(i));
    		cot=elapsed/(float)log(i);
    		sob=elapsed/(float)pow(i,0.5);
    		printf("%17d%19.3f%14.6f%16.6f%16.6f\n",i,elapsed,sub,cot,sob);
    	}
	}
}
void initialtest(){
	int i;
	printf("  n    fibonacci_1   fibonacci_2   fibonacci_3\n");
    for(i=0;i<=10;i++){
        printf("%3d %8d %14d %13d\n",i,fib1(i),fib2(i),fib3(i));
    }
    printf("\n\t\t\t******************************\n");
}
void test(){
	tfib1();
	tfib2();
	tfib3();
}

int main(){
	initialtest();
	test();
	printf("\n\t\t\t******************************\n");
	test();
	printf("\n\t\t\t******************************\n");
	test();
	return 0;
}
