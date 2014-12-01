//
//  connection.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 10/23/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "connection.h"

#define BUFFER_SIZE 1024

connection::connection(int socket_fd)
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

std::string connection::recieve_string()
{
    char buf[BUFFER_SIZE];
    size_t rc = recv(this->m_socket_fd,buf,BUFFER_SIZE,0);
    if(rc<1)
    {
        std::cout<<"connection: Recieve Error"<<std::endl;
        return "";
    }
    else
    {
        //Append NULL terminating character to string
        buf[rc]=(char)NULL;
        return std::string(buf);
    }
}

void connection::close_socket()
{
    if(this->m_open)
    {
        std::cout<<"closed connection"<<std::endl;
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