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