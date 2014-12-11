//
//  json.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 12/9/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "json.h"

json::json_data json::parse_key_value(std::string jsonData){
    return json_data();
}

std::string json::map_to_json(json::json_data data){
    std::string ret = "{";
    for(auto it = data.begin(); it != data.end(); it++){
        ret += "\"" + it->first + "\":\"" + it->second + "\",";
    }
    //Change last , to ending bracket
    ret[ret.size() - 1] = '}';
    return ret;
}

