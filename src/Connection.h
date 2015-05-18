/* 
 * File:   Connection.h
 * Author: endiny
 *
 * Created on 17 мая 2015 г., 20:15
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <set>
#include <algorithm>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include "MessageHandler.h"

#ifndef CONNECTION_H
#define	CONNECTION_H

class Connection {
public:
    Connection();
    virtual ~Connection();
    void MainCycle();
private:
    int listener;
    struct sockaddr_in addr;
    char buffer[1024];
    void SendToAll(char *msg);
    int bytes_read;
    std::set<int> clients;
    MessageHandler *messageHandler;
};


#endif	/* CONNECTION_H */

