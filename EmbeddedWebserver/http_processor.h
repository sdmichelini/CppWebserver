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

class http_processor:public server_processor{
public:
    void process_client(connection * conn);
private:
};

#endif /* defined(__EmbeddedWebserver__http_processor__) */
