//
//  constants.h
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 12/8/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#ifndef __EmbeddedWebserver__constants__
#define __EmbeddedWebserver__constants__

#include <iostream>
#include <map>
#include <mutex>

class constant{
public:
    static constant& get_instance(){
        static constant s;
        return s;
    }
    void add_constant(std::string name, std::string value);
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
    constant();
    constant(constant const&);
    void operator=(constant const&);
    std::map<std::string, std::string> m_values;
    std::mutex m_lock;
};

#endif /* defined(__EmbeddedWebserver__constants__) */
