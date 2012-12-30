#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

const string pathtodict = "all";

bool strncasecmpfunc(const string& str1, const string& str2) {
    if (str1.size() != str2.size()) {
        return false;
    }
    for (string::const_iterator c1 = str1.begin(), c2 = str2.begin(); c1 != str1.end(); ++c1, ++c2) {
        if (tolower(*c1) != tolower(*c2)) {
            return false;
        }
    }
    return true;
}

string inttostr(int num)
{
   stringstream sstr;
   sstr << num;
   return sstr.str();
}

void processword(string * str1, int pos)
{
    while (str1->length()>0)
    {
        if (pos>=str1->length())
            pos=str1->length()-1;
    if (ispunct(str1->at(pos)))
            str1->erase(pos,1);
    else
        break;
    }
}

void processword(string& str1)
{
    string s;
    for (string::iterator c1 = str1.begin(); c1 < str1.end()-2; ++c1)
    {
        s=(char)(*c1);
        s+=(char)(*(c1+1));
        s+=(char)(*(c1+2));
        if (s=="ﬁ")
            {
            //cout<<"FOUND ﬁ\n";
                (*c1)='f';
                str1.erase(c1+1,c1+2);
                (*(c1+1))='i';
            }
        else
            if (s=="ﬀ")
                {
                    //cout<<"FOUND ﬀ\n";
                    (*c1)='f';
                    str1.erase(c1+1,c1+2);
                    (*(c1+1))='f';
                }
            else
                if (s=="ﬂ")
                    {
                        //cout<<"FOUND ﬂ\n";
                        (*c1)='f';
                        str1.erase(c1+1,c1+2);
                        (*(c1+1))='l';
                    }
                else
                    if (s=="ﬃ")
                        {
                            //cout<<"FOUND ﬃ\n";
                            (*c1)='f';
                            (*(c1+1))='f';
                            (*(c1+2))='i';
                        }
                    else
                        if (s=="ﬄ")
                            {
                                //cout<<"FOUND ﬄ\n";
                                (*c1)='f';
                                (*(c1+1))='f';
                                (*(c1+2))='l';
                            }
                        else
                            if (s=="ﬅ" || s=="ﬆ")
                                {
                                    //cout<<"sFOUND ﬅ or ﬆ\n";
                                    (*c1)='s';
                                    str1.erase(c1+1,c1+2);
                                    (*(c1+1))='t';
                                }
    }
}

bool isnotsymb(const string& str1)
{
    bool havechars=false;
    for (string::const_iterator c1 = str1.begin(); c1 != str1.end(); ++c1)
    {
        if (isalpha(*c1))
        {
            havechars=true;
            break;
        }
    }
    return havechars;
}

typedef multimap <string, string> DIndex;
typedef set <string> Dict;

void saveDIndex(string path, DIndex* d1)
{
    ofstream index;
    ifstream test(path.c_str());
            if (test.is_open())
            {
                test.close();
                index.open(path.c_str(),ios_base::out | ios_base::app);
            }
            else
            {
                index.open(path.c_str(),ios_base::out | ios_base::trunc);
            }

    if (index.is_open())
    {
        for (DIndex::const_iterator it = d1->begin(); it != d1->end(); it++)
        {
          index<< (*it).first << "\n";
          index<< (*it).second << "\n";
        }

    index.close();
    }
    else
    {
        cout<<"Can't open index file "<<path<< "\n";
    }
}

void saveWord(string newword)
{
    ofstream words;
    string wpath = pathtodict;
    words.open(wpath.c_str(),ios_base::out | ios_base::app);
    if (words.is_open())
    {
        words << newword << "\n";
        words.close();
    }
    else
    {
        cout<<"Can't access dictionary "<<wpath<< "\n";
    }
}

void loadDIndex(string dfile, DIndex* i1)
{
    ifstream inp;
    string temp1,temp2;
    inp.open(dfile.c_str());
    if (inp.is_open())
    {
        while (getline(inp,temp1))
        {
            getline(inp,temp2);
            i1->insert(std::pair<string, string>(temp1,temp2));
        }
        inp.close();
    }
    else
    {
        cout<<"No such file - "<<dfile<< "\n";
    }
}

void loadwords(Dict* d1)
{
    ifstream words;
    string temps;
    string wpath = pathtodict;
    words.open(wpath.c_str());
    if (words.is_open())
    {
    while (getline(words,temps))
        d1->insert(temps);
    words.close();
    }
    else
    {
        cout<<"No such file - "<<wpath<< "\n";
    }
}

