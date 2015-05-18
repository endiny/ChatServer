/* 
 * File:   MessageHandler.cpp
 * Author: endiny
 * 
 * Created on 18 мая 2015 г., 12:36
 */

#include "MessageHandler.h"

MessageHandler::MessageHandler() 
{
    user=new User();
}

MessageHandler::~MessageHandler() {
}

char* MessageHandler::InputMessage(char* buffer)
{
    std::string temp;   
    char *value;
    temp=buffer;
    if (temp.substr(0,4)=="/msg")
    {
        return user->CheckToken(buffer);
    }
    if (temp.substr(0,4)=="/reg")
        return (char*)(user->SignUp(buffer)?"/reg 1":"/reg 0");
    if (temp.substr(0,4)=="/log")
        return (char*)(user->LogIn(buffer)?"/log1":"/log 0");
    else return NULL;
}