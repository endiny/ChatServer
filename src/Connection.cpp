/* 
 * File:   Connection.cpp
 * Author: endiny
 * 
 * Created on 17 мая 2015 г., 20:15
 */

#include "Connection.h"

Connection::Connection() 
{
    clients.clear();
    listener=socket(AF_INET, SOCK_STREAM, 0);
    if (listener<0)
    {
        std::cerr<<"socket init error\n";
        exit(1);
    }
    fcntl(listener, F_SETFL, O_NONBLOCK);
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(listener, (struct sockaddr*)&addr, sizeof(addr))<0)
    {
        std::cerr << "socket binding error\n";
        exit(2);
    }
    listen(listener,8);
}

void Connection::MainCycle()
{
    while(1)
    {
        fd_set readset;
        FD_ZERO(&readset);
        FD_SET(listener, &readset);
        
        for (std::set<int>::iterator i=clients.begin(); i != clients.end(); i++)
            FD_SET(*i, &readset);
        
        timeval timeout;
        timeout.tv_sec = 120;
        timeout.tv_usec = 0;
        
        int mx(std::max(listener, *(std::max_element(clients.begin(), clients.end()))));
        if (select(mx+1,&readset, NULL, NULL, &timeout) <= 0)
        {
            std::cerr << "Error selecting socket\n";
            exit(3);
        }
        
        if(FD_ISSET(listener, &readset))
        {
            int sock = accept(listener, 0, 0);
            std::cout<<"Opened socket\n";
            if (sock<0)
            {
                std::cerr << "Error accepting connection\n";
                exit(4);
            }
            fcntl(sock, F_SETFL, O_NONBLOCK);
            clients.insert(sock);
        }
        
        for (std::set<int>::iterator i=clients.begin(); i!=clients.end(); i++)
        {
            if (FD_ISSET(*i, &readset))
            {
                bytes_read = recv(*i, buffer, 1024, 0);
                MessageHandler::InputMessage(buffer);
                std::cout<<"[RECV]::"<<buffer<<std::endl;
                if (bytes_read<=0)
                {
                    close(*i);
                    clients.erase(*i);
                    std::cout << "Socket closed\n";
                    continue;
                }
                else
                    send(*i, buffer, bytes_read,0);
            }
        }
    }
}

Connection::~Connection() {
    for (std::set<int>::iterator i=clients.begin(); i!=clients.end(); i++)
        close(*i);
    close(listener);
    std::cout << "All was closed";
}

void Connection::SendToAll(char* msg)
{
    if (msg)
    {
        for (std::set<int>::iterator i=clients.begin(); i!=clients.end(); i++)
        {
            send(*i,const_cast<char*>(msg), 1024, 0);
        }
    }
}

