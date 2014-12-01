//
//  css_page.h
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 12/1/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#ifndef __EmbeddedWebserver__css_page__
#define __EmbeddedWebserver__css_page__

#include "http_response.h"
#include <fstream>
#include <iostream>

class css_page: public http_response{
public:
    css_page(std::string uri);
    bool is_valid(){
        return m_valid;
    }
private:
    bool m_valid;
};

#endif /* defined(__EmbeddedWebserver__css_page__) */
