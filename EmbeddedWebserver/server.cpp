//
//  server.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 10/23/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "server.h"

server::server(unsigned short port){
    this->m_port = port;
    this->m_running = false;
    this->m_listening = false;
    this->m_socketFd = 0;
    m_queue = new connection_queue();
}

bool server::begin(){
    if(m_listening){
        std::cout<<"Warning: Attempted to Call begin() after server was started"<<std::endl;
        return false;
    }
    
    struct sockaddr_in sSockInfo;//Socket Information Structure
    char myHostname[MAX_HOSTNAME];//Holder for HOSTNAME
    struct hostent * pHostName;//Pointer to our hostent
    
    memset(&sSockInfo, 0, sizeof(sockaddr_in));//Clear the memory of sSockInfo
    
    
    gethostname(myHostname,MAX_HOSTNAME-1);//Copy the system host name into myHostname
    
    if((pHostName=gethostbyname(myHostname))==NULL)//Check for Error in Getting Our Host
    {
        std::cout<<"Host Name Error on Server with Host Name: "<<myHostname<<std::endl;
        return false;
    }
    
    sSockInfo.sin_family = AF_INET;//IPv4
    
    sSockInfo.sin_addr.s_addr = htonl(INADDR_ANY);//Use any available address for the Server
    
    sSockInfo.sin_port = htons(m_port);//Port
    
    
    if((m_socketFd = socket(AF_INET,SOCK_STREAM,0))<0)//Create the socket
    {
        std::cout<<"Failure Creating the Socket"<<std::endl;
        return false;
    }
    
    int iOption = 1;  // Reuse address option to set, 0 = disables, 1 = enables
    
    if (setsockopt(m_socketFd, SOL_SOCKET, SO_REUSEADDR, (const char *) &iOption,  sizeof(int)) == -1)
    {
        std::cout << "Set reuse address: Client set reuse address option failed" << std::endl;
    }

    
    if(bind(m_socketFd,(struct sockaddr *)&sSockInfo,sizeof(sockaddr_in)) < 0)//Now bind the socket
    {
        std::cout<<"Failure Binding Socket"<<std::endl;
        std::cout<<"Error: "<<strerror(errno)<<std::endl;
        return false;
    }
    
    listen(m_socketFd,LISTEN_BACKLOG);//Listen
    m_listening = true;//Safeguard for Writing and Reading from Socket
    //Dispatch Thread
    m_queue->start();
    m_acceptThread = new std::thread(server::acceptClients,this);
    return true;
}

void server::stop(){
    m_queue->stop();
    if(m_listening){
        m_listening = false;
        close(m_socketFd);
    }
}
//This is the main thread for accepting clients
void server::acceptClients(server * s){
    while(s->is_listening()){
        //Accept the remote client
        int remoteClientFd = accept(s->get_raw_socket(),NULL,NULL);
        if(remoteClientFd > 0){
            //Dispatch Client Thread
            s->m_queue->add_client(remoteClientFd);
        }
        //Sleep some
        usleep(500);
    }
}

server::~server(){
    stop();
    m_acceptThread->join();
    delete m_queue;
}
