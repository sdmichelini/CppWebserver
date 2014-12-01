//
//  http_response.h
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 11/25/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#ifndef __EmbeddedWebserver__http_response__
#define __EmbeddedWebserver__http_response__

#include <string>
#include <vector>

struct http_header{
    std::string name;
    std::string value;
};

struct http_response{
    std::string body;
    void set_header(std::string name, std::string value);
    void set_status(int status){
        m_status = status;
    }
    std::string to_string();
private:
    std::vector<http_header> m_headers;
    static std::string get_status_message(int status);
    
    ///status
    int m_status = 200;
};

#endif /* defined(__EmbeddedWebserver__http_response__) */
