

<%@ LANGUAGE="VBSCRIPT"%>
<SCRIPT LANGUAGE="VBSCRIPT" RUNAT="SERVER">
'====================
'Filename : WebSockClient.asp
'Title：測試WebSock通訊
'Date :2014-06-04
'Version : 1.00
'Copyright (C) AMANO Corporation 2006 - 2009
'====================
</SCRIPT>
<!doctype html>
<html lang="ja">
<head>
<meta http-equiv="content-type" content="text/html; charset=Shift_JIS">
<meta http-equiv="content-style-type"  content="text/css">
<meta http-equiv="content-script-type" content="text/javascript">
<meta http-equiv="pragma" content="no-cache">
<meta http-equiv="cache-control" content="no-cache">
<title>測試websock2</title>
<meta name="robots" content="none">
<meta name="description" content="Liujiquan Test WebSock">
<meta name="author" content="ABS-ASE:Development Team">
<link rel="stylesheet" media="all" href="./css/login.css">
<script src="./js/Baidu-Frontia-JS-1.0.0.js"></script>
</head>
<script type="text/javascript">
function window_onload()
{

}

function OnBaiduLogin()
{
	var AK = 'iG2ffdkYaq8kIjrSfvjMcUrf';
	baidu.frontia.init(AK);
	// 初始化登&#24405;的配置
	var redirect_url = 'http://frontiajsdemo.duapp.com/social/baidu.html';
	var options = 
	{
		response_type: 'token',
		media_type: 'baidu',  // 登&#24405;百度&#24080;号
		redirect_uri: redirect_url,
		client_type: 'web',
		scope: 'netdisk'
	};
	// 登&#24405;
	baidu.frontia.social.login(options);
    // 判断用&#25143;是否登&#24405;
    var user;
    user = baidu.frontia.getCurrentAccount();
    var msg = document.getElementById('message');
    if (user && user.getType() === 'user' && user.getMediaType() === 'baidu') 
    {
      		// 如果用&#25143;已&#32463;登&#24405;，&#21017;&#26174;示用&#25143;的登&#24405;信息
      		msg.innerHTML = 'name = ' + user.getName() + '<br>' +
          	'token = ' + user.getAccessToken() + '<br>' +
          	'social_id = ' + user.getId() + '<br>' +
          	'expires_in = ' + user.getExpiresIn();
    }
}
</script>
TEST
<body class="loginheader" onload="window_onload();">
<form name="" method="post">
message<pre id='message'></pre>
<input type="button" onclick='OnBaiduLogin()' id='LoginBaidu' value='百度登&#37636;'  style='width:200px; height:50px;'>									
</form>
</body>
</html>
