#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 4
#define Epsilon 0.00001


double * gaussSeidel(double **A, double *b,double *x, int n, int reset){
	static int iniFlag = 1;
	static double * result;
	int i;
	if(reset){
		iniFlag = 1;
	}
	if(iniFlag){
		iniFlag = 0;
		result = (double *)malloc(n * sizeof(double));
		for(i=0;i<n;i++){
			result[i] = x[i];
		}
	}
	int j;
	for(i=0;i<n;i++){
		result[i] = b[i];
		for(j=0;j<n;j++){
			if(j==i || A[i][j] ==0){
				continue;
			}
			result[i] = result[i] - A[i][j] * result[j];
		}
		result[i] = result[i]/A[i][i];
	}
	double *  r = result;
	return result;
}

double * matrixMulOneColum(double **a, double *x, int n){
	double *result = (double *)malloc(n*sizeof(double));
	int i,j;
	for(i=0;i<n;i++){
		result[i] = 0;
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			result[i] = result[i] + a[i][j] * x[j];
		}
	}
	return result;
}

double diffNormInf(double *a, double *b, int n){
	double result = 0;
	int i;
	for(i=0;i<n;i++){
		if(fabs(a[i]-b[i]) > result){
			result = fabs(a[i] - b[i]);
		}
	}
	return result;
}

int main(){
	double ** A;
	double *b;
	double * x;
	A = (double **)malloc(N*sizeof(double *));
	int i;
	for(i=0;i<N;i++){
		A[i] = (double *)malloc(N*sizeof(double));
	}
	A[0][0] = 3; A[0][1] = 3; A[0][2] = -2; A[0][3] = 1;
	A[1][0] = 2; A[1][1] = 5; A[1][2] = 3; A[1][3] = -4;
	A[2][0] = -3; A[2][1] = 2; A[2][2] = 6; A[2][3] = 1;
	A[3][0] = 1; A[3][1] = 2; A[3][2] = -1; A[3][3] = 3;
	b = (double *)malloc(N*sizeof(double));
	for(i=0;i<N;i++){
		b[i] = 0;
	}
	b[0] = 1;
	double * result;
	x = (double *)malloc(N*sizeof(double));
	for(i=0;i<N;i++){
		x[i] = 1;
	}
	int k = 0;
	double * temp;
	int reset = 0;
	while(k<4){
		result = gaussSeidel(A, b, x, N, reset);
		reset = 0;
		temp = matrixMulOneColum(A, result, N);
		if(diffNormInf(temp, b, N) < Epsilon){
			for(i=0;i<N;i++){
				printf("result[%d] = %.2f\t",i+1,result[i]);
			}
			printf("\n");
			for(i=0;i<N;i++){
				x[i] = 1;
			}
			for(i=0;i<N;i++){
				b[i] = 0;
			}
			k++;
			if(k>=4){
				break;
			}
			b[k] = 1;
			reset = 1;
		}
		free(temp);
	}
	
}

