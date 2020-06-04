#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <ctime>
using namespace std;

int n,k,
a=25,
b=25,
c=25,
d=25,
r=1,
g=50;

int **tab;

void show()
{
//    for(int i=0; i<n; i++)
//    {
//        for(int j=0; j<n; j++) cout << tab[i][j] << " "; 
//        cout << endl;
//    }
}

int lotto()
{
int l = (rand() % 100) + 1;
if(l<=a) return 0;
else if(l<=a+b) return 1;
else if(l<=a+b+c) return 2;
else return 3;
}

int graph(int x, int y, int s)
{
    if(s!=1)
    {
        int l = lotto();
        if(l==0) graph(x-s/2, y-s/2, s/2);
        else if(l==1) graph(x, y-s/2, s/2);
        else if(l==2) graph(x-s/2, y, s/2);
        else graph(x, y, s/2);
    }
	else if(tab[x-1][y-1]==1) graph(n,n,n);
    else
    {
        if(r){tab[y-1][x-1]=1;};
        tab[x-1][y-1]=1;
    } 
}


int main(int argc, char **argv)
{
    srand( time(NULL) );
	cout << "Generowanie macierzy grafu R-MAT" << endl
         << "Rodzaj grafu (0-skierowany, 1-nieskierowany): ";
    cin >> r;
    cout << "Ilosc wierzcholkow: n=2^k, podaj k: ";
    cin >> k;
    cout << "Gestosc (w %): ";
    cin >> g;
    cout << "Prawdopodobienstwo (w %, a+b+c+d=100)" << endl << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    cout << "c: ";
    cin >> c;
    cout << "d: ";
    cin >> d;
    if((a+b+c+d==100) && ((r==1)||(r==0)) && (k>0))
    {
        n = pow(2,k);
        tab = new int *[n];
        for(int i=0; i<n; i++) tab[i] = new int[n]();
        for(int i=0; i<n; i++) for(int j=0; j<n; j++) if(i==j)tab[i][j]=1; //jedynki po przekontnej
        
        int m = (pow(n,2)-n)*g/100;
        if(r) m=m/2;
        
        for(int i=0; i<m; i++) graph(n,n,n);
        show();
        
    }else cout << "Zle dane"<< endl;
    
    

	return 0;
}
