#include <iostream>
#include <stdio.h>
#include <fstream>
#include <ctime>
#include <chrono>
using namespace std;

string path = "C:\\Users\\lukas\\Documents\\CppWorkspace\\SAT\\implic.txt";

class Sat
{
    public:
        struct literal
        {
            bool neg = 0;
            bool *x;
        };
        
        int tabuNum;
        int *tabu; 
        bool xValue[9]{};
        int impNum = 0;
        bool *impValues = new bool[impNum]; 
        
        literal **implicants;
        
        void validLine(int i, string line)
        {
            implicants[i] = new literal[6];
            for(int j=0; j<6; j++) implicants[i][j].x = &xValue[0];  
    
            int l=0;
            int length = line.length();
            for(int k=0; k<length; k++)
                {
                    if(line[k] == '!') implicants[i][l].neg = 1;
                    else if(line[k] == 'x'){}
                    else if( ((int)line[k] > 48) && ((int)line[k] < 57) ) 
                        implicants[i][l].x = &xValue[( (int)line[k] - 48 )];  
                    else if(line[k] == '+')l++;
                }
        }
        
        void dataIn(int menu)
        {
            
            for(int i=0;i<8;i++)
                    {
                        xValue[i+1] = (rand() % 2 ) + 0;
                    }
                    
             if(menu == 1)
            {
                cout << "Ilosc implicentow(max: 100)?: ";
                cin >> impNum;
                implicants = new literal *[impNum];
                
                string line;
                for(int i=0; i<impNum; i++)
                {
                    cin >> line;
                    validLine(i, line);
                }
            }
            else if(menu == 2)
            {   
                string line;
                ifstream file(path);
                while( getline(file, line) ) impNum++;
                
                implicants = new literal *[impNum];
                cout << "Ilosc implicentow: " << impNum << endl;
                
                file.clear();
                file.seekg(0, ios::beg);
                
                int i=0;
                while( getline(file, line) )
                {
                    validLine(i, line);
                    i++;
                }
                
            }
        }
        
        bool checkSat()
        {
            for(int i=0; i<impNum; i++)
            {
                bool implicant = 0;
                for(int j=0; j<6; j++)
                {
                    if(implicants[i][j].x == &xValue[0]){}
                    else if(implicants[i][j].neg == 1) implicant += !*implicants[i][j].x;
                    else implicant += *implicants[i][j].x;
                }
               impValues[i] = implicant;
            }
            
            for(int i=0; i<impNum; i++) if(impValues[i] == 0) return 0;
            
            return 1;
        }
        
        void wSat()
        {
          
            while(!checkSat())
            {
                
                
                int k = 0;
                for(int i=0; i<impNum; i++) if(impValues[i] == 0) k++;
                int *negImp = new int[k]{};
                
                int j = 0;
                for(int i=0; i<impNum; i++)
                {
                    if(impValues[i] == 0)
                    {
                        negImp[j] = i;
                        j++;
                    }
                }
                int lottoImp = (rand() % k ) + 0;
                int lottoEle = (rand() % 6 ) + 0;
                while( (implicants[negImp[lottoImp]][lottoEle].x == &xValue[0]) && (*implicants[negImp[lottoImp]][lottoEle].x == 0) )
                {
                lottoEle = (rand() % 6 ) + 0; 
                }
                
                *implicants[negImp[lottoImp]][lottoEle].x = !(*implicants[negImp[lottoImp]][lottoEle].x);
                
            }
            
        }
        
        void gSat()
        {
        
            auto begin = chrono::high_resolution_clock::now();
            
            for(int i=0; i<tabuNum; i++) tabu[i] = 0;
            
            while(!checkSat())
            {
                
                
                int tabMin[8]{};
                for(int i=0;i<8;i++)
                {   
                    xValue[i+1] = !xValue[i+1];
                    checkSat();
                    int k = 0;
                    for(int j=0; j<impNum; j++)
                    {
                        if(impValues[j] == 0) k++;
                    }
                    tabMin[i] = k;
                    xValue[i+1] = !xValue[i+1];
                    checkSat();
                }
                
                int min=0;
                for(int i=0;i<8;i++)
                {
                    for(int j=0; j<tabuNum; j++)
                    {
                        if( (tabMin[min] > tabMin[i])&&(tabu[j]!=i) )
                        {
                            min = i; 
                            xValue[min+1] = !xValue[min+1];
                        }
                    }
                }
                
                for(int i=tabuNum-1; i>=0; i--) tabu[i+1] = tabu[i];
                tabu[0] = min;
                
                auto end = chrono::high_resolution_clock::now();
                if(chrono::duration_cast<chrono::milliseconds>(end-begin).count() > 50)
                {
                    for(int i=0;i<8;i++)
                    {
                        xValue[i+1] = (rand() % 2 ) + 0;
                    }
                }

            }
        }
        
        void test()
        {
           
            cout << "Test GSAT x 10000: " << endl;
            auto begin = chrono::high_resolution_clock::now();
            for(int i=0; i<10000; i++)
            {
                gSat();
                for(int j=1;j<9;j++) xValue[j] = 0;
            }
            auto end = chrono::high_resolution_clock::now();
            cout << "time: " << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "milliseconds" << endl << endl;
            
            
            cout << "Test WSAT x 10000: " << endl;
            begin = chrono::high_resolution_clock::now();
            for(int i=0; i<10000; i++)
            {
                wSat();
                for(int j=1;j<9;j++) xValue[j] = 0;
            }
            end = chrono::high_resolution_clock::now();
            cout << "time: " << chrono::duration_cast<chrono::milliseconds>(end-begin).count() << "milliseconds" << endl;
        }
        
        void init()
        {
            int menu;
            cout << "Chcesz wprowadzic implicenty recznie(1) czy z pliku(2)?: ";
            cin >> menu;
            dataIn(menu);
            print();
            cout << "Chcesz wykonac test?(1/0): ";
            cin >> menu;
            if(menu == 1)
            {
                cout << "Podaj dlugosc tablicy tabu: ";
                cin >> tabuNum;
                tabu = new int[tabuNum+1]();
                test();
            }
            else if(menu == 0)
            {
                cout << "Wybierz rodzaj metody WalkSAT(1), GeedySAT(2): ";
                cin >> menu;
                if(menu==1)wSat();
                else{
                cout << "Podaj dlugosc tablicy tabu: ";
                cin >> tabuNum;
                tabu = new int[tabuNum+1]();
                gSat();
                }
                print();
            }
           
        }
        
        void print()
        {
            cout << endl;
            for(int i=0; i<impNum; i++)
            {
                for(int j=0; j<6; j++)
                {
                    if(implicants[i][j].x == &xValue[0]){}
                    else if(implicants[i][j].neg == 1) cout << !*implicants[i][j].x;
                    else cout << *implicants[i][j].x;
                }
               cout << endl;
            }
            cout << "X: ";
            for(int i=1;i<9;i++) cout << xValue[i];
            cout << endl << endl;
        }
};

int main(int argc, char **argv)
{
    srand( time( NULL ) );
	cout << "SAT Problem\n";
    Sat test1;
    test1.init();
    
	return 0;
}
