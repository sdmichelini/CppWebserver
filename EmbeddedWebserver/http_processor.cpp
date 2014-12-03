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
#include "js_page.h"
#include "http_request.h"


void http_processor::process_client(connection *conn){
    std::string request = conn->recieve_string();
    
    if(request.size()==0){
       //do nothing except close connection
    }
    else{
        http_request req(request);
        if(req.get_content_length() != req.get_body().size()){
            req.set_body(conn->recieve_string());
        }
        
        http_response r;
        if(req.get_path()==VARIABLE_URL){
            r.set_status(200);
            r.body = "<html><head><title>Variables</title></head><body>This is where variables should be.</body></html>";
        }
        else if(req.get_path()==SSE_URL){
            r.set_status(200);
            r.body = "<html><head><title>Server Sent Events</title></head><body>This is where server sent events should be.</body></html>";
        }
        //Normal HTTP page
        else{
            std::cout<<req.get_path()<<std::endl;
            size_t extension_loc = req.get_path().find_last_of('.');
            if(extension_loc != std::string::npos){
                std::string extension = req.get_path().substr(extension_loc+1);
                //Filter out CSS
                if(extension == "css"){
                    r = css_page(req.get_path());
                }
                else if(extension == "js"){
                    r = js_page(req.get_path());
                }
                else{
                    r = html_page(req.get_path());
                }
            }
        }
        if(conn->bytes_available()){
            std::cout<<"There is still data to read"<<std::endl;
        }
        std::string response = r.to_string();
        size_t bytesSent = 0;
        //Iterator variable to see which chunk we are sending
        unsigned int it = 0;
        //Send in chunks
        while(bytesSent != response.size()){
            if(response.substr(it * MAX_PACKET_SIZE).size() < MAX_PACKET_SIZE){
                bytesSent += conn->write_string(response.substr(it * MAX_PACKET_SIZE));
                break;
            }
            else{
                bytesSent += conn->write_string(response.substr(it * MAX_PACKET_SIZE,MAX_PACKET_SIZE));
                it++;
            }
        }
    }
}