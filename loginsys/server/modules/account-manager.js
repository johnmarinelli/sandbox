var connection = require('./database-connection');
var mysql = require('mysql');

connection.connect();

module.exports.addNewAccount = function(data, callback){
	var checkUsernameTakenString = "SELECT * FROM nodelogin WHERE username='" + data.username + "'";
	var addAcctString = "INSERT INTO nodelogin (name, email, username, password) values ('" + data.name + "', '" + data.email + "', '" + data.username + "', '" + data.pwd + "')";

	console.log(checkUsernameTakenString);
	console.log(addAcctString);

	connection.query(checkUsernameTakenString, function(err, rows, fields){
		if(Object.keys(rows).length === 0){	
			connection.query(addAcctString, function(err, rows, fields){
				if(err) callback(err);
				else{
					connection.end();
					callback("Your account was successfully created.");
				}
			});
		}
	
		else{
			callback('Username taken');
		}
	});
}
