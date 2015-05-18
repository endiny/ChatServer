/* 
 * File:   User.cpp
 * Author: endiny
 * 
 * Created on 18 мая 2015 г., 16:52
 */

#include "User.h"

User::User() 
{
    f_in.open("users");
    if (!f_in.good())
        return;
    
    std::string tmp;
    
    while (!f_in.eof())
    {
        std::getline(f_in,tmp);
        users.insert(StrToPair(tmp));
    }
}


User::~User() 
{
    
}

bool User::SignUp(char* msg)
{
    if (!msg) return 0;
    std::pair<std::string,std::string> a(StrToPair(std::string(msg)));
    if (users.find(a.first)!=users.end()) 
        return 0;
    users.insert(a);
    return 1;
}

void User::WriteFile() 
{
    f_out.open("users");
    for (std::map<std::string,std::string>::iterator i=users.begin();
            i!=users.end(); i++)
    {
        f_out << i->first << " " << i->second << std::endl;
    }
}


std::pair<std::string,std::string> User::StrToPair(std::string str)
{
    if (str[0]=='/' && str[4]==' ')
        str=str.substr(5);
    std::string login,hash;
    int space=str.find_first_of(' ');
    login=str.substr(0,space);
    hash=str.substr(space+1,str.find_first_of(' ',space+1)-(space+1));
    return std::make_pair<std::string,std::string>(login,hash);
}

std::string User::CreateToken()
{
    std::time_t stamp(std::time(0));
    std::stringstream strm;
    strm<<stamp;
    return strm.str();
}

bool User::LogIn(char *msg)
{
    std::pair<std::string,std::string> a(StrToPair(std::string(msg)));
    if (tokens.find(a.first)!=tokens.end())
        return 0;
    std::map<std::string,std::string>::iterator i=users.end();
    if (i==tokens.end())
        return 0;
    if (i->second!=a.second)
        return 0;
    a.second = CreateToken();
    tokens.insert(a);
    return 1;
}

char* User::CheckToken(char* msg)
{
    std::string token;
    std::string temp=msg;
    temp=temp.substr(5);
    token=temp.substr(0,temp.find_first_of(' '));
    temp = temp.substr(temp.find_first_of(' ')+1);
    if (tokens.find(token)!=tokens.end())
        return (char*)temp.c_str();
    else 
        return 0;
}