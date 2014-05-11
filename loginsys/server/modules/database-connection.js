var mysql = require('mysql');

var host = 'localhost';
var user = 'administrator';
var pwd = '';
var database = 'test';

module.exports = mysql.createConnection({
	host: host,
	user: user,
	password: pwd,
	database: database,
});
