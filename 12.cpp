#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

int expRandom(double p,int n)
{
	int i=0;
	while (((rand()*1.0/RAND_MAX)>p)and(i<n-1))
	{
		i++;
	}
	return i;
}

double av(double *probs,int n)
{
	double avrg=0;
	int i=0;
	while(i<n)
	{
		avrg+=i*probs[i];
		i++;
	}
	return avrg;
}


double var(double *probs,int n)
{
	double variance=0;
	int i=0;
	while(i<n)
	{
		variance+=i*i*probs[i];
		i++;
	}
	variance=variance-av(probs,n)*av(probs,n);
	return variance;
}

int main()
{
	srand(unsigned(time(0)));
	double p;
	cout<<"Enter probability for geometric destribution:"<<endl;
	cin>>p;
	int n;
	n=int(ceil(2/p))+1;
	double *theoretic=new double[n];
	int i=0;
	double pr=1;
	while (i<n-1)
	{
		theoretic[i]=pow(1-p,i)*p;
		pr-=theoretic[i];
		i++;
	}
	theoretic[i]=pr;
	cout<<endl<<"Enter number of experiments"<<endl;
	int num;
	cin>>num;
	double *expProb=new double[n];
	i=0;
	while (i<n)
	{
		expProb[i]=0;
		i++;
	}
	i=0;
	while (i<num)
	{
		expProb[expRandom(p,n)]+=1.0/num;
		i++;
	}
	cout<<endl<<"Experemental probabilities:"<<endl;	
	i=0;
	while (i<n-1)
	{
		cout<<i<<" before success "<<": "<<expProb[i]<<endl;
		i++;
	}
	cout<<i<<" or more before success "<<": "<<expProb[i]<<endl;
	double error=abs(av(expProb,n)-av(theoretic,n))/(av(theoretic,n)+1);
	cout<<"Average: "<<av(expProb,n)+1<<" ( "<<error*100<<"% error)"<<endl;
	
	error=abs(var(expProb,n)-var(theoretic,n))/var(theoretic,n);
	cout<<"Variance: "<<var(expProb,n)<<" ( "<<error*100<<"% error)"<<endl;
	
	double chisqr=0;
	i=0;
	while (i<n)
	{
		chisqr+=(expProb[i]*expProb[i])/theoretic[i];
		i++;
	}
	chisqr=(chisqr-1)*num;
	cout<<"Chi squared: "<<chisqr<<endl<<"Compare this to table value to test destribution"<<endl;
	cout<<"(Smaller means that experemental matches theoretical)";
}
