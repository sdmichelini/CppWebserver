//
//  server.h
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 10/23/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#ifndef __EmbeddedWebserver__server__
#define __EmbeddedWebserver__server__

#include <iostream>
#include <string>
#include <iostream>
//Has memcpy
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
//C++11 threading
#include <thread>
#include <atomic>
#include "connection_queue.h"

///Max Size of Hostname
#define MAX_HOSTNAME 255
///Size of listen backlog
#define LISTEN_BACKLOG 5

/*!
 @class server
 @brief Base-Server Class
 @discussion Server class which manages clients and listens on a specified port and ip
 */
class server{
public:
    server(unsigned short port);
    bool begin();
    void stop();
    //Server Status Variables
    bool is_running()
    {
        return m_running;
    }
    bool is_listening(){
        return m_listening;
    }
    int get_raw_socket(){
        return m_socketFd;
    }
    unsigned short get_port()
    {
        return m_port;
    }
    virtual ~server();
private:
    connection_queue * m_queue;
    //Accepting Thread
    std::thread  * m_acceptThread;
    
    static void acceptClients(server * s);
    unsigned short m_port;
    bool m_running;
    std::atomic<bool> m_listening;
    int m_socketFd;
};

#endif /* defined(__EmbeddedWebserver__server__) */
