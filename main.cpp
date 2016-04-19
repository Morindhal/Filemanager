#include "FileObject.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

#define home_dir "/home/bergman/Documents/c++/filemanager/source/"

using namespace std;

void PrintLocationToFile(string * ls_current_dir);
void ParseMyString(string tString, vector<FileObject*>* CurrentFileList);
void ShowCurrentDir(vector<FileObject>*, string * ls_current_dir, bool tHidden = true, bool tFolderOnly = false);
void DisplayUI();

/*
 *Planer:
 * Lägg till lite minneshantering så att jag inte läcker som ett såll.
 * Kolla hur man identifierar "mExecutable" filer.
 * Execute "mExecutable" filer. (troligen lättast att prova med ett kommando)
 * Separera ut logiken lite så att det blir lättare att porta till ett GUI, gör funktioner av skiten.
 * 
 * Fixa lite kommentarer så jag förstår vad fan jag sysslar med.
 * 
 * Långtidsplaner:
 * Separera användbar kod till en logisk kärna man kan använda från olika UI'n, testa detta först i konsoll UI't.
 * QT-creator för att göra ett grundläggande GUI, endast för att visa /home/bergman/ först.
 * Lägg till navigationsmöjligheter till GUI:t.
 * Undersök hur andra filhanterare parsar filer, t.ex. Dolphin, använder troligen inte ls.
 * Lägg till specialfall för .exe-filer att använda wine.
 */

int main()
{
    bool exit = false, ShowHiddenFiles = false;
    cout << "\n";
    string *ls_current_dir = new string("/home/bergman/");
    //myStream.open();
    
    string choice = "1", tempstring = "";
    int newDirectoryNR = 0;
    vector<FileObject>* CurrentFileList = new vector<FileObject>;
    while(!exit)
    {
        //system("clear | clear");
        cout << "\nCurrent dir : " << *ls_current_dir << '\n';
        switch(stoi(choice))
        {
            case 2:
                //GOTO input directory #
                ShowCurrentDir(CurrentFileList, ls_current_dir, ShowHiddenFiles,  true);
                cout << "\n\nWhich directory would you like to enter? (.. for back):\n";
                getline(cin, tempstring);
                newDirectoryNR = stoi(tempstring);
                if(CurrentFileList->at(newDirectoryNR).GetFileName() == "../")
                    do{
                        ls_current_dir->pop_back();
                        if((ls_current_dir->back()) == '/')
                            break;
                    }while(true);
                else if((CurrentFileList->at(newDirectoryNR).GetFileName().back()) == '/') //if valid number append, if not display error message.
                {
                    string tempusStringus = CurrentFileList->at(newDirectoryNR).GetFileName();
                    for(int i = 0 ; i<tempusStringus.length() ; i++)
                        if(tempusStringus.at(i) == ' ')
                        {
                            tempusStringus.insert(i,"\\");
                            ++i;
                        }
                    ls_current_dir->append(tempusStringus);
                }
                else
                {
                    cout << "\n\nThat was not a folder :(  !! \n\n";
                    getline(cin, tempstring);
                }
            case 1:
                ShowCurrentDir(CurrentFileList, ls_current_dir, ShowHiddenFiles);
                DisplayUI();
            break;
            case 3:
                if(ShowHiddenFiles)
                    ShowHiddenFiles = false;
                else
                    ShowHiddenFiles = true;
                ShowCurrentDir(CurrentFileList, ls_current_dir, ShowHiddenFiles);
                DisplayUI();
            break;
            case 0:
                exit = true;
                
        }
        CurrentFileList->clear();
        getline(cin, choice);
    }
    delete ls_current_dir;
    delete CurrentFileList;
    return 0;
}

void PrintLocationToFile(string * ls_current_dir)
{
    string tempstring = "";
        tempstring.append(string(" ls -f --file-type "));
        tempstring.append(*ls_current_dir);
        tempstring.append(string(" > "));
        tempstring.append(home_dir);
        tempstring.append("filename");
    system(tempstring.c_str());
    cout << '\n';
}

void ParseMyString(string tString, vector<FileObject> *CurrentFileList)
{
    bool tHidden = false, tFolder = false, tExecutable = false;
    if(tString.at(0) == '.')
        tHidden = true;
    if(tString.at(tString.length()-1) == '/')
        tFolder = true;
    
    CurrentFileList->push_back(FileObject(tString));
    CurrentFileList->at(CurrentFileList->size()-1).FileType(tHidden, tFolder, tExecutable);
        
}


void ShowCurrentDir(vector<FileObject>* CurrentFileList, string * ls_current_dir, bool tHidden, bool tFolderOnly)
{
    ifstream myStream("/home/bergman/Documents/c++/filemanager/source/filename", ifstream::in);
    PrintLocationToFile(ls_current_dir);
    PrintLocationToFile(ls_current_dir);
    string myString[256];
    char myChar = '.';
    for(int i = 0, n = 0 ; myStream.eof() != true ; i++)
    {
        getline(myStream, myString[i]);
    }
    for(int i = 0 ; i<256 && myString[i] != "" ; i++)
        ParseMyString(myString[i], CurrentFileList);
    myStream.close();
    for(int i = 0; i < CurrentFileList->size() ; i++)
    {
        if(!tHidden || !CurrentFileList->at(i).GetHidden())
        {
            if(CurrentFileList->at(i).GetFolder())
                    cout << i << ") " << CurrentFileList->at(i).GetFileName() << "                                               <---  Folder!\n";
            else if(!tFolderOnly)
                cout << CurrentFileList->at(i).GetFileName() << "                                               <---  Not a Folder :(!\n";
        }
    }
}

void DisplayUI()
{
    cout << "\n1: Update current directory.\n2: Switch directory.\n3: Toggle show hidden.\n0: Exit.\n Input : ";
}
