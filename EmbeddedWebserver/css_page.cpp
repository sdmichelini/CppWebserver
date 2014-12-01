//
//  css_page.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 12/1/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "css_page.h"

css_page::css_page(std::string uri){
    std::ifstream file;
    
    file.open("css_base/"+uri);
    
    if(!file.is_open()){
        std::cout<<"Error CSS: "<<uri<<" not found."<<std::endl;
        this->set_status(404);
        m_valid = false;
        return;
    }
    std::string line;
    
    while(getline(file, line)){
        this->body += line;
    }
    
    file.close();
    m_valid = true;
    if(this->body.size()>0)this->set_status(200);
    else{
        this->set_status(404);
    }
}