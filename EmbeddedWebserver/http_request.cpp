//
//  http_request.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 12/1/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "http_request.h"

http_request::http_request(std::string request){
    //Init Variables
    m_request = request;
    //Assume not supported before parsing
    m_version = kUnknown;
    m_method = kUnsupported;
    m_path = "";
    m_body = "";
    //Now parse the request
    parse_request();
}

void http_request::parse_request(){
    if(m_request == ""){
        return;
    }
    
    std::cout<<m_request<<std::endl;
    
    //The method will be from the beginning of the string to the first space
    size_t pos = m_request.find(' ');
    if(pos==std::string::npos){
        //Error
        std::cout<<"Error: Parsing Request. Invalid Format"<<std::endl;
        return;
    }
    //Check which method it is
    std::string method = m_request.substr(0,pos);
    if(method=="GET"){
        m_method = kGet;
    }
    else if(method=="POST"){
        m_method = kPost;
    }
    else if(method=="HEAD"){
        m_method = kHead;
    }
    else if(method=="DELETE"){
        m_method = kDelete;
    }
    else{
        std::cout<<"Error: Invalid Request Format."<<std::endl;
        return;
    }
    //Now get URI
    size_t uri_begin_pos = m_request.find('/',pos+1);
    if(uri_begin_pos == std::string::npos){
        std::cout<<"Error: Invalid Request Format."<<std::endl;
        return;
    }
    uri_begin_pos += 1;
    size_t uri_end_pos = m_request.find(' ',uri_begin_pos);
    if(uri_end_pos == std::string::npos){
        std::cout<<"Error: Invalid Request Format."<<std::endl;
        return;
    }
    m_path = m_request.substr(uri_begin_pos, (uri_end_pos - uri_begin_pos));
    //Now HTTP Version
    //Should be after HTTP/
    size_t version_begin = m_request.find('/',uri_end_pos);
    if(version_begin == std::string::npos){
        std::cout<<"Error: Invalid Request Format."<<std::endl;
        return;
    }

    size_t version_end = m_request.find(HTTP_DELIM,version_begin + 1);
    if(version_end == std::string::npos){
        std::cout<<"Error: Invalid Request Format."<<std::endl;
        return;
    }
    version_begin += 1;
    std::string version = m_request.substr(version_begin, version_end-version_begin);
    if(version == "1.0"){
        m_version = k1_0;
    }
    else if(version == "1.1"){
        m_version = k1_1;
    }
    //Can't determine Version
    else{
        m_version = kUnknown;
        return;
    }
    size_t delim_loc;
    while(true){
        delim_loc = m_request.find(HTTP_DELIM,version_end + 1);
        if(delim_loc == std::string::npos){
            std::cout<<"Error: Invalid Request Format."<<std::endl;
            return;
        }
        std::string line = m_request.substr(version_end + 2, delim_loc-(version_end + 2));
        size_t colon_pos = line.find(':');
        if(colon_pos == std::string::npos){
            break;
        }
        std::string header_name = line.substr(0, colon_pos);
        std::string header_value = line.substr(colon_pos+1);
        http_header h;
        h.name = header_name;
        h.value = header_value;
        m_headers.push_back(h);
        version_end = delim_loc;

    }
    if(m_request.size() < delim_loc + 4){
        return;
    }
    m_body = m_request.substr(delim_loc + 4);
    if(m_body.size() > 0){
       std::cout<<"Request Body: "<<m_body<<std::endl;
    }
}