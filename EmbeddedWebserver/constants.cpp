//
//  constants.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 12/8/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "constants.h"

constant::constant(){
    
}

void constant::add_constant(std::string name, std::string value){
    m_lock.lock();
    m_values[name] = value;
    m_lock.unlock();
}

void constant::add_float(std::string name, float value){
    add_constant(name, std::to_string(value));
}

std::string constant::get_value(std::string name){
    std::string temp;
    m_lock.lock();
    temp = m_values[name];
    m_lock.unlock();
    return temp;
}

bool constant::value_exists(std::string name){
    return get_value(name)!="";
}