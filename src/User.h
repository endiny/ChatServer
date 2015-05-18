/* 
 * File:   User.h
 * Author: endiny
 *
 * Created on 18 мая 2015 г., 16:52
 */

#ifndef USER_H
#define	USER_H

#include <fstream>
#include <crypt.h>
#include <string>
#include <map>
#include <utility>
#include <ctime>
#include <sstream>

class User {
public:
    User();
    User(const User& orig);
    virtual ~User();
    bool SignUp(char* msg);
    char* LogIn(char *msg);
    char* CheckToken(char* msg);
private:
    std::pair<std::string,std::string> StrToPair(std::string str);
    std::map<std::string, std::string> users;
    std::map<std::string, std::string> tokens;
    
    void WriteFile();
    std::string CreateToken();
    
    std::ifstream f_in;
    std::ofstream f_out;
};

#endif	/* USER_H */

