//
//  html_page.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 12/1/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "html_page.h"

html_page::html_page(std::string uri){
    std::ifstream file;
    
    file.open("html_base/"+uri);
    
    if(!file.is_open()){
        std::cout<<"Error HTML: "<<uri<<" not found."<<std::endl;
        this->set_status(404);
        this->body = "<html><body>The file: "+uri+" was not found on this server.</body></html>";
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
        this->body = "<html><body>The file: "+uri+" was not found on this server.</body></html>";
        this->set_status(404);
    }
}