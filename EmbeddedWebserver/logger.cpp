//
//  logger.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 12/8/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "logger.h"

void logger::log(std::string message, severity l){
    log_item logI;
    logI.message = message;
    logI.level = l;
    m_lock.lock();
    m_logs.push_back(logI);
    m_lock.unlock();
}

std::string logger::generate_html(){
    std::string ret = "";
    m_lock.lock();
    ret += "<table class='table table-striped'>";
    ret += "<th>Number</th><th>Message</th>\n";
    for (unsigned int i = 0; i<m_logs.size(); i++) {
        switch(m_logs[i].level){
            case kNone:
                ret += "<tr>";
                break;
            case kLow:
                ret += "<tr class='warning'>";
                break;
            case kHigh:
                ret += "<tr class='danger'>";
                break;
                
        }
        ret += "\n";
        ret += "<td>"+std::to_string(i)+"</td><td>"+m_logs[i].message+"</td>\n";
        ret += "</tr>\n";
    }
    ret += "</table>";
    m_lock.unlock();
    return ret;
}