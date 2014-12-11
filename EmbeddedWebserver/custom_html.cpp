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
    m_head += line + "\n";
}

void custom_html::add_css(std::string file){
    add_head_line("<link rel=\"stylesheet\" type=\"text/css\" href=\""+file+"\">");
}

void custom_html::add_div(std::string div_class, std::string content){
    m_body += "<div class=\""+div_class+"\">\n";
    m_body += content + "\n";
    m_body += "</div>\n";
}

void custom_html::add_body(std::string bodyLine){
    m_body += bodyLine + "\n";
}

void custom_html::render_template(std::string templateName){
    std::ifstream file;
    
    file.open("template_base/"+templateName + ".html");
    
    if(!file.is_open()){
        add_div("alert alert-danger","<strong>Error!</strong> Template: "+templateName+" not found");
        return;
    }
    std::string line;
    
    while(getline(file, line)){
        add_body(line);
    }
    
    file.close();
}

void custom_html::to_html(){
    //Bootstrap
    add_css("https://maxcdn.bootstrapcdn.com/bootstrap/3.3.1/css/bootstrap.min.css");
    add_css("/global.css");
    this->body = "<html>\n";
    body += "<head>\n";
    body += m_head;
    body += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    body += "</head>\n";
    body += "<body>\n";
    body += m_body;
    body += "<script src='//ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js'></script>";
    body += "<script src='/main.js'></script>";
    body += "<script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.1/js/bootstrap.min.js'></script>";
    body += "</body>\n";
    body += "</html>\n";
}