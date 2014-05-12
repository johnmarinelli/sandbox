var connection = require('./database-connection');
var mysql = require('mysql');

connection.connect();

function isDictEmpty(dict){
	return Object.keys(dict).length === 0;
}

module.exports.login = function(data, callback){
	var loginString = "SELECT * FROM nodelogin WHERE (username='" + data.username + "' AND password='" + data.pwd + "') LIMIT 1"

	connection.query(loginString, function(err, rows, fields){
		if(isDictEmpty(rows)){
			callback(null, 'Username or password is incorrect');
			return;
		}

		else{
			callback({ 
						name: rows[0].name, 
						email: rows[0].email, 
						username: rows[0].username, 
						pwd: rows[0].password 
			}, null);
		}
	});
}

module.exports.addNewAccount = function(data, callback){
	var checkUsernameTakenString = "SELECT * FROM nodelogin WHERE username='" + data.username + "'";
	var addAcctString = "INSERT INTO nodelogin (name, email, username, password) values ('" + data.name + "', '" + data.email + "', '" + data.username + "', '" + data.pwd + "')";
	connection.query(checkUsernameTakenString, function(err, rows, fields){
		if(isDictEmpty(rows)){	
			connection.query(addAcctString, function(err, rows, fields){
				if(err) callback(err);
				else{
					connection.end();
					return true;
				}
			});
		}
	
		else{
			callback('Username taken');
		}
	});
}
