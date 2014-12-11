//
//  json.h
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 12/9/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#ifndef __EmbeddedWebserver__json__
#define __EmbeddedWebserver__json__

#include <stdio.h>
#include <string>
#include <map>



namespace json {
    typedef std::map<std::string, std::string> json_data;
    /*!
     @function parse_key_value
     @brief Parse's a JSON string into a std::map object
     @return data
        Map of string's
     */
    json_data parse_key_value(std::string jsonData);
    
    std::string map_to_json(json_data data);
}

#endif /* defined(__EmbeddedWebserver__json__) */
