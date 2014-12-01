//
//  echo_processor.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 11/24/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "echo_processor.h"

void echo_processor::process_client(connection * conn){
    std::string read = conn->recieve_string();
    std::cout<<"Read from Socket: "<<read<<std::endl;
    conn->write_string(read);
}