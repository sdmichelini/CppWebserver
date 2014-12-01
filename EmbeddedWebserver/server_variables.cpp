//
//  server_variables.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 12/1/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "server_variables.h"

server_variables::server_variables(){
    
}

void server_variables::add_variable(std::string name, std::string value){
    m_values[name] = value;
}

void server_variables::add_float(std::string name, float value){
    m_values[name] = std::to_string(value);
}

std::string server_variables::get_value(std::string name){
    return m_values[name];
}

bool server_variables::value_exists(std::string name){
    return m_values[name]!="";
}