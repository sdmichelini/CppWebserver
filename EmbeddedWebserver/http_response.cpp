//
//  http_response.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 11/25/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "http_response.h"


void http_response::set_header(std::string name,std::string value){
    for(unsigned int i = 0; i <m_headers.size(); i++){
        if(name == m_headers[i].name){
            m_headers[i].value = value;
            return;
        }
    }
    http_header h;
    h.name = name;
    h.value = value;
    m_headers.push_back(h);
}

std::string http_response::to_string(){
    //Set content length
    set_header("Content-Length", std::to_string(body.size()));
    set_header("Connection", "close");
    //Make HTTP response
    //Status Line
    std::string ret = "HTTP/1.1 "+std::to_string(m_status)+" "+get_status_message(m_status)+"\r\n";
    for(unsigned int i = 0; i < m_headers.size();i++)
    {
        ret += m_headers[i].name+":"+m_headers[i].value+"\r\n";
    }
    ret += "\r\n";
    ret +=body;
    return ret;
}

std::string http_response::writeEventStream(){
    set_header("Connection", "keep-alive");
    set_header("Content-Type", "text/event-stream");
    //Make HTTP response
    //Status Line
    std::string ret = "HTTP/1.1 "+std::to_string(m_status)+" "+get_status_message(m_status)+"\r\n";
    for(unsigned int i = 0; i < m_headers.size();i++)
    {
        ret += m_headers[i].name+":"+m_headers[i].value+"\r\n";
    }
    ret += "\r\n";
    ret +=body;
    return ret;
}

std::string http_response::get_status_message(int status){
    if(status == 200){
        return "OK";
    }
    else if(status == 400){
        return "Bad Request";
    }
    else if(status == 404){
        return "Not Found";
    }
    else if(status == 500){
        return "Internal Server Error";
    }
    else return "";
}