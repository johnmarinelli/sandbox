var express = require('express');
var http = require('http');
var app = express();

var port = 8000;

app.set('port', port);
app.set('views', __dirname + '/server/views');
app.set('view engine', 'jade');
app.locals.pretty = true;
app.use(express.static(__dirname + '/public'));

/*
*  router.exports is a function routes url
*/
require('./server/router')(app);

app.listen(port, function(){
	console.log('listening on port %d', port);
});
