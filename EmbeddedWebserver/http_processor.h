//
//  http_processor.h
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 11/25/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#ifndef __EmbeddedWebserver__http_processor__
#define __EmbeddedWebserver__http_processor__

#include <map>
#include "server_processor.h"
#include "http_router.h"
#include "constants.h"
#include "server_variables.h"
#include "server_sent_events.h"
#include "logger.h"

#define MAX_PACKET_SIZE 1024

class http_processor:public server_processor{
public:
    http_processor();
    void process_client(connection * conn);
    void config_route(std::string path, http_router r);
private:
    const std::string ALL_VARIABLE_URL = "vars";
    const std::string VARIABLE_URL = "var";
    const std::string VARIABLE_REST = "var/:";
    const std::string CONSTANT_REST = "const/:";
    const std::string SSE_URL = "sse";
    const std::string CONSTANT_URL = "const";
    const std::string LOG_URL ="log";
    
    std::map<std::string, http_router> m_routes;
};

#endif /* defined(__EmbeddedWebserver__http_processor__) */
