//
//  logger.h
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 12/8/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#ifndef __EmbeddedWebserver__logger__
#define __EmbeddedWebserver__logger__

#include <vector>
#include <string>
#include <mutex>

enum severity{
    kNone = 0,
    kLow = 1,
    kHigh = 2
};

class logger{
public:
    static logger& get_instance(){
        static logger s;
        return s;
    }
    std::string generate_html();
    
    void log(std::string message, severity l = kNone);
    
    struct log_item{
        std::string message;
        severity level;
    };
private:
    logger(){}
    logger(logger const&){}
    void operator=(logger const&){}
    
    std::vector<log_item> m_logs;
    
    std::mutex m_lock;
};

#endif /* defined(__EmbeddedWebserver__logger__) */
