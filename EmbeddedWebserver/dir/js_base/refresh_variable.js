function refreshDiv(){
	console.log("refreshDiv");
	$.getJSON( "/vars", function( data ) {
  	$.each( data, function( key, val ) {
  		console.log(key);
    	$("#var_"+key).html(val);
  	});
  });
}

var myVar = setInterval(refreshDiv, 200);
var updating = 1;

function toggleUpdate(){
	if(updating == 1){
		updating = 0;
		clearInterval(myVar);
		$("#toggle").html("Enable Live Update");
		$("#toggle").attr('class',"btn btn-success");
	}else{
		updating = 1;
		myVar = setInterval(refreshDiv, 200);
		$("#toggle").html("Disable Live Update");
		$("#toggle").attr('class',"btn btn-danger");
	}
}