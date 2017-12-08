#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define N 9 

double * columnGauss(double ** a, double *b, int n){
	int i,j,k;
	int ii, biggestColumn;
	double * temp;
	double biggest;
	double z;
	int id,jd;
	for(i=0;i<n-1;i++){		
		biggest = -1;
		for(ii=i;ii<n;ii++){
			if(fabs(a[ii][i]) > biggest){
				biggestColumn = ii;
				biggest = fabs(a[ii][i]);
			}
		}
		temp = a[i];
		a[i] = a[biggestColumn];
		a[biggestColumn] = temp;
		
		for(ii = i+1;ii<n;ii++){
			z = a[ii][i] / a[i][i];
			a[ii][i] = 0;
			for(j = i + 1;j<n;j++){
				a[ii][j] = a[ii][j] - z * a[i][j];
			}
			b[ii] = b[ii] - z * b[i];
		}
	}
	for(i=n-1;i>=0;i--){
		for(j=i+1;j<n;j++){
			b[i] = b[i] - a[i][j] * b[j];
		}
		b[i] = b[i] / a[i][i];
	}
	return b;
}

int main(){
	int n = N;
	double ** a = (double **)malloc(n * sizeof(double *));
	int i;
	for(i=0;i<n;i++){
		a[i] = (double *)malloc(n * sizeof(double));
	}
	double * b = (double *)malloc(n * sizeof(double));
	int j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			a[i][j] = 0;
		}
	}
	a[0][0] = 31; a[0][1] = -13; a[0][5] = -10;
	a[1][0] = -13; a[1][1] = 35; a[1][2] = -9; a[1][4] = -11;
	a[2][1] = -9; a[2][2] = 31; a[2][3] = -10; 
	a[3][2] = -10; a[3][3] = 79; a[3][4] = -30; a[3][8] = -9;
	a[4][3] = -30; a[4][4] = 57; a[4][5] = -7; a[4][7] = -5;
	a[5][4] = -7; a[5][5] = 47; a[5][6] = -30;
	a[6][5] = -30; a[6][6] = 41;
	a[7][4] = -5; a[7][7] = 27; a[7][8] = -2;
	a[8][3] = -9; a[8][7] = -2; a[8][8] = 29;
	b[0] = -15; b[1] = 27; b[2] = -23; b[3] = 0; b[4] = -20;
	b[5] = 12; b[6] = -7; b[7] = 7; b[8] = 10;
	double * result = columnGauss(a,b,n);
	for(i=0;i<n;i++){
		printf("x%d=%.15e\n", i+1,result[i]);
	}
} 