int main()
{
    string DIndexfile="default.dict";
    DIndex DIndex1;
    Dict Dict1;
    int choice=0;
    int askkey=1;
    cout<<"Loading default dict...\n";
    loadDIndex(DIndexfile,&DIndex1);
    cout<<"Done.\n";
    while (choice!=5)
    {
        cout<<"What shall we do? 0- select dict file (by default, default.dict is used,\n";
        cout<<"1 - add to current dict some directory, 2 - search for record in dict\n";
        cout<<"3 - exclude some directory from current dict, 4 - save dict, 5 -exit\n";
        cin>>choice;
        switch (choice)
        {
        case 0:
            {
                cout<< "Enter dictfile relative or full path"<< "\n";
                cin>>DIndexfile;
                cout<<"Loading user dict...\n";
                loadDIndex(DIndexfile,&DIndex1);
                cout<<"Done.\n";
            }
        case 1:
            {
            string path;
                cout<<"********************"<< "\n";
                cout<<"    ADD DIRECTORY   "<< "\n";
                cout<<"Loading words..."<< "\n";
                loadwords(&Dict1);
                cout<<"Done.";
                cout<<"Enter full or relative directory path, or 0 not to scan pdf's & use textfiles in this dir"<< "\n";
                cin>> path;
                string s;
                if (path!="0")
                {
                    if (path.at(path.length()-1)!='/')
                        path+="/";
                    s="~/artdict/pdft.sh "+path+" "+"~/artdict/";
                    system(s.c_str());
                }
                ifstream inp;
                inp.open("numfiles.txt");
                if (inp.is_open())
                {
                    inp >> s;
                    inp.close();
                    int num=atoi(s.c_str());
                    cout<<"Total number of pdf files: "<<num<<"\n";
                    string key,value;
                    for (int i=0; i<=num; i++)
                    {
                        inp.open(inttostr(i).c_str());
                        if (inp.is_open())
                        {
                            inp.seekg (0, ios::end);
                            int length = inp.tellg();
                            inp.seekg(length-min(length,2048),ios::beg); // seek back from end
                            while (getline(inp, s))
                            {
                               value=s;
                            }
                            //cout<<value<<"\n";
                            //inp.seekg (0, ios::beg);
                            inp.close();
                            inp.open(inttostr(i).c_str());
                            while (getline(inp, s))
                            {
                                //cout<<s<<"\n";
                                istringstream isstr(s);
                                while (isstr >> key)
                                {
                                    //cout<<key<<"\n";
                                    if (isnotsymb(key))
                                    {
                                        processword(&key,0);//delete punctuation signs at the beginning
                                        processword(&key,key.length()-1);//and at the end
                                        processword(key);
                                        DIndex::iterator it = DIndex1.find(key);
                                        bool found=false;
                                        if (it != DIndex1.end())
                                        {
                                            pair<DIndex::iterator,DIndex::iterator> range_r = DIndex1.equal_range(key);
                                               for (it=range_r.first; it!=range_r.second; ++it)
                                            {
                                              if (strncasecmpfunc((*it).second, value))
                                              {
                                                  found=true;
                                                  break;
                                              }
                                            }
                                        }

                                        if (!found)
                                            //if no such key was found, insert element
                                        {
                                            string key_l=key;
                                            transform(key_l.begin(), key_l.end(),key_l.begin(), ::tolower);
                                            Dict::iterator wit = Dict1.find(key_l);
                                            if (wit != Dict1.end()) //if word was found in dictionary
                                                //DIndex1.insert(std::pair<string, string>(key,new DItem(value)));
                                                DIndex1.insert(std::pair<string, string>(key,value));
                                            else
                                                if (askkey>0)
                                                {
                                                    int ans=1;
                                                    if (askkey==1)
                                                    {
                                                    cout<<"The word "<<key<<" doesn't exist in dictionary. Add? (0 - no, 1- yes, 2- autocommit all, other - autodecline all \n";
                                                    cout<<key<<" ----  ";
                                                    cin >> ans;
                                                    }
                                                    switch (ans)
                                                    {
                                                    case 0:
                                                    {break;}
                                                    case 1:
                                                    {   Dict1.insert(key);
                                                        DIndex1.insert(std::pair<string, string>(key,value));
                                                        saveWord(key);
                                                        break;}
                                                    case 2:
                                                    {   Dict1.insert(key);
                                                        DIndex1.insert(std::pair<string, string>(key,value));
                                                        saveWord(key);
                                                        askkey=2;
                                                        break;
                                                    }
                                                    default:
                                                    {askkey=0;}
                                                    }
                                                }
                                        }//end of "key not found" condition
                                    }
                                }// end of line
                            }//end of file

                            inp.close();
                        }// end of file exists
                        else
                        {
                            cout<<"Skipping unreadable "<<i<<": key";
                        }
                    }//end of all files
                }// end of numfiles.txt exists
                else
                {
                    cout<<"Error took place while opening numfiles.txt"<< "\n";
                }
                break;
            }
        case 2:
            {
            string key;
            cout<<"Input search string:\n";
            cin >> key;
            cout<<"Searching...\n";
            DIndex::iterator it;
            pair<DIndex::iterator,DIndex::iterator> range_r = DIndex1.equal_range(key);
            cout<<"Found\n";
            int k=0;
               for (it=range_r.first; it!=range_r.second; ++it)
            {
                   k++;
                   cout<<(*it).second<<"\n";
            }
               cout<<"Total "<<k<<" records found.\n";
               break;
            }
        case 3:
            {
            break;
            }
        case 4:
            {
            cout<<"Saving \""<<DIndexfile<<"\" dict...\n";
            saveDIndex(DIndexfile,&DIndex1);
            cout<<"Done.\n";
            break;
            }
        default:
        {
            break;
        }
        }
    }



    return 0;
}
