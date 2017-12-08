#include<stdio.h>
#include<math.h>

double f(double x){
	return sin(x);
} 

double compoundTrapezoidFormula(double g(double),double lowerbound,double upperbound,int N){
	double result = 0;
	int n = N - 1;
	double h = (upperbound - lowerbound) / n;
	int i;
	result = result + 0.5 * g(lowerbound);
	for(i=1; i<n; i++){ 
		result = result + g(lowerbound + i * h);
	}
	result = result + 0.5 * g(upperbound);
	result = result * h;
	return result;
}


double compoundSimpsonFormula(double g(double),double lowerbound, double upperbound, int N){
	double result = 0;
	int n = N-1;
	int m = n / 2;
	double h = (upperbound - lowerbound) / n;
	int i;
	result = result + g(lowerbound);
	for(i=0;i<m;i++){
		result = result + 4*g(lowerbound + (2*i+1)*h);
	}
	for(i=1;i<m;i++){
		result = result + 2*g(lowerbound + (2*i)*h);
	}
	result = result + g(upperbound);
	result = result * h / 3.0;
	return result;
}

int main(){
	int k;
	int N;
	int i;
	double realResult = cos(1) - cos(5);
	double calculateResult;
	double eh;
	double ehDk;
	double ok;
	printf("复化梯形积分结果：\n");
	for(k=1;k<=12;k++){
		N = 1;
		for(i=1;i<=k;i++){
			N = N * 2;
		}
		N = N + 1;
		calculateResult = compoundTrapezoidFormula(f,1,5,N);
		printf("%.15e",calculateResult);
		eh = calculateResult-realResult;
		printf(", %.15e",eh);
		ehDk = compoundTrapezoidFormula(f,1,5,(2*N-1)) - realResult;
		ok = log(eh/ehDk)/log(2);
		printf(", %.15e\n",ok);
	}
	printf("复化simpson积分结果：\n");
	for(k=1;k<=12;k++){
		N = 1;
		for(i=1;i<=k;i++){
			N = N * 2;
		}
		N = N + 1;
		calculateResult = compoundSimpsonFormula(f,1,5,N);
		printf("%.15e",calculateResult);
		eh = calculateResult-realResult;
		printf(", %.15e",eh);
		ehDk = compoundSimpsonFormula(f,1,5,(2*N-1)) - realResult;
		ok = log(eh/ehDk)/log(2);
		printf(", %.15e\n",ok);
		
	}
}
