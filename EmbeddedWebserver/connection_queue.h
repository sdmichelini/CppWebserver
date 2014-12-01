//
//  connection_queue.h
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 11/24/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#ifndef __EmbeddedWebserver__connection_queue__
#define __EmbeddedWebserver__connection_queue__

#include <iostream>
#include <deque>
#include <thread>
#include <mutex>
#include <atomic>
#include "connection.h"
#include "http_processor.h"


class connection_queue{
public:
    connection_queue();
    void start();
    void stop();
    void add_client(int socketFd);
    bool is_running(){
        return m_running;
    }
    std::mutex m_lock;
    ~connection_queue();
private:
    static void process_dispatch(connection_queue * queue);
    void process_clients();
    
    //Thread for running the queue
    std::thread * m_dispatchThread;
    
    http_processor * processor;
    
    //For adding to the queue
    std::condition_variable m_condition;
    
    //Holds all the clients
    std::deque<connection*> m_clients;
    
    std::atomic<bool>m_running;
};

#endif /* defined(__EmbeddedWebserver__connection_queue__) */
