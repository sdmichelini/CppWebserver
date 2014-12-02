//
//  custom_html.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 12/1/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "custom_html.h"

custom_html::custom_html(std::string title){
    add_head_line("<title>"+title+"</title>");
    m_title = title;
}

void custom_html::add_head_line(std::string line){
    m_head += line = "\n";
}

void custom_html::add_css(std::string file){
    add_head_line("<link rel=\"stylesheet\" type=\"text/css\" href=\""+file+"\">");
}

void custom_html::add_div(std::string div_class, std::string content){
    m_body += "<div class=\""+div_class+"\">\n";
    m_body += content + "\n";
    m_body += "</div>";
}

void custom_html::to_html(){
    this->body = "<html>\n";
    body += "<head>\n";
    body += m_head;
    body += "</head>\n";
    body += "<body>\n";
    body += m_body;
    body += "</body>\n";
    body += "</html>\n";
}