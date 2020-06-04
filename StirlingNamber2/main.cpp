#include <iostream>
#include <stdio.h>
#include <cstdlib>
using namespace std;

int n;
int c_max = 1;
int *tab = new int[n+1]{};

void show(){
    for(int i=1; i<=n; i++){
        cout << tab[i];
    }
    cout << endl;
};

void stirling(int i){
    if(i != 0){
        for(int k=0; k<=i-1; k++){
            if(tab[k]+1>c_max)c_max = tab[k]+1;
        }
        if(tab[i]<c_max){
            tab[i]++;
            show();
            stirling(n);
        }else{
            tab[i]=1;
            c_max=1;
            stirling(i-1);
        }
    }
};

int main()
{
	cout << "Generowanie wszystkich podzialow zbiodu n-elementowego" << endl
         << "Podaj liczbe n:";
    cin >> n;
    for(int i=1; i<=n; i++){
        tab[i] = 1;
    }
    show();
    stirling(n);
	return 0;
}
