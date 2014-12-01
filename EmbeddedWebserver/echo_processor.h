//
//  echo_processor.h
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 11/24/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#ifndef __EmbeddedWebserver__echo_processor__
#define __EmbeddedWebserver__echo_processor__

#include <iostream>
#include "server_processor.h"

class echo_processor: public server_processor{
public:
    void process_client(connection * conn);
};

#endif /* defined(__EmbeddedWebserver__echo_processor__) */
