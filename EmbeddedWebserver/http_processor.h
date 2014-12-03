//
//  http_processor.h
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 11/25/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#ifndef __EmbeddedWebserver__http_processor__
#define __EmbeddedWebserver__http_processor__

#include "server_processor.h"

#define MAX_PACKET_SIZE 1024

class http_processor:public server_processor{
public:
    void process_client(connection * conn);
private:
    const std::string VARIABLE_URL = "var/";
    const std::string SSE_URL = "sse/";
};

#endif /* defined(__EmbeddedWebserver__http_processor__) */
