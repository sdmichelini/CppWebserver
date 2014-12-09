//
//  http_router.h
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 12/8/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#ifndef EmbeddedWebserver_http_router_h
#define EmbeddedWebserver_http_router_h

#include <functional>
#include "http_request.h"
#include "http_response.h"

/*!
 Typedef for an HTTP router
 */
typedef std::function<void(http_request req, http_response &res)> http_router;

#endif
