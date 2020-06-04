#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

int length, menu, sumaA=0, L=0;
int * tabA;
int **tab;

int main(int argc, char **argv)
{
	cout << "Problem PARTITION"<< endl
    << "Podaj liczebnosc zbioru glownego: ";
    cin >> length;
    tabA = new int[length]();
    cout << "Czy chcesz zainicjowac rozmiary elementor recznie (1), losowo (2)?: ";
    cin >> menu;
    cout << endl;
    for(int i=0; i<length; i++)
    {
        cout << "a" << i+1 << ": ";
        cin >> tabA[i];
        sumaA +=tabA[i];
    }
    
    L = ceil((float)sumaA/2);
    
    tab = new int * [length];
    
    for(int i=0; i<length; i++) tab[i] = new int[sumaA]();
    
    
    
    for(int j=0; j<sumaA; j++) 
        if((j==0)||j==tabA[0]) tab[0][j] = 1;
                
    for(int i=1; i<length; i++) 
    {
        for(int j=0; j<=L; j++)
        {
            if((tab[i-1][j]==1)) tab[i][j] = 1;
            if((tabA[i]<=j)&&(tab[i-1][(j-tabA[i])]==1)) tab[i][j] = 1;
        }
    }
    
    
    

    for(int i=0; i<length; i++) 
    {
        for(int j=0; j<L; j++)
        {
            if(tab[i][j] == 1) cout << "T" << " "; 
            if(tab[i][j] == 0) cout << "F" << " ";
            
        }
        cout << endl;
    }
    
    if(tab[length-1][L-1] == 1) cout << "Podzial jest mozliwy" << endl;

    
    
	return 0;
}
