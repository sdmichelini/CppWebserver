//
//  main.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 10/1/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "server.h"
#include "logger.h"
#include "constants.h"
#include "json.h"
#include <signal.h>


server * s;

int main(int argc, const char * argv[]) {
    
    s = new server(10000);
    logger::get_instance().log("Server Init.");
    constant::get_instance().add_constant("MyConstant", "TestValue");
    constant::get_instance().add_constant("MyConstant1", "TestValue");
    
    if(!s->begin()){
        std::cout<<"error"<<std::endl;
        return 1;
    }
    logger::get_instance().log("Server Started.");
    logger::get_instance().log("Test Error",kHigh);
    while(1){
        usleep(5000);
    }
    return 0;
}
