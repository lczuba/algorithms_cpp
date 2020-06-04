#include <stdio.h>
#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <math.h>
#include <bitset>
using namespace std;

struct HTNode
{
        HTNode * left; // wskaźnik do lewego dziecka 
        HTNode * right; // wskaźnik do prawego dziecka
        bool type = false; // false - węzeł, true - liść;
        int count = 0; // ilość wystąpień 
        char key; // symbol 
};


class File
{
    public:
        streampos size, sizeAfter;
        char * memblock;
        list<HTNode*> Hlist;
        list<bool>Code;
        list<bool>CodeAll;
        int overbits = 0;
        string filePath;
        
        void openFile(string fPath, string fName)
        {
            filePath = fPath; 
            ifstream file (fPath + fName, ios::in|ios::binary|ios::ate);
            if(file.is_open())
            {
                size = file.tellg();
                memblock = new char[size];
                file.seekg (0, ios::beg);
                file.read (memblock, size);
                file.close();
                cout << endl << "Rozmiar pliku: "<< (float)size / 1024 << " KB" << endl;
            }
            else cout << "Nie udalo sie otworzyc pliku!!!" << endl;
        }
        
        void frequency()
        {   
            for(int i=0; i<size; i++)
            {
                bool exist = false;
                for( list<HTNode*>::iterator iter=Hlist.begin(); iter != Hlist.end(); iter++ )
                    {
                        if((*iter)->key == memblock[i])
                        {
                            (*iter)->count++;
                            exist = true;
                        }
                    }
                if(!exist)
                {
                    HTNode *node;
                    node = new HTNode;
                    node->key = memblock[i];
                    node->count = 1;
                    node->type = true;
                    Hlist.push_back(node);
                }
            }
        }
        
        void sort()
        {
            // Sorting List using Lambda function as comparator
            Hlist.sort([](const HTNode * node1, const HTNode * node2)
            {
                    if(node1->count == node2->count)
                        return node1->count < node2->count;
                    return node1->count < node2->count;
            });
        }
        
        void createTree()
        {
            while(Hlist.size() != 1)
            {
                HTNode * node;
                node = new HTNode;
                list<HTNode*>::iterator iter=Hlist.begin();
                node->left = (*iter);
                node->count = (*iter)->count;
                iter = Hlist.erase(iter);
                node->right = (*iter);
                node->count += (*iter)->count;
                iter = Hlist.erase(iter);
                
                Hlist.push_front(node);
                sort();
            }
        }
        
        void path(HTNode *node, char key)
        {
            if(node->type == true)
                {
                    if(node->key == key)
                    {
                        for( list<bool>::iterator iter=Code.begin(); iter != Code.end(); iter++ )
                        {
//                            cout << *iter;
                            CodeAll.push_back((*iter));
                        }  
                    }
                    else Code.pop_back();
                }
            else if(node->type == false)
            {
                Code.push_back(false);
                path(node->left, key);
                Code.push_back(true);
                path(node->right, key);
                Code.pop_back(); 
            }
        }
        
        void encoding()
        {
            list<HTNode*>::iterator root=Hlist.begin();
            for(int i=0; i<size; i++)
            {
                path((*root), memblock[i]);
                Code.clear();
            }
        }
        
        void decoding()
        {
            cout << endl;
            for(int i=0;i<size;i++)
            {
                bitset<8> bits (memblock[i]);
                for(int i=0;i<8;i++) CodeAll.push_back(bits[i]);
            }
            
            string fileName;
            cout << endl << "Zapisz odkodowany plik jako: (np. decrypted.txt): ";
            cin >> fileName;
            
            ofstream infile;
            infile.open(filePath + fileName , ios::binary | ios::out |ios::ate);
            
           
                    list<bool>::iterator CodeIter=CodeAll.begin();
                    list<HTNode*>::iterator root=Hlist.begin();
                    HTNode *node = *root;
                    while(CodeAll.size() - overbits+1)
                    {
                        
                        if((node)->type == true)
                        {
                            char data = (node)->key;
                            infile.write(static_cast<const char*>(&data), sizeof(data));
                            node = *root;
                        }
                        else if((node)->type == false)
                        {
                            if(*CodeIter == false) node = node->left;
                            if(*CodeIter == true) node = node->right;
                            CodeIter = CodeAll.erase(CodeIter);
                        }
                    }
            cout << endl;
        }
        
        void print()
        {
            for( list<HTNode*>::iterator iter=Hlist.begin(); iter != Hlist.end(); iter++ )
                {
                    cout <<(int)(*iter)->key << " " << (*iter)->count;
                    cout << endl;
                }  
        }
        
        void saveEnc()
        {
            string fileName;
            cout << endl << "Zapisz plik jako: (np. encrypted.txt): ";
            cin >> fileName;
            
            ofstream infile;
            infile.open(filePath + fileName , ios::binary | ios::out |ios::ate);
            
            if((CodeAll.size()%8))
            {
                overbits = 8-(CodeAll.size()%8);
                for(int i=0; i<overbits; i++) CodeAll.push_back(0);
            }
            for(auto iter = CodeAll.begin(); iter!=CodeAll.end();)
            {
                int decimal=0;
                for(int i=0;i<8;i++)
                {
                    decimal += pow(2,i)* (*iter);
                    iter++;
                }
                char data = decimal;
                infile.write(static_cast<const char*>(&data), sizeof(data));
            }
            CodeAll.clear();
            sizeAfter = infile.tellp();
            cout << endl << "Rozmiar pliku po kompresji: "<< (float)sizeAfter / 1024  << " KB" << endl << endl
            << "Stosunek procentowy: " << sizeAfter*100/size << "%" << endl << endl;
        }
};


int main(int argc, char **argv)
{
    File fileCode;
    string fileName, filePath = "C:\\Users\\lukas\\Documents\\CppWorkspace\\HuffmanCoding\\";
    bool exit = false;
    
    while(!exit)
    {
        cout << "Kodowanie Huffmana" << endl
        << "1. Zakoduj plik" << endl
        << "2. Odkoduj plik" << endl
        << "3. Wyjscie" << endl;
        int option;
        cin >> option;
        
            switch(option)
            {
            case 1:
            {
                cout << "Podaj nazwe pliku do zakodowania (np. text.txt): ";
                cin >> fileName;
                
                fileCode.openFile(filePath, fileName);
                fileCode.frequency();
                fileCode.sort();
                fileCode.createTree();
                fileCode.encoding();
                fileCode.saveEnc();
                
            break; 
            }
            case 2:
                cout << "Podaj nazwe pliku do odkodowania (np. encrypted.txt): ";
                cin >> fileName;
                fileCode.openFile(filePath, fileName);
                fileCode.decoding();
            break;
            
            case 3:
                exit = true;
            break;
            }
    }
	
    
    
	return 0;
}
