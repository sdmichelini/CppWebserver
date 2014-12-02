//
//  html_page.h
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 12/1/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#ifndef __EmbeddedWebserver__html_page__
#define __EmbeddedWebserver__html_page__

#include "http_response.h"
#include <fstream>
#include <iostream>

class html_page: public http_response{
public:
    html_page(std::string uri);
    bool is_valid(){
        return m_valid;
    }
    ///Local path to HTML files
    const std::string HTML_PATH = "html_base/";
private:
    bool m_valid;
};

#endif /* defined(__EmbeddedWebserver__html_page__) */
