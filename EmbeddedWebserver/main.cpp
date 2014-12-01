//
//  main.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 10/1/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "server.h"
#include <signal.h>


server * s;

int main(int argc, const char * argv[]) {
    
    // insert code here...
    std::cout << std::string("HTTP/1.1 200 OK\r\nContent-Type: text/xml; charset=utf-8\r\nContent-Length: \r\n").size()<<std::endl;
    
    s = new server(10000);
    if(!s->begin()){
        std::cout<<"error"<<std::endl;
        return 1;
    }
    
    while(1){
        usleep(5000);
    }
    return 0;
}
