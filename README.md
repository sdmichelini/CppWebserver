<h1>C++ Webserver</h1>

<h3><b>Author: </b> sdmichelini</h3>

<h3><b>Description: </b></h3>

Simple C++ Webserver which is multithreaded using C++11 and built on Unix using BSD sockets. Has the ability to display HTML and 
CSS files currently. Working on scripting HTML and live variables with server sent events and JSON.

<h3><strong>Features: </strong></h3>

Routing is handled using C++ 11 lambda expressions. 
```C++
config_route("/", [](http_request req, http_response res){
		size_t extension_loc = req.get_path().find_last_of('.');
		if(extension_loc != std::string::npos){
			std::string extension = req.get_path().substr(extension_loc+1);
			//Filter out CSS
			//Simple check to see what type of file client is requesting
			if(extension == "css"){
				//Route CSS to Global CSS directory
				res = css_page(req.get_path());
			}
			else if(extension == "js"){
				//Route JS to Global JavaScript Directory
				res = js_page(req.get_path());
			}
			else{
				//Render it as an HTML Page
				res = html_page(req.get_path());
			}
		}
	});
```

Dynamic HTML Creation.

```C++
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
```

Turns into this HTML page

![Constants Picture](/images/ConstantsPic.png)