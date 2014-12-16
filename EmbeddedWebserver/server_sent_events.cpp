//
//  server_sent_events.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 12/11/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "server_sent_events.h"

server_sent_events::server_sent_events(){
    
}

unsigned long server_sent_events::create_event(std::vector<std::string> vars){
    size_t size;
    dataMutex.lock();
    m_eventConfig.push_back(vars);
    size = m_eventConfig.size();
    dataMutex.unlock();
    return size;
}

std::string server_sent_events::get_event_data(unsigned long eventId){
    dataMutex.lock();
    if(eventId > m_eventConfig.size()){
        dataMutex.unlock();
        return "";
    }
    else{
        json::json_data eventData;
        for(auto i = 0; i < m_eventConfig[eventId - 1].size(); i++){
            //Check if event data exists
            if(server_variables::get_instance().get_values().find(m_eventConfig[eventId - 1][i]) != server_variables::get_instance().get_values().end()){
                eventData[m_eventConfig[eventId - 1][i]] = server_variables::get_instance().get_values()[m_eventConfig[eventId - 1][i]];
            }
        }
        dataMutex.unlock();
        return json::map_to_json(eventData);
    }
}

void dispatch_event(unsigned long eventId, connection * conn){
    bool finished = false;
    while(!finished){
        finished = (conn->write_string(server_sent_events::get_instance().get_event_data(eventId)))<=0;
        usleep(MICROS_PER_MILLI * DATA_UPDATE_RATE);
    }
}