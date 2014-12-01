//
//  custom_html.h
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 12/1/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#ifndef __EmbeddedWebserver__custom_html__
#define __EmbeddedWebserver__custom_html__

#include "http_response.h"

class custom_html:public http_response{
public:
    custom_html(std::string title);
    void add_head_line(std::string line);
    void add_css(std::string file);
    void add_div(std::string div_class, std::string content);
private:
    std::string head;
    std::string body;
    
};

#endif /* defined(__EmbeddedWebserver__custom_html__) */