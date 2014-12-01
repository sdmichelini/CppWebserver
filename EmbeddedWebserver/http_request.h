//
//  http_request.h
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 12/1/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#ifndef __EmbeddedWebserver__http_request__
#define __EmbeddedWebserver__http_request__

#include <iostream>
#include "http_response.h"

enum http_method{
    kGet,
    kPost,
    kHead,
    kDelete,
    kUnsupported
};

enum http_version{
    k1_0,
    k1_1,
    kUnknown
};

//Example HTTP Request
/*
GET /path/file.html HTTP/1.0
From: someuser@jmarshall.com
User-Agent: HTTPTool/1.0
 */

class http_request{
public:
    ///Constructs the request and parses it
    http_request(std::string request);
    ///Get's the HTTP Method
    http_method get_method(){
        return m_method;
    }
    ///Returns the path from the request
    std::string get_path(){
        return m_path;
    }
    ///Get's the HTTP version
    http_version get_version(){
        return m_version;
    }
    ///Get the Request Body
    std::string get_body(){
        return m_body;
    }
    ///Get http headers
    std::vector<http_header> get_headers(){
        return m_headers;
    }
private:
    ///Request in string form. Raw from packet
    std::string m_request;
    ///Parses the HTTP request string and assigns class variables
    void parse_request();
    ///HTTP method
    http_method m_method;
    ///HTTP version
    http_version m_version;
    ///URI requested
    std::string m_path;
    ///Request Body
    std::string m_body;
    ///Line delimeter for HTTP
    const std::string HTTP_DELIM = "\r\n";
    ///Headers
    std::vector<http_header> m_headers;
    
};

#endif /* defined(__EmbeddedWebserver__http_request__) */
