/* 
 * File:   MessageHandler.h
 * Author: endiny
 *
 * Created on 18 мая 2015 г., 12:36
 */

#ifndef MESSAGEHANDLER_H
#define	MESSAGEHANDLER_H
#include <string>
#include "User.h"

class MessageHandler {
public:
    MessageHandler();
    virtual ~MessageHandler();
    char* InputMessage(char* buffer);
    std::string CheckToken();
private:
    User *user;
    
};

#endif	/* MESSAGEHANDLER_H */

