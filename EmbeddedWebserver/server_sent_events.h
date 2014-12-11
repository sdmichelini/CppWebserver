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
#include <vector>

class server_sent_events{
public:
    static server_sent_events& get_instance(){
        static server_sent_events s;
        return s;
    }
private:
    server_sent_events();
    server_sent_events(server_sent_events const&);
    void operator=(server_sent_events const&);
};

#endif /* defined(__EmbeddedWebserver__server_sent_events__) */
