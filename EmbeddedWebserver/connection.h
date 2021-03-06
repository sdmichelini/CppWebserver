//
//  connection.h
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 10/23/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#ifndef __EmbeddedWebserver__connection__
#define __EmbeddedWebserver__connection__

#include <string>
#include <iostream>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

/*!
 @class connection
 @brief Manages a Connection to a Remote Socket
 @discussion Handle's all communication to a remote host. Abstracts away from BSD sockets
 */
class connection{
public:
    /*!
     @function connection
     @brief Create's an instance of the connection class
     @param socket_fd
        BSD Socket File Descriptor
     */
    connection(int socket_fd);
    size_t write_string(std::string message);
    /*!
     @function write_bytes
     @brief Write's Raw Bytes to a Socket
     @param bytes
        Bytes to write to socket
     @param size
        Size of Bytes to be written to socket
     @return 
        True if all bytes are sent, false on error
     */
    size_t write_bytes(void * bytes, unsigned short size);
    std::string recieve_string();
    void close_socket();
    void set_timeout(unsigned int millis);
    
    bool bytes_available();
    
    void stay_open(){
        m_stay_open = true;
    }
    
    void dont_stay_open(){
        m_stay_open = false;
    }
    
    bool keep_open(){
        return m_stay_open;
    }
    
    bool is_closed()
    {
        return m_open;
    }
    int get_raw_socket()
    {
        return m_socket_fd;
    }
    ~connection();
private:
    int m_socket_fd;
    bool m_open;
    bool m_stay_open;
};

#endif /* defined(__EmbeddedWebserver__connection__) */
