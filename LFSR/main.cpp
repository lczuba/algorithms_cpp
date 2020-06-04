#include <iostream>
#include <fstream>
#include <istream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iterator>
#include <math.h>
using namespace std;

bool * output;
int poz=0;

void print(bool value)
{
    cout << value;
    output[poz] = value;
    poz++;
}

void save()
{
    ofstream dataOut;
    dataOut.open("C:\\Users\\lukas\\Documents\\CppWorkspace\\LFSR\\dataOut.txt");
    for(int i=0; i<poz; i++) dataOut << output[i];
    dataOut.close();
    cout << endl << "Dlugosc sekwencji: " << poz - 1;
}

bool check(bool *arr1, bool *arr2, long long n)
{
    for (long long i = 0; i < n; i++) 
        if (arr1[i] != arr2[i]) 
            return false; 
    return true;
}

bool fbSum(int fbType, int regLength, bool *reg_copy, bool *feedback)
{
    int sum=0;
    if(fbType == 1 ) {for(int i=1; i<regLength; i++)
        if(feedback[i] == 1)sum=sum+reg_copy[i];}
    else if(fbType == 2)
    {
        sum = reg_copy[(regLength - 1)];
        for(int i=1; i<(regLength - 1); i++) 
            if(feedback[i] == 1) reg_copy[i] = (sum + reg_copy[i])%2;
    }
    sum = sum % 2;    
    return sum;
}

void lfsr(bool *reg, bool *reg_copy, int regLength, bool *feedback, int fbType)
{   
    int sum = fbSum(fbType, regLength, reg_copy, feedback);
    print(reg_copy[regLength-1]);
    for(int i=regLength-2; i>=0; i--) reg_copy[i+1] = reg_copy[i];
    reg_copy[0] = sum;
    if(!check(reg, reg_copy, regLength)) 
    lfsr(reg, reg_copy, regLength, feedback, fbType);
    else save();
}

int main(int argc, char **argv)
{   
    int regLength, fbType;
    bool *reg, *regCopy, *feedback;
    
    int opt;
	cout << "LinearFeedbackShiftRegister" << endl
    << "1.Wczytaj ustawienia z pliku;" << endl 
    << "2.Wpisz ustawienia recznie;" << endl;
    cin >> opt;
    if(opt == 1)
    {   
        string fName;
        ifstream dataIn;
        cout << "Podaj nazwe pliku.txt: ";
        cin >> fName;
//        fName = "dataIn.txt";
        dataIn.open("C:\\Users\\lukas\\Documents\\CppWorkspace\\LFSR\\" + fName);
        if(dataIn.is_open())
        {   
        
            string line;
            getline(dataIn, line);
            regLength = stoi(line);     
       
            reg = new bool[regLength];
            regCopy = new bool[regLength];
            int power = pow(2, regLength) - 1; 
            output = new bool[power];
            char value[regLength];
            getline(dataIn, line); 
            strcpy(value, line.c_str());
            for(int i=0;i<regLength;i++)
            {
                reg[i] = value[i] - '0';
                regCopy[i] = value[i] - '0';
            }
            
            getline(dataIn, line);
            fbType = stoi(line);
            
            feedback = new bool[regLength];
            getline(dataIn, line);
            strcpy(value, line.c_str());
            for(int i=0;i<regLength;i++)feedback[i] = value[i] - '0';
        }
        dataIn.close();
        lfsr(reg, regCopy, regLength, feedback, fbType);
        cout << endl;
        
    }
    else if(opt == 2)
    {
        cout << "Dlugosc rejestru: ";
        cin >> regLength;
        
        cout << "Stan poczatkowy rejestru(np.: 10101010): ";
        reg = new bool[regLength];
        regCopy = new bool[regLength];
        int power = pow(2, regLength) - 1; 
        output = new bool[power];
        char value[regLength];
        cin >> value;
        for(int i=0;i<regLength;i++)
            {
                reg[i] = value[i] - '0';
                regCopy[i] = value[i] - '0';
            }
        
        cout << "Rodzaj sprzezenia: " << endl
        << "1.Zewnetrzne;" << endl
        << "2.Wewnetrzne;" << endl;
        cin >> fbType;
        
        cout << "Wektor opisujacy sprzezenie zwrotne (np.: 10010001): ";
        feedback = new bool[regLength];
        cin >> value;
        for(int i=0;i<regLength;i++)feedback[i] = value[i] - '0';
        
        lfsr(reg, regCopy, regLength, feedback, fbType);
        cout << endl;
    }
    else
    {
        cout << "Error!";
    }
    
    
	return 0;
}
