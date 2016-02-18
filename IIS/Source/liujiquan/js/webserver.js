/*-----------------------------------------------------------
 Select -> ListBox
*/
function CListBox(selectObj)
{
	this.selectObj = selectObj;					// select 
	this.Init = function(selectObj){			// Init
		this.selectObj = selectObj;
	};
	this.getLength = function(){				// Len
		return this.selectObj.options.length;
	};
	this.clear = function(){					// clear
		this.selectObj.options.length = 0;
	};
	this.addString = function(str){				// addString
		var len = this.getLength();
		var item = new Option(str, len);
		item.title = str;
		this.selectObj.options.add(item);
	};	
} ;

/*-----------------------------------------------------------
 UL/LI-> ListBox2
*/
function trim(str){ //
　　     return str.replace(/(^\s*)|(\s*$)/g, "");
　　 }

function CListBox2(ulObj)
{
	this.ulObj = ulObj;							// ul
	this.getLength = function(){				// getLength
		return this.ulObj.childNodes.length;
	};
	this.clear = function(){					// 清空
		var len = this.getLength();
		for(var i = 0; i < len; i++)
		{
			this.ulObj.removeChild(this.ulObj.childNodes[i]);
		}
	}		
	this.delete_ = function(i){					// delete
		var len = this.getLength();
		if(i >= 0 && i < len)
			this.ulObj.removeChild(this.ulObj.childNodes[i]);
	};
	this.add = function(str){					// add
		var len = this.getLength();
		var li = document.createElement("li");
		li.innerHTML = str;
		li.value=100;
		this.ulObj.appendChild(li);	
	};
	this.deleteIP = function(strIp){
		var len = this.getLength();
		for(var i = 0; i < len; i++)
		{	
			if( trim(this.ulObj.childNodes[i].innerHTML) == strIp)
			{
				this.ulObj.removeChild(this.ulObj.childNodes[i]);
				break;
			}
		}		
	};
};

/*-----------------------------------------------------------
 DIV/RADIO-> CRadiolist
*/
function CRadiolist(divObj, groupName)
{
	this.divObj = divObj;						// div
	this.length = 0;
	this.groupname = groupName;
	this.clear = function(){					// 清空
			var len = this.divObj.children.length;	
			for(var i = 0; i < len; i++)
			{
				this.divObj.removeChild(this.divObj.children[i]);
			}
			len = this.divObj.childNodes.length;
			for(i = 0; i < len; i++)
			{
				this.divObj.childNodes[i].removeNode(true);
			}	
	}
	this.add = function(sock, pszIP){					// add
			var e = document.createElement("input");    
			e.type = "radio";   
			e.name = this.groupname;
			e.id = sock;
			e.value = pszIP;     
			this.divObj.appendChild(e);    
			// Checked
//			e.setAttribute("checked","checked");
			// Text
			var showText = pszIP + ":" + sock;
			this.divObj.appendChild(document.createTextNode(showText));
			this.length++;
	};
	this.delete_ = function(sock, pszIP){
			var len = this.length;
			for(var i = 0; i < len; i++)
			{
				var item = 	this.divObj.children[i];
				if(item.value == pszIP && item.id== sock)
				{
					this.divObj.removeChild(item);
					this.divObj.childNodes[i*2].removeNode(true);
					this.length--;
					break;
				}
			}
	};
};