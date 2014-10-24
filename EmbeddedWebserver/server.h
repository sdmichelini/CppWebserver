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
/*!
 @class server
 @brief Base-Server Class
 @discussion Server class which manages clients and listens on a specified port and ip
 */
class server{
public:
    server(std::string ip, unsigned short port);
    void begin();
    void stop();
    //Server Status Variables
    bool is_running()
    {
        return m_running;
    }
    unsigned short get_port()
    {
        return m_port;
    }
    std::string get_ip()
    {
        return m_ip;
    }
    
private:
    unsigned short m_port;
    std::string m_ip;
    bool m_running;
};

#endif /* defined(__EmbeddedWebserver__server__) */
