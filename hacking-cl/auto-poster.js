/*
* WORKING DRAFT FOR CRAIGSLIST AUTO-POSTER;
* requires: the 'post' link for the area 
* (ex: https://post.craigslist.org/c/phx?lang=en)
* , and jQuery (your life requires jQuery anyway)
*/

var email = 'jonmarinelli@hotmail.com';
var title = 'SUP';
var body = 'ILL DO IT FOR A CHEESEBURGER';
var location = 'behind ur truk'
var zipCode = '12345';
var phoneNumber = '666-123-4567';

//let's assume we've opened the html page here & we're at the "what type of posting is this" page.

//for some reason, without putting the form into a variable CL blocks trigger events.  oh wait, it's to prevent this kind of software from working lulz
var form = $(".catpick"); 

//rewrite their onClick function, with their form bwahahah
//value='so' is service offered
$("input[value='so']").click(function(){ 
  form.submit(); 
  return true; 
});

//$("input[value='so']").prop('checked', true);
$("input[value='so']").trigger('click');

//value=76 is computer services
$("input[value='76']").prop('checked', true);
$("input[value='76']").trigger('click');

//choose location that fits best.  for phoenix, '2' is e. valley
$("input[value='2']").prop('checked', true);
$("input[value='2']").trigger('click');

/*
* FINAL BOSS
*/
$("input#FromEMail").val(email);
$("input#ConfirmEMail").val(email);
$("input#contact_phone").val(phoneNumber);
$("input#PostingTitle").val(title);
$("input#GeographicArea").val(location);
$("input#postal_code").val(zipCode);
$("textarea#PostingBody").val(body);

$(".bigbutton[name='go']").trigger('click');
/*
* dynamically uploading files to their server.
* this isn't illegal, right?
* (it's just images, i promise)
* still being worked on
*/

var csc = $("input[name='cryptedStepCheck']").val();

//in their http headers the data.file value is a blob
$.ajax({
  type: 'post',
  data: { 
    file:"http://marinelliworks.com/landing-page/assets/selfie.png", 
    cryptedStepCheck: csc,
      a: 'add',
  },
  success: function(data){  
    alert(data); 
    $("body").replaceWith(data.split('<body class="post"')[1].split('</body>')[0]);
  },
});

$(".done.bigbutton").trigger('click');

