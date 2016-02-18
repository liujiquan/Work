/*====================
 Filename : navigator.js
 Title : ブラウザ判別ライブラリ
 Date : 2012-02-05
 Version : 1.00
 Copyright(C) AMANO Business Solutions Corporation. All Rights Reserved.
 ====================*/
var _cxNav = (function() {
	var _constructor = function() {
		//private
		var inner = {
			ua: navigator.userAgent.toLowerCase().replace("　"," "),
			bName: "",		//Browser Name
			bVer: "",		//Browser Version
			bOS: "",		//OS
			bMobile: "",	//Mobile
			rName: "",		//Rendering Engine
			DOMCheck: "",	//Document Object Model
			
			_checkBrowser: function() {
				if ((inner.ua.indexOf("iphone") != -1) && (inner.ua.indexOf("mobile") != -1)) {	//------------------------------------------iPhone
					if (inner.ua.indexOf("firefox") != -1) {
						inner.bName = "Firefox";
					} else if (inner.ua.indexOf("opera") != -1) {
						inner.bName = "Opera";
					} else {
						inner.bName = "Mobile Safari";
					}
					inner.rName = "Gecko";
					inner.bOS   = "iOS";
					inner.bMobile = "iPhone";
				}
				else if (inner.ua.indexOf("ipad") != -1) {	//------------------------------------------iPad
					if (inner.ua.indexOf("firefox") != -1) {
						inner.bName = "Firefox";
					} else if (inner.ua.indexOf("opera") != -1) {
						inner.bName = "Opera";
					} else {
						inner.bName = "Mobile Safari";
					}
					inner.rName = "Gecko";
					inner.bOS   = "iOS";
					inner.bMobile = "iPad";
				}
				else if (inner.ua.indexOf("ipod") != -1) {	//------------------------------------------iPod
					inner.rName = "Gecko";
					inner.bName = "Mobile Safari";
					inner.bOS   = "iOS";
					inner.bMobile = "iPod";
				}
				else if (inner.ua.indexOf("android") != -1) {	//------------------------------------------Android
					if (inner.ua.indexOf("firefox") != -1) {
						inner.bName = "Firefox";
					} else if (inner.ua.indexOf("opera") != -1) {
						inner.bName = "Opera";
					} else {
						inner.bName = "Chrome Lite";
					}
					inner.rName = "Gecko";
					inner.bMobile = "Android";
					inner.bOS = "Android";
				}
				else if (window.opera) {	//------------------------------------------Opera
					inner.bName = "Opera";
					inner.rName = "Presto";
					var re;
					for (var i = 0; i <= 100; i++) {
						re = new RegExp("version/+" + i, "i");
						if (re.test(inner.ua)) {
							inner.bVer = i + ".x";
							break;
						}
					}
					inner.bOS = (inner.ua.indexOf("mac os") != -1) ? "Macintosh" : "Windows";
				}
				else if (document.routeEvent) {	//------------------------------Firefox
					inner.rName = "Gecko";
					inner.bName = "Firefox";
					var re;
					for (var i = 0; i <= 100; i++) {
						re = new RegExp("firefox/+" + i, "i");
						if (re.test(inner.ua)) {
							inner.bVer = (i == 0) ? "β" : (i + ".x");
							break;
						}
					}
					inner.bOS = (inner.ua.indexOf("mac os") != -1) ? "Macintosh" : "Windows";
				}
				else if (document.all) {	//----------------------------------Internet Explorer
					inner.bName = "Internet Explorer";
					inner.rName = "Trident";
					for (var i = 3; i <= 10; i++) {
						var re;
						re = new RegExp("msie\\s+" + i, "i");
						if (re.test(inner.ua)) {
							if (!document.documentMode)
							{
								inner.bVer = i + ".x"; 	//v7以下
							}
							else
							{
								for (var j = 4; j <= 20; j++) {
									var re2;
									re2 = new RegExp("trident/+" + j, "i");
									if (re2.test(inner.ua)) {
										j += 4;
										inner.bVer = j + ".x"; 	//v8以上
										break;
									}
								}
							}
							break;
						}
					}
					inner.bOS = (inner.ua.indexOf("mac os") != -1) ? "Macintosh" : "Windows";
				}
				else if (-1 != inner.ua.indexOf("gecko")) {
					if (-1 != inner.ua.indexOf("chrome")) {	//------------------Chrome
						inner.bName = "Chrome";
						inner.rName = "Webkit";
						for (var i = 0; i <= 100; i++) {
							var re = new RegExp("chrome/" + i, "i");
							if (re.test(inner.ua)) {
								inner.bVer = (i == 0) ? "β" : i + ".x";
								break;
							}
						}
					}
					else if (-1 != inner.ua.indexOf("safari")) {	//----------Safari
						inner.bName = "Safari";
						inner.rName = "Webkit";
						var re;
						for (var i = 0; i <= 100; i++) {	//v0~10
							re = new RegExp("version/" + i, "i");
							if (re.test(inner.ua)) {
								inner.bVer = i + ".x";
								break;
							}
						}
					}
					else {	//--------------------------------------------------Mozilla
						inner.bName = "Mozilla";
					}
					inner.bOS = (inner.ua.indexOf("mac os") != -1) ? "Macintosh" : "Windows";
				}
				else if (-1 != this.ua.indexOf("Macintosh")) {	//--------------Macintosh
					inner.bName = "Macintosh";
				}
				
				if (inner.bVer == undefined) {
					inner.bVer = "----";
				}
				
				inner.DOMCheck = (document.getElementById) ? true : false;
			}
		};
		
		//Check DOM
		this.chkDOM = function () { return inner.DOMCheck; };
		
		//Check Browser Status
		this.getBName = function () { return inner.bName; };
		this.getBVer = function () { return inner.bVer; };
		this.getRName = function () { return inner.rName; };
		this.getUA = function () { return inner.ua; }
		this.getOS = function () { return inner.bOS; };
		
		//Check IE
		this.isIE = function () { return this._isMatch(inner.bName, "Internet Explorer"); };
		this.isIE6 = function () { return (this.isIE() && (this._isMatch(inner.bVer, "6.x"))); };
		this.isIE7 = function () { return (this.isIE() && (this._isMatch(inner.bVer, "7.x"))); };
		this.isIE8 = function () { return (this.isIE() && (this._isMatch(inner.bVer, "8.x"))); };
		this.isIE9 = function () { return (this.isIE() && (this._isMatch(inner.bVer, "9.x"))); };
		this.isIE10 = function () { return (this.isIE() && (this._isMatch(inner.bVer, "10.x"))); };
		
		//Check Browser
		this.isCh = function () { return this._isMatch(inner.bName, "Chrome"); };
		this.isFf = function () { return this._isMatch(inner.bName, "Firefox"); };
		this.isOp = function () { return this._isMatch(inner.bName, "Opera"); };
		this.isSf = function () { return this._isMatch(inner.bName, "Safari"); };
		
		//Check Mobile Browser
		this.isIPhone = function () { return this._isMatch(inner.bMobile, "iPhone"); };
		this.isIPad = function () { return this._isMatch(inner.bMobile, "iPad"); };
		this.isIPod = function () { return this._isMatch(inner.bMobile, "iPod"); };
		this.isAndroid = function () { return this._isMatch(inner.bMobile, "Android"); };
		this.isIOS = function () { return this._isMatch(inner.bOS, "iOS"); };
		this.isModernPCBrowser = function () {
			return ((this.isFf() || this.isCh() || this.isSf() || this.isIE9() || this.isIE10()) && (!this.isIOS() && !this.isAndroid()));
		};
		
		//Check OS
		this.isMacOS = function () { return this._isMatch(inner.bOS, "Macintosh"); };
		
		//Func
		this._isMatch = function (s1, s2) { return (s1 == s2); };
		
		inner._checkBrowser();
	}
	return _constructor;
})();
var nv = new _cxNav();
