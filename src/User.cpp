/* 
 * File:   User.cpp
 * Author: endiny
 * 
 * Created on 18 мая 2015 г., 16:52
 */

#include "User.h"

User::User() {
}

User::User(const User& orig) {
}

User::~User() {
}

bool User::SignUp(char* msg)
{
    std::string temp=msg;
    std::string word;
    int space=temp.find_first_of(' ');
    std::string login=temp.substr(space+1,temp.find_first_of(' ',space+1)-(space+1));
    space=temp.find_first_of(' ',space+1);
    f_in.open("users");
    while (f_in >> word)
    {
        if (word==login)
            return 0;
    }
    
    f_in.close();
    f_out.open("users", std::ofstream::app | std::ofstream::out);
    f_out << login << " " << temp.substr(space+1,temp.find_first_of(' ',space+1))
            << std::endl;
    f_out.close();
    return 1;
    
    
}
