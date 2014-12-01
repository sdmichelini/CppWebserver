//
//  http_processor.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 11/25/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "http_processor.h"
#include "html_page.h"
#include "css_page.h"
#include "http_request.h"


void http_processor::process_client(connection *conn){
    std::string request = conn->recieve_string();
    if(request.size()==0){
       //do nothing except close connection
    }
    else{
        http_request req(request);
        http_response r;
        if(req.get_path()=="var/"){
            r.set_status(200);
            r.body = "<html><head><title>Variables</title></head><body>This is where variables should be.</body></html>";
        }
        //Normal HTTP page
        else{
            size_t extension_loc = req.get_path().find_last_of('.');
            if(extension_loc != std::string::npos){
                std::string extension = req.get_path().substr(extension_loc+1);
                //Filter out CSS
                if(extension == "css"){
                    r = css_page(req.get_path());
                }
                else{
                    r = html_page(req.get_path());
                }
            }
        }
        conn->write_string(r.to_string());
        std::cout<<r.to_string()<<std::endl;
    }
}