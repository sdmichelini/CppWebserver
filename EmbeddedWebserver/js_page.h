//
//  js_page.h
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 12/2/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#ifndef __EmbeddedWebserver__js_page__
#define __EmbeddedWebserver__js_page__

#include "http_response.h"
#include <fstream>
#include <iostream>

/*!
 @class js_page
 @brief Handle's loading local javascript files
 @discussion Load's a Javascript file from the 
 */
class js_page: public http_response{
public:
    js_page(std::string uri);
    ///Check's whether or not a valid JS file
    bool is_valid(){
        return m_valid;
    }
    const std::string JS_PATH = "js_base/";
private:
    bool m_valid;
};

#endif /* defined(__EmbeddedWebserver__js_page__) */
