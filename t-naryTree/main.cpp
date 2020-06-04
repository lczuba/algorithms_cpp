#include <stdio.h>
#include <iostream>
using namespace std;
int t, n;
int *tab;

show()
{
    for(int i=0; i<n*t; i++){
       cout << tab[i]; 
    };
    cout << endl;
}

int check(int i)
{
    int check = 0;
    for(i; i>=0; i=i-t)if(tab[i] == 1)check++;
    if(check == n) return 1;
    else return 0;
}

int search(int p=n*t-1)
{
    if(tab[p] == 1) return p;
    else search(p-1);
}

void tree(int p=n*t-1)
{
    p = search(p);
    if(p != n*t-t)
        {
            show();
            tab[p] = 0;
            tab[p+1] = 1;
            tree();
        }
    else if(p == n*t-t)
        {
            show();
            if(check(p));
            else
            {
                tab[p] = 0;
                p = search(p);
                tab[p] = 0;
                tab[p+1] = 1;
                tab[p+2] = 1;
                tree();
            }
            
        }
}

int main(int argc, char **argv)
{
	cout << "Generowanie drzew t-narnych z n wewnetrznymi wezlami." 
    << endl 
    << "Podaj liczbe t: ";
    cin >> t;
    cout << "Podaj liczbe n: ";
    cin >> n;
    tab = new int[n*t]();
    
    for(int i=0; i<n; i++) tab[i] = 1;
    tree();
	return 0;
}
