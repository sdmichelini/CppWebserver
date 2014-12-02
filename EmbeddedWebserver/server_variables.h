//
//  server_variables.h
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 12/1/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#ifndef __EmbeddedWebserver__server_variables__
#define __EmbeddedWebserver__server_variables__

#include <iostream>
#include <map>
#include <mutex>

class server_variables{
public:
    static server_variables& get_instance(){
        static server_variables s;
        return s;
    }
    void add_variable(std::string name, std::string value);
    void add_float(std::string name, float value);
    std::string get_value(std::string name);
    bool value_exists(std::string name);
    
    std::map<std::string, std::string> get_values(){
        std::map<std::string, std::string> ret;
        m_lock.lock();
        ret = m_values;
        m_lock.unlock();
        return ret;
    }
private:
    server_variables();
    server_variables(server_variables const&);
    void operator=(server_variables const&);
    std::map<std::string, std::string> m_values;
    std::mutex m_lock;
};

#endif /* defined(__EmbeddedWebserver__server_variables__) */
