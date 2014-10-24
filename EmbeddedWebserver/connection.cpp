//
//  connection.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 10/23/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "connection.h"

connection::connection(unsigned short socket_fd)
{
    this->m_socket_fd = socket_fd;
    //Assume Socket Opened already when making this class
    this->m_open = true;
}

bool connection::write_string(std::string message)
{
    return write_bytes((void *)message.c_str(), message.size());
}

bool connection::write_bytes(void *bytes, unsigned short size)
{
    return (send(this->m_socket_fd,bytes,size,0)==size);
}

void connection::close_socket()
{
    if(this->m_open)
    {
        close(this->m_socket_fd);
    }
    this->m_open = false;
}

void connection::set_timeout(unsigned int millis)
{
    struct timeval timeout;
    timeout.tv_sec = millis/1000;
    timeout.tv_usec = (millis%1000)*1000;
    
    if (setsockopt (this->m_socket_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout)) < 0)
        std::cout<<"Failed to Set SO_RCVTIME0"<<std::endl;
    
    if (setsockopt (this->m_socket_fd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(timeout)) < 0)
        std::cout<<"Failed to Set SO_SNDTIME0"<<std::endl;
}

connection::~connection()
{
    close_socket();
}