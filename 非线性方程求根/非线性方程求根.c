#include<stdio.h>
#include<math.h>
#include<stdlib.h>

double f(double x){
	return x*x*x/3.0 - x;
} 

double dfDdx(double x){
	return x*x-1;
}

double NewtonIterator(double x, double g(double), double dgDdx(double)){
	return x - g(x)/dgDdx(x);
}

double secantMethod(double xk, double xkm1, double g(double)){
	return xk - (g(xk)*(xk-xkm1))/(g(xk)-g(xkm1));
}

double e = 1e-8;

int main(){
	double xNewton[4]={0.1,0.2,0.9,9.0};
	double xSecant[4][2]={-0.1, 0.1, -0.2, 0.2, -2, 0.9, 0.9, 9.0};
	int i, n;
	double xk, xkm1, xkm2;
	printf("牛顿法：\n");
	for(n=0;n<4;n++){
		xkm1 = xNewton[n];
		//printf("debug\n");
		for(i=1;i<=1000000;i++){
			xk = NewtonIterator(xkm1,f,dfDdx);
			//printf("xk=%f,xkm1=%f\n",xk,xkm1);
			//system("pause");
			if(fabs(xk - xkm1)<e){
				break;
			}
			else{
				xkm1 = xk;
			}
		}
			if(i<=1000000){
			printf("初值=%.15e,根=%.15e,迭代步数=%d\n",xNewton[n],xk,i);
		}
		else{
			printf("经过1,000,000次计算都没有误差值内答案\n");
		}
	}
	printf("弦截法:\n");
	for(n=0;n<4;n++){
		xkm2 = xSecant[n][0];
		xkm1 = xSecant[n][1];
		for(i=1;i<=1000000;i++){
			xk = secantMethod(xkm1, xkm2, f);
		//	printf("xk=%f,xkm1=%f,xkm2=%f\n",xk,xkm1,xkm2);
			if(fabs(xk - xkm1)<e){
				break;
			}
			else{
				xkm2 = xkm1;
				xkm1 = xk;
			}
		}
		if(i<=1000000){
			printf("初值=%.15e、%.15e,根=%.15e,迭代步数=%d\n",xSecant[n][0],xSecant[n][1],xk,i);
		}
		else{
			printf("经过1,000,000次计算都没有误差值内答案\n");
		}
	}
	return 0;
}
