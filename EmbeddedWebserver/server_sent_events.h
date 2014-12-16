//
//  server_sent_events.h
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 12/11/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#ifndef __EmbeddedWebserver__server_sent_events__
#define __EmbeddedWebserver__server_sent_events__

#include <iostream>
#include "json.h"
#include "server_variables.h"

#include "connection.h"
#include <vector>

//Update rate in milliseconds
#define DATA_UPDATE_RATE 200
//Microsconds per Millisecond
#define MICROS_PER_MILLI 1000

class server_sent_events{
public:
    static server_sent_events& get_instance(){
        static server_sent_events s;
        return s;
    }
    /*!
     @function create_event
     @brief Creates a Server-Sent Event
     @discussion
        Creates a Server-Sent Event with the array of variables to monitor
     @param vars
        Array of Variable names from server_variables
     @return 
        0 on failure, number > 0 on successful creations
     */
    unsigned long create_event(std::vector<std::string> vars);
    
    /*!
     @function get_event_data
     @brief Get's the current JSON data associated with an Event
     @return
        Blank String and JSON data corresponding to event id on success
     */
    std::string get_event_data(unsigned long eventId);
    
    static void dispatch_event(unsigned long eventId, connection * conn);
private:
    server_sent_events();
    server_sent_events(server_sent_events const&);
    void operator=(server_sent_events const&);
    ///Array of the arrays of the event data which is held as a variable
    std::vector<std::vector<std::string>> m_eventConfig;
    
    std::mutex dataMutex;
    
};

#endif /* defined(__EmbeddedWebserver__server_sent_events__) */
