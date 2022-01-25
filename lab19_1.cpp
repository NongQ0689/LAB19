#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned int i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename , vector<string> &names ,vector<int> &scores , vector<char> &grades)
{
    ifstream source(filename);
    string input ;
    char format[] = "%[^:]: %f %f %f";
    char scanname[50] ;
    float a,b,c;
    while (getline(source,input))
    {
        const char *text = input.c_str();
        sscanf(text,format,scanname,&a,&b,&c);

        names.push_back(scanname);
        scores.push_back(a+b+c);
        grades.push_back(score2grade(a+b+c));
    }
}

void getCommand(string &command, string &key){

    cout<<"Please input your command: ";

    string input;
    getline(cin,input);
    const char *text = input.c_str();
    char format[] = "%s %[^:] ";
    char cm[20] , k[20] ;
    sscanf(text,format,&cm,&k);
    command = cm;
    key = k; 
}

void searchName(vector<string> &names , vector<int> &score ,vector<char> &grade , string &key){
    cout<<"---------------------------------\n";
    bool find ;
    for(unsigned int i = 0 ; i < names.size(); i++)
    {
        if(toUpperStr(names[i])==key)
        {
            cout<<names[i]<<"'s "<<"score = "<<score[i]<<"\n";
            cout<<names[i]<<"'s "<<"grade = "<<grade[i]<<"\n";
            find = true;
        }
    }
    if(!find) cout<<"Cannot found.\n";
    cout<<"---------------------------------\n";
}

void searchGrade(vector<string> &names , vector<int> &score ,vector<char> &grade , string &key){
    cout<<"---------------------------------\n";
    const char *constcharkey = key.c_str();
    char KEY = *constcharkey;
    for(unsigned int i =0 ; i < names.size(); i++)
    {
        if(grade[i]==KEY)
        {
            cout<<names[i]<<" ("<<score[i]<<")\n";
        }
    }
    cout<<"---------------------------------\n";

}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
