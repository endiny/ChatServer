/* 
 * File:   MessageHandler.h
 * Author: endiny
 *
 * Created on 18 мая 2015 г., 12:36
 */

#ifndef MESSAGEHANDLER_H
#define	MESSAGEHANDLER_H
#include <string>

class MessageHandler {
public:
    MessageHandler();
    virtual ~MessageHandler();
    static char* InputMessage(char* buffer);

};

#endif	/* MESSAGEHANDLER_H */

