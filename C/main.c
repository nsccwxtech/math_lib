#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
//#include "lapack.h""
	
int M,N,K;
M=512;
N=256;
K=128;
void timer_start(struct timeval *);
void timer_end(double *,struct timeval *);

void timer_start(struct timeval *timev)
{
    gettimeofday(timev, 0L);
}
void timer_start_(struct timeval *timev)
{
    gettimeofday(timev, 0L);
}
void timer_end(double *sec,struct timeval *timev)
{
    struct timeval t;

    gettimeofday(&t, 0L);
    *sec = 1e6*(t.tv_sec-timev->tv_sec) + 1*(t.tv_usec-timev->tv_usec);
}
void timer_end_(double *sec,struct timeval *timev)
{
    struct timeval t;

    gettimeofday(&t, 0L);
    *sec = 1e6*(t.tv_sec-timev->tv_sec) + 1*(t.tv_usec-timev->tv_usec);
}
void rpcc(unsigned long *counter)
{
        unsigned long rpcc;
        asm("rtc %0": "=r" (rpcc) : );
        *counter=rpcc;
}
main()
{
double A[M][N];
double B[N][K];
double C[M][K];
double C1[M][K];
int i,j,k;
unsigned long st1,st2,st3,st4;
double alphe,beta;
char Trana,Tranb;
	struct timeval t1_start;
	double t1; 
Trana='N';
Tranb='N';
alphe=1.0;
beta=1.0;
for(i=0;i<M;i++){
for(j=0;j<N;j++){
        A[i][j]=i/50.0+j/40.0;
}
}

for(i=0;i<N;i++){
for(j=0;j<K;j++){
         B[i][j]=i/20.0+j/50.0;
}
}

for(i=0;i<M;i++){
for(j=0;j<K;j++){
         C[i][j]=1.0;
         C1[i][j]=1.0;
}
}
	rpcc(&st1);
for(i=0;i<M;i++){
for(k=0;k<K;k++){
for(j=0;j<N;j++){
        C[i][k]=C[i][k]+A[i][j]*B[j][k];
}
}
}
	rpcc(&st2);
		printf("main=%ld\n",st2-st1);
	rpcc(&st3);

	timer_start(&t1_start);
	dgemm_(&Trana,&Tranb,&K,&M,&N,&alphe,B,&K,A,&N,&beta,C1,&K);
	timer_end(&t1,&t1_start);
	printf("time: %lf us\n",t1);
	rpcc(&st4);
		printf("slave=%ld\n",st4-st3);

for (i=0;i<K;i++){
for(j=0;j<M;j++){
        if(fabs(C[i][j]-C1[i][j])>1.0e-3){
		printf("erro!,i=%d,j=%d,C=%f,C1=%f\n",i,j,C[i][j],C1[i][j]);
	}
}
}

		printf("end\n");

}





