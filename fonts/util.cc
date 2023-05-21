#include <vector>
#include <iostream>
#include <sstream>
#include "util.h"
using namespace std;

vector<string> split(string str, char spliter){
    vector<string> splited_str;
    string s = "";
    for(int i = 0; i < str.size(); i++){
        if((i<str.size()-1)&&str[i]==spliter&&(str[i-1]=='"')&&(str[i+1]=='"')){
            splited_str.push_back(s.substr(1,s.size()-2));
            s = "";
        } else{
            s+=str[i];
        }
    }
   splited_str.push_back(s.substr(1,s.size()-2));
     
   /*for(int i = 0; i < splited_str.size(); i++){
        cout<<splited_str[i]<<endl;
    }*/
    
    return splited_str;

}

int fhash(int chave){
    return (chave%13);
}
int int_to_str(string str){
    int num;
    stringstream ss;
    ss<<str;
    ss>>num;

    return num;
}
