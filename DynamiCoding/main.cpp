#include <iostream>

using namespace std;
int ilosc;
int ilerazy;

int* Tab_pomocnicza;
int* tab2;
int* tab;

int e=0;
int s;
int x;
int teb[2];
int zmienna;


void Bledy2()
{
    int k=0;;
     do{

     k=0;
     cout<<"Wypelnij zbiór: "<<endl;
     for(int i=0; i<ilosc; i++)
     {
         cin>>tab[i];
         k=k+tab[i];
     }

    if(k<0 || k>55)
          {
            cout << "Suma wyrazow jest wieksza od 55 lub mniejsza od zera" << endl;
          }
    } while(k<0 || k>55);
    cout<<endl;
}
void Bledy1()
{
    do{
     cout<<"Podaj wyrazy w ciagu: ";
     cin>>ilosc;

    if(ilosc<0 || ilosc>10)
          {
            cout << "Podaj poprawna ilosc (10>ilosc>0)" << endl;
          }
    } while(ilosc<0 || ilosc>10);
    cout<<endl;
}
void Stworz_tablice()
{
    tab= new int [ilosc];
    for(int i=0; i<ilosc; i++)
    tab[ilosc]=0;

}
Rozmowa()
{
    Bledy1();
    Stworz_tablice();
    Bledy2();
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void wyczysc()
{
 for(int i=0; i<ilosc; i++)
 Tab_pomocnicza[i]=0;
}

void cos(int e)
{
    Tab_pomocnicza[e]=55;
}

void poka(int *wynik)
{
     cout<<"po zredukowaniu: ";
      for(int s=0; s<ilosc; s++)
       cout<<" "<<Tab_pomocnicza[s];
        cout<<endl;
   for(int i=0; i<ilosc; i++)
   {
       if(Tab_pomocnicza[i]!=55)
        teb[1]+=tab[i]; //!
   }
}
void Partition()
{
  cout<<"tab0=: "<<teb[0]<<endl;
  cout<<"tab1=: "<<teb[1]<<endl;
  if(teb[0]==teb[1])
  {
    cout<<"Znalazlem, suma: "<<teb[0]<<endl;
    exit(0);
  }
  teb[0]=0;
  teb[1]=0;
}
void wyswietl(int* wynik)
{

    for(int i=0; i<x; i++)
    {
        int s;
       for(s=0; s<ilosc; s++)             // 2 czesc
    //    if(Tab_pomocnicza[s]==wynik[i])
     //  {
      //     cout<<"Znleziono na pozcyji: "<<s<<endl;
     //       break;
    //   }

        cos(wynik[i]-1);
        cout<<"Wygenerowana liczba: "<<wynik[i]<<endl;
        teb[0]+=tab[wynik[i]-1]; //!!
    }

    poka(wynik);
    Partition();
    wyczysc();

}

void wypisz(int i, int p, int z)
{

    for( int j = i;j<= ilosc - p + 1; j++ )
    {
       tab2[ x - p] = j;

        if( p==1 )
        {

            wyswietl(tab2);
        }
        else
        wypisz(j + 1,p - 1,z);
    }
}
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int main()
{
    teb[0]=0;
    teb[1]=0;
    Rozmowa();
// --------------------------------------------
    if(ilosc%2==1)
    zmienna=(ilosc-1)/2;
    if(ilosc%2==0)
    zmienna=ilosc/2;
    cout<<"Ilosc wyznaczen: "<<zmienna<<endl;
    Tab_pomocnicza= new int [ilosc];

    for(int i=1; i<=ilosc; i++)
    Tab_pomocnicza[i-1]=0;

    for( x=1; x<=zmienna; x++)
    {
        delete [] tab2;
        tab2 = new int[x];
        cout<<"funkcja odpalona:"<<x<<endl;
        wypisz( 1, x, 0 );

    }
// ---------------------------------------------------------
    return 0;
}
