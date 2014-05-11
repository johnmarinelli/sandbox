var acctManager = require('./modules/account-manager');
var queryString = require('querystring');

module.exports = function(app){
    app.get('/', function(req, res){
		res.render('login', { title: 'Login Here' });
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

		var confirmationString = acctManager.addNewAccount({
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
};
