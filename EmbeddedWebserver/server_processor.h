//
//  server_processor.h
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 11/24/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#ifndef EmbeddedWebserver_server_processor_h
#define EmbeddedWebserver_server_processor_h

#include "connection.h"

class server_processor{
public:
    virtual void process_client(connection * conn) = 0;
};

#endif
