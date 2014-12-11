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
    m_lock.lock();
    m_values[name] = value;
    m_lock.unlock();
}

void server_variables::add_float(std::string name, float value){
    add_variable(name, std::to_string(value));
}

std::string server_variables::get_value(std::string name){
    std::string temp;
    m_lock.lock();
    temp = m_values[name];
    m_lock.unlock();
    return temp;
}

bool server_variables::value_exists(std::string name){
    return get_value(name)!="";
}

void server_variables::delete_variable(std::string name){
    m_lock.lock();
    if(m_values.find(name)!=m_values.end()){
        m_values.erase(m_values.find(name));
    }
    m_lock.unlock();
}