//
//  http_processor.cpp
//  EmbeddedWebserver
//
//  Created by Steve Michelini on 11/25/14.
//  Copyright (c) 2014 sdmichelini. All rights reserved.
//

#include "http_processor.h"
#include "custom_html.h"
#include "html_page.h"
#include "css_page.h"
#include "js_page.h"
#include "http_request.h"


http_processor::http_processor(){
    config_route("/", [](http_request req, http_response res){
        std::cout<<req.get_path()<<std::endl;
        size_t extension_loc = req.get_path().find_last_of('.');
        if(extension_loc != std::string::npos){
            std::string extension = req.get_path().substr(extension_loc+1);
            //Filter out CSS
            if(extension == "css"){
                res = css_page(req.get_path());
            }
            else if(extension == "js"){
                res = js_page(req.get_path());
            }
            else{
                res = html_page(req.get_path());
            }
        }
    });
    config_route(VARIABLE_URL, [](http_request req, http_response &res){
        std::string error = "";
        if(req.get_method()==kPost){
            size_t vNamePos = req.get_body().find("vName=");
            size_t vValuePos = req.get_body().find("vValue=");
            size_t ampPos = req.get_body().find('&');
            if(req.get_body().find('+')!=std::string::npos){
                error = "<strong>Warning:</strong> There can be no space in the request";
            }
            else if((vNamePos != std::string::npos)&&(vValuePos != std::string::npos)&&(ampPos != std::string::npos)){
                std::string name = req.get_body().substr(vNamePos + 6, ampPos-vNamePos-6);
                std::string value = req.get_body().substr(vValuePos + 7);
                if(name==""||value==""){
                    error = (name=="")?"<strong>Warning:</strong> Name Must be Non-Blank":"<strong>Warning:</strong> Value Must be Non-Blank";
                }
                else{
                    server_variables::get_instance().add_variable(name, value);
                }
                
            }
            else{
                error = "<strong>Warning:</strong> Invalid HTTP Post Request";
            }
        }
        //Init Custom HTML
        custom_html res2 = custom_html("Variables");
        //Get the Current Constants
        std::map<std::string, std::string> constants = server_variables::get_instance().get_values();
        typedef std::map<std::string, std::string>::iterator it_type;
        //We are going to send back a successful request
        res2.set_status(200);
        //Boostrap Container
        res2.add_body("<div class='container'>");
        //Use CSS main_content
        res2.add_body("<div class='main_content'>");
        //Heading
        res2.add_body("<h1>Variables</h1>");
        res2.add_body("</div>");
        //Make a table of the constants
        if(constants.size()!=0){
            res2.add_body("<table class ='table table-striped'>");
            res2.add_body("<tr><th>Name</th><th>Value</th><th>Delete</th></tr>");
            for(it_type i = constants.begin(); i != constants.end(); i++)
            {
                res2.add_body("<tr>");
                res2.add_body("<td>"+i->first+"</td><td id='var_"+i->first+"'>"+i->second+"</td><td width='5%'><button class='btn btn-danger' onClick=\"deleteVariable('"+i->first+"',location.reload())\"><span text-align='right' class='glyphicon glyphicon-remove' aria-hidden='true'></span></button></td>");
                res2.add_body("</tr>");
            }
            res2.add_body("</table>");
        }
        //Error with Alert if we have none
        else{
            res2.add_div("alert alert-info", "You have no variables");
        }
        //Print error if we have one
        if(error != ""){
            res2.add_div("alert alert-warning", error);
        }
        res2.add_body("<div class='main_content'>");
        //Render a template
        res2.render_template("variable_footer");
        res2.add_body("</div>");
        res2.add_body("</div>");
        //Link a JS file
        res2.add_js("refresh_variable.js");
        //Generate HTML
        res2.to_html();
        res = res2;

    });
    config_route(ALL_VARIABLE_URL, [](http_request req, http_response &res){
        json::json_data data = server_variables::get_instance().get_values();
        if(data.size() == 0){
            res.set_status(404);
            return;
        }
        res.set_status(200);
        res.set_header("Content-Type", "text/json");
        res.body = json::map_to_json(data);
    });
    config_route(CONSTANT_URL, [](http_request req, http_response &res){
        std::string error = "";
        if(req.get_method()==kPost){
            size_t vNamePos = req.get_body().find("vName=");
            size_t vValuePos = req.get_body().find("vValue=");
            size_t ampPos = req.get_body().find('&');
            if(req.get_body().find('+')!=std::string::npos){
                error = "<strong>Warning:</strong> There can be no space in the request";
            }
            else if((vNamePos != std::string::npos)&&(vValuePos != std::string::npos)&&(ampPos != std::string::npos)){
                std::string name = req.get_body().substr(vNamePos + 6, ampPos-vNamePos-6);
                std::string value = req.get_body().substr(vValuePos + 7);
                if(name==""||value==""){
                    error = (name=="")?"<strong>Warning:</strong> Name Must be Non-Blank":"<strong>Warning:</strong> Value Must be Non-Blank";
                }
                else{
                    constant::get_instance().add_constant(name, value);
                }
                
            }
            else{
                error = "<strong>Warning:</strong> Invalid HTTP Post Request";
            }
        }
        custom_html res2 = custom_html("Constants");
        std::map<std::string, std::string> constants = constant::get_instance().get_values();
        typedef std::map<std::string, std::string>::iterator it_type;
        res2.set_status(200);
        res2.add_body("<div class='container'>");
        res2.add_body("<div class='main_content'>");
        res2.add_body("<h1>Constants</h1>");
        res2.add_body("</div>");
        if(constants.size()!=0){
            res2.add_body("<table class ='table table-striped'>");
            res2.add_body("<tr><th>Name</th><th>Value</th><th>Delete</th></tr>");
            for(it_type i = constants.begin(); i != constants.end(); i++)
            {
                res2.add_body("<tr>");
                res2.add_body("<td>"+i->first+"</td><td>"+i->second+"</td><td width='5%'><button class='btn btn-danger' onClick=\"deleteConstant('"+i->first+"',location.reload())\"><span text-align='right' class='glyphicon glyphicon-remove' aria-hidden='true'></span></button></td>");
                res2.add_body("</tr>");
            }
            res2.add_body("</table>");
        }
        else{
            res2.add_div("alert alert-info", "You have no constants");
        }
        if(error != ""){
            res2.add_div("alert alert-warning", error);
        }
        res2.add_body("<div class='main_content'>");
        res2.render_template("constant_footer");
        res2.add_body("</div>");
        res2.add_body("</div>");
        res2.to_html();
        res = res2;
    });
    config_route(VARIABLE_REST, [](http_request req, http_response &res){
        std::string var = req.get_path().substr(req.get_path().find_last_of('/')+1);
        std::map<std::string, std::string> vars = server_variables::get_instance().get_values();
        if(req.get_method() == kGet){
            res.set_header("Content-Type", "text/json");
            if(vars.find(var) == vars.end()){
                res.set_status(404);
                res.body = "{'Error':'Not Found'}";
            }
            else{
                res.set_status(200);
                res.body = "{'"+var+"':'"+vars[var]+"'}";
            }
        }
        else if(req.get_method() == kPost){
            res.set_status(301);
            res.set_header("Location", "/var/");
        }
        else if(req.get_method() == kDelete){
            std::cout<<"Delete: "<<var<<std::endl;
            res.set_header("Content-Type", "text/json");
            if(vars.find(var) == vars.end()){
                res.set_status(404);
                res.body = "{'Error':'Not Found'}";
            }
            else{
                res.set_status(200);
                server_variables::get_instance().delete_variable(var);
                res.body = "{'"+var+"':'deleted'}";
            }
        }
    });
    config_route(CONSTANT_REST, [](http_request req, http_response &res){
        std::string var = req.get_path().substr(req.get_path().find_last_of('/')+1);
        std::map<std::string, std::string> vars = constant::get_instance().get_values();
        if(req.get_method() == kGet){
            res.set_header("Content-Type", "text/json");
            if(vars.find(var) == vars.end()){
                res.set_status(404);
                res.body = "{'Error':'Not Found'}";
            }
            else{
                res.set_status(200);
                res.body = "{'"+var+"':'"+vars[var]+"'}";
            }
        }
        else if(req.get_method() == kPost){
            res.set_status(301);
            res.set_header("Location", "/var/");
        }
        else if(req.get_method() == kDelete){
            std::cout<<"Delete: "<<var<<std::endl;
            res.set_header("Content-Type", "text/json");
            if(vars.find(var) == vars.end()){
                res.set_status(404);
                res.body = "{'Error':'Not Found'}";
            }
            else{
                res.set_status(200);
                constant::get_instance().delete_variable(var);
                res.body = "{'"+var+"':'deleted'}";
            }
        }
    });
    
    config_route(LOG_URL, [](http_request req, http_response &res){
        custom_html res2 = custom_html("Logs");
        res2.add_body("<div class='main_content'>");
        res2.add_body("<div class='container'>");
        res2.add_body("<h1>Log Messages</h1>");
        res2.add_body(logger::get_instance().generate_html());
        res2.render_template("log_template");
        res2.add_body("</div>");
        res2.add_body("</div>");
        res2.to_html();
        res = res2;
    });
}

