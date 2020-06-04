#include <iostream>
#include <stdio.h>
#include <cstdlib>
using namespace std;

int n;
int *tab1 = new int[n];
int *tab2 = new int[n+1];

void show(){
    
    for(int i=0; i<n; i++){
        cout << tab2[i];
    }
    cout << endl;
}

int check(){
    int p=1;
    for(int i=0; i<n; i++){
        if(tab1[i]+1 == (tab1[i+1]))p++;
    }
    if(p==n)return 1;
    else return 0;
}

void permutation(int k, int l){
    int p;
    if(k!=n){
        show();
        tab2[k] = tab2[k+1];
        tab2[k+1] = 1;
        permutation(k+1, l);
    }else if(l!=n-1){
        p = tab1[l];
        tab1[l] = tab1[l+1];
        tab1[l+1] = p;
        for(int i=0; i<n; i++){
            tab2[i] = tab1[i];
        }
        if(check());
        else permutation(0, l+1);
        
    }
    else if(l==n-1){
        permutation(n,1);
    }
}

int main()
{
	cout << "Permutacje zbioru n-elementowego" 
    << endl 
    << "podaj dlugosc zbioru: ";
    cin >> n;
    
    for(int i=0; i<n; i++){
        tab1[i] = i+1;
    }
    
    for(int i=0; i<n; i++){
        tab2[i] = tab1[i];
    }
    
    permutation(0,1);
    
	return 0;
}
