//
//  connection_queue.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 11/24/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "connection_queue.h"

connection_queue::connection_queue(){
    m_running = false;
    processor = new http_processor();
}

void connection_queue::start(){
    m_running = true;
    m_dispatchThread = new std::thread(connection_queue::process_dispatch,this);
}

void connection_queue::stop(){
    if(m_running)
    {
        m_running = false;
        m_dispatchThread->join();
    }
    m_clients.erase(m_clients.begin(),m_clients.begin() + m_clients.size());
}

void connection_queue::add_client(int socketFd){
    std::unique_lock<std::mutex> lk(m_lock);
    m_clients.push_back(new connection(socketFd));
    m_lock.unlock();
    m_condition.notify_one();
}

void connection_queue::process_dispatch(connection_queue *queue)
{
    queue->process_clients();
}

void connection_queue::process_clients(){
    while(is_running()){
        std::unique_lock<std::mutex> lock(m_lock);
        while(m_clients.size() == 0){
            m_condition.wait(lock);
        }
        m_lock.unlock();
        //Process the client here
        connection * conn = m_clients.front();
        processor->process_client(conn);
        if(!conn->keep_open())
        {
            m_lock.lock();
            m_clients.pop_front();
            delete conn;
            m_lock.unlock();
        }else{
            //Connection now handled by other thread
            m_lock.lock();
            m_clients.pop_front();
            m_lock.unlock();
        }
    }
}

connection_queue::~connection_queue(){
    stop();
}