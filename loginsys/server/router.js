var acctManager = require('./modules/account-manager');
var queryString = require('querystring');

module.exports = function(app){
    app.get('/home', function(req, res){
		var user = JSON.parse(req.signedCookies.you);
		res.render('home', { name: user.name, email: user.email });
    });

	/* SIGNING IN */
	app.get('/login', function(req, res){
		res.render('login', { title: 'Login Here' });
	});
	
	app.post('/login', function(req, res){
		var chunk = '';
		req.on('data', function(data){
			chunk += data;
		});
		
		req.on('end', function(){
			var username = queryString.parse(chunk).username;
			var password = queryString.parse(chunk).password;
		
			acctManager.login({
				username: username,	
				pwd: password
			}, function(user, error){
				if(error){
					res.send(error, 400);	
				}  else{
					console.log(user);
					req.method = 'get';
					res.cookie('you', JSON.stringify(user), { signed: true } );
					res.cookie('MyTest', 'ducks', { signed: false } );
					res.redirect('/home');
				}
			});
		});		
	});

	/*  CREATING NEW ACCOUNT */
	app.get('/signup', function(req, res){
		res.render('signup', { title: 'Signup' });
	});

	app.post('/signup', function(req, res){
		var chunk = '';
		req.on('data', function(data){
			chunk += data;
			console.log(chunk);
		});	

		req.on('end', function(){
		var name = queryString.parse(chunk).realname;
		var email = queryString.parse(chunk).email;
		var username = queryString.parse(chunk).username;
		var password = queryString.parse(chunk).password;

		acctManager.addNewAccount({
			name: name,
			email: email,
			username: username,
			pwd: password
			}, function(error){
				if(error){
					res.send(error, 400);
				}  else{
					res.send('ok', 200);
				}
			});
		});	
	});

	/* UPLOADING A FILE */
    app.get('/upload', function(req, res){
		res.render('upload');
	});

	app.post('/upload', function(req, res){
		var fs = require('fs');
		var path = require('path');
		var Busboy = require('busboy');

		var busboy = new Busboy({ headers: req.headers });
		busboy.on('file', function(fieldname, file, filename, encoding, mimetype){
			var newPath = __dirname + '/uploads/' + path.basename(fieldname);
			file.pipe(fs.createWriteStream(newPath));
		});
		busboy.on('finish', function(){
			res.writeHead(200, {'Connection': 'close' });
			res.end('Thats all!');
		});
		
		return req.pipe(busboy);
	});
};
