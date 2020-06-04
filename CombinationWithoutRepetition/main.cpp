#include <iostream>
#include <stdio.h>
#include <cstdlib>
using namespace std;

int n; //n-elementowy zbiór
int k; //k-elementowy podzbiór
int *tab = new int[k]; //dynamiczna tablica k-elementowa

void show(){
	for(int i=0; i<=k; i++){
	    cout << tab[i] << " ";
	}
	cout<< endl;
}

int comb(int a_pos){
	if(a_pos != -1){
		int max_pos = n-(k-a_pos);
		if(tab[a_pos]<max_pos){
            tab[a_pos]++;
            
            for(int i=a_pos+1;i<=k; i++)
			{
            	tab[i] = tab[i-1]+1;
            }
            
            a_pos=k;
            show();
            return comb(a_pos);
        }else return comb(a_pos-1);	
	}
}

int main()
{
    
    cout << "Kombinacje bez powtorzen"<<endl;
    cout << "podaj dlogosc ciagu: ";
    cin >> n;
    cout << "podaj dlogosc kombinacii: ";
    cin >> k;
   	if(k<=n){
	   	k--;
	    for(int i=0; i<=k; i++){
	        tab[i]=i+1;
	    }
	    show();
	         
	    comb(k);
	}else{
		cout << "k > n error";
	}
    
    
    return 0;
}

