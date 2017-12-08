#include<stdio.h> 
#include<math.h>

int main(){
	double A[10][2];//����A
	double Y[10][1];//����Y
	double x[10] = {0.25,0.5,0.75,1,1.25,1.5,1.75,2,2.25,2.5};
	double y[10] = {1.284,1.648,2.117,2.718,3.427,2.798,3.534,4.456,5.465,5.894};
	int i,j; 
	for(i=0;i<10;i++){
		A[i][0] = sin(x[i]);
		A[i][1] = cos(x[i]);
		Y[i][0] = y[i];
	} 
	double AT[2][10];//����A��ת�� 
	for(i=0;i<10;i++){
		AT[0][i] = sin(x[i]);
		AT[1][i] = cos(x[i]);
	}
	double ATA[2][2];//����A��ת�ó���A
	int m;
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			ATA[i][j] = 0;
			for(m=0;m<10;m++){
				ATA[i][j] = ATA[i][j] + AT[i][m]*A[m][j];
			}
		}
	}
	
	double ATY[2][1];//����A��ת�ó���Y 
	for(i=0;i<2;i++){
		for(j=0;j<1;j++){
			ATY[i][j] = 0;
			for(m=0;m<10;m++){
				ATY[i][j] = ATY[i][j] + AT[i][m] * Y[m][j]; 
			}
		}
	}
	//�����Է����� AT A ab = AT Y
	double ab[2][1];//a��b 
	double Gauss[2][3];//��˹��Ԫ�����Ǹ����󣬻�Ϊ 1 0 a; 0 1 b;
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			Gauss[i][j] = ATA[i][j];
		}
		Gauss[i][2] = ATY[i][0];
	}
	double g = Gauss[0][1]; 
	for(j=0;j<3;j++){//��ȥGauss[0][1] 
		Gauss[0][j] = Gauss[0][j] - Gauss[1][j] * g / Gauss[1][1];
	} 

	g = Gauss[0][0];
	for(j=0;j<3;j++){//��Gauss[0][0]ϵ����Ϊ1 
		Gauss[0][j] = Gauss[0][j] / g;
	}

	g = Gauss[1][0];
	for(j=0;j<3;j++){//��ȥGauss[1][0] 
		Gauss[1][j] = Gauss[1][j] - Gauss[0][j] *g / Gauss[0][0];
	}
	
	g = Gauss[1][1];
	for(j=0;j<3;j++){//��Gauss[1][1]��ϵ����Ϊ1 
		Gauss[1][j] = Gauss[1][j] / g;
	}
	double a = ab[0][0] = Gauss[0][2];//a
	double b = ab[1][0] = Gauss[1][2];//b
	//���������� 
	double AXminusB[10][1]; 
	for(i=0;i<10;i++){
		AXminusB[i][0] = 0;
		for(m=0;m<2;m++){
			AXminusB[i][0] = AXminusB[i][0] + A[i][m] * ab[m][0];
		}
		AXminusB[i][0] = AXminusB[i][0] - Y[i][0]; 
	}
	double mse = 0;
	for(i=0;i<10;i++){
		mse = mse + AXminusB[i][0] * AXminusB[i][0];
	}
	mse = mse/10;
	printf("a=%.15e,b=%.15e,�������=%.15e",a,b,mse);
	
	return 0;
} 
