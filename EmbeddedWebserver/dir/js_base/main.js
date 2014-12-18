function deletePath(pathToDelete, varName, callback){
	$.ajax({
		url: pathToDelete+varName,
		type:'DELETE',
		success: function(result){
			console.log(result);
			callback();
		}
	});
}

function deleteVariable(var2, callback){
	deletePath('/var/',var2);
}

function deleteConstant(var2, callback){
	deletePath('/const/',var2);
}