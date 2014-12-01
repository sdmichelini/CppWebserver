//
//  http_processor.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 11/25/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "http_processor.h"
#include "http_response.h"
#include "http_request.h"


void http_processor::process_client(connection *conn){
    std::string request = conn->recieve_string();
    http_request req(request);
    http_response r;
    if(request.size()==0){
        std::cout<<"HTTP Request Error"<<std::endl;
        //Bad Request
        r.set_status(400);
        r.set_header("Content-Type", "text/html");
        r.body = "<html><body>Bad Response</body></html>";
        conn->write_string(r.to_string());
    }
    else{
        r.set_status(200);
        r.set_header("Content-Type", "text/html");
        r.body = "<html><body>Good Response</body></html>";
        conn->write_string(r.to_string());
    }
}