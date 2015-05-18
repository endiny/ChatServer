/* 
 * File:   MessageHandler.cpp
 * Author: endiny
 * 
 * Created on 18 мая 2015 г., 12:36
 */

#include "MessageHandler.h"

MessageHandler::MessageHandler() {
}

MessageHandler::~MessageHandler() {
}

char* MessageHandler::InputMessage(char* buffer)
{
    std::string temp;
    temp=buffer;
    if (temp.substr(0,4)=="/msg")
    {
        char *b;
        b = (char*)temp.c_str();
        return b;
    }
    else return NULL;
}