void http_processor::config_route(std::string path, http_router r){
    m_routes[path] = r;
}

void http_processor::process_client(connection *conn){
    std::string request = conn->recieve_string();
    std::cout<<"recieved request"<<std::endl;
    if(request.size()==0){
       //do nothing except close connection
    }
    else{
        http_request req(request);
        if(req.get_content_length() != req.get_body().size()){
            req.set_body(conn->recieve_string());
        }
        
        http_response r;
        //This is where all the routing is done
        size_t pos = req.get_path().find_last_of('/');
        if(pos==std::string::npos){
            size_t extension_loc = req.get_path().find_last_of('.');
            if(extension_loc != std::string::npos){
                std::string extension = req.get_path().substr(extension_loc+1);
                //Filter out CSS
                if(extension == "css"){
                    r = css_page(req.get_path());
                }
                else if(extension == "js"){
                    r = js_page(req.get_path());
                }
                else{
                    r = html_page(req.get_path());
                }
            }
            else if(m_routes.find(req.get_path())!=m_routes.end())
            {
                m_routes[req.get_path()](req,r);
            }
            else r = html_page("index.html");
        }
        else{
            std::string path = req.get_path().substr(0, pos + 1);
            if(req.get_path().substr(pos+1).size() > 0){
                path+=":";
            }
            std::cout<<"Routing Path: "<<path<<std::endl;
            if(m_routes.find(path)!=m_routes.end()){
                m_routes[path](req,r);
            }
            else if(path.find(VARIABLE_REST)!=std::string::npos){
                m_routes[VARIABLE_REST](req,r);
            }
            else{
                r = html_page("bad_route.html");
            }
        }
        if(conn->bytes_available()){
            std::cout<<"There is still data to read"<<std::endl;
        }
        std::string response = r.to_string();
        size_t bytesSent = 0;
        //Iterator variable to see which chunk we are sending
        unsigned int it = 0;
        //Send in chunks
        while(bytesSent != response.size()){
            if(response.substr(it * MAX_PACKET_SIZE).size() < MAX_PACKET_SIZE){
                bytesSent += conn->write_string(response.substr(it * MAX_PACKET_SIZE));
                break;
            }
            else{
                bytesSent += conn->write_string(response.substr(it * MAX_PACKET_SIZE,MAX_PACKET_SIZE));
                it++;
            }
        }
    }
}