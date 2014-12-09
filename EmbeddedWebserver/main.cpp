//
//  main.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 10/1/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "server.h"
#include "constants.h"
#include <signal.h>


server * s;

int main(int argc, const char * argv[]) {
    
    s = new server(10000);
    constant::get_instance().add_constant("My Constant", "Test Value");
    
    if(!s->begin()){
        std::cout<<"error"<<std::endl;
        return 1;
    }
    
    while(1){
        usleep(5000);
    }
    return 0;
}
