#include <iostream>
#include <stdio.h>
#include <cstdlib>
using namespace std;

int n; //n-elementowy zbiór
int *tab;

void show(int n_pos){
	for(int i=1; i<=n_pos;i++){
		cout<<tab[i]<<" ";
	}
	cout<<endl;
}

int up(int);
int down(int);

int up(int n_pos){
	if((tab[n_pos-1]+1 <= n)&&(n_pos <= n)){
		tab[n_pos] = tab[n_pos-1]+1;
		show(n_pos);
		up(n_pos+1);
	}else down(n_pos-1);
}

int down(int n_pos){
	if((tab[n_pos] < n)&&(n_pos <= n)){
		tab[n_pos] = tab[n_pos]+1;
		tab[n_pos+1] = 0;
		show(n_pos);
		up(n_pos+1);
	}else if(n_pos-1!=0) down(n_pos-1);
}

int main()
{
    cout << "Kombinacje bez powtorzen (alg. Semby)"<<endl;
    cout << "podaj dlogosc ciagu: ";
    cin >> n;
    tab = new int[n+1]();
	up(1);
    
    return 0;
}

