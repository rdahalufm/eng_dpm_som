/*
 * webpage_html.c
 *
 *  Created on: Apr 6, 2022
 *      Author: Rupak
 */


// All the webpages are const static and stored here
// Data exchange is dynamic with javascript exchanging json data

const char header_chunked_common[] ="HTTP/1.1 200 OK\r\nContent-Type: %s\r\nAccess-Control-Allow-Origin: *\r\nTransfer-Encoding: chunked\r\n\r\n";


const unsigned char style_css[] =
"table {padding:0px;margin:0px;width:100%;height:100%;text-align: center;border-spacing: 0;border-collapse: collapse;border:0px;}table td {border-spacing: 0;border-collapse: collapse;margin:0px;padding:0px;}html {font-size:16px;font-weight:600;font-family: Arial;font-weight: bold;}html, body, .wrapper {width:632px;height:367px;margin:0px;padding:0px;margin:0px auto;}.wrapper {background:#282828;}body {font-size:.9em;}.header, .footer {height:45px;}.docbody {height:60%;padding:0px;}.header {border-bottom:1px solid #000;}.footer {border-top:1px solid #000;}.home .header table td {width:25%;text-align: center;vertical-align: middle;padding:1%;}.home .footer table td {text-align: center;vertical-align: middle;padding:1%;}.btn {height:50px;line-height: 50px;display: block;color:#000;text-decoration: none;background:blue;vertical-align:middle;text-transform: uppercase;font-size:16px;}.btn:hover {cursor: pointer;}.btn span.status {color:#fff;}#flow-status, #water-temp,#venturi-status {display: block;width:80%;height:80%;font-weight:normal;}#flow-status #flow-status-value, #water-temp #water-temp-value,#venturi-status #venturi-status-value {font-weight:400;font-size:30px;}#flow-status {background: left bottom repeat-x #1f622d;color:#fff;padding:0px 0px 0px 0px;border:3px solid #1F622D;}#flow-status span {display: inline-block;}#venturi-status {background:  left bottom repeat-x #1f622d;color:#fff;padding:2.5% 0px 0px 0px;border:3px solid #1F622D;}#venturi-status span {display: inline-block;}#water-temp {background:#fff;color:#1f622d;padding:2.5% 0px 2.5% 0px;vertical-align: middle;font-weight: bold;text-transform: uppercase;}#flow-to-gun {background: no-repeat #121212 right center;}#flow-from-gun  {background:  no-repeat #121212 left center;}#flow-to-gun.error {background: no-repeat #c41a00 right center;}#flow-from-gun.error  {background: no-repeat #c41a00 left center;}#flow-to-gun-value, #flow-from-gun-value, #flow-to-gun-units, #flow-from-gun-units{font-size:35px;margin-top:7px;}#supply, #return {font-style: italic;font-size:15px;color:#FF14EF;float: left;}#flow-to-gun-units, #flow-from-gun-units {color: #FF7E00;}.logo {width:100%;max-width:145px;}.w0 {width:5%;}.w1 {width:10%;}.w2 {width:20%;}.w3 {width:30%;}.w4 {width:40%;}.w5 {width:50%}#reset {}.btn-yellow {background: #d4a20b;border:3px solid #967413;}.btn-green {background: #1f622d;border:3px solid #1f622d;}.btn-blue {background: #267296;border:3px solid #184153;color:#fff;}#flow-status.error, #water-temp.error, #communications.error, #valve.error,#bypass.error,#venturi.error  {background: left bottom repeat-x #c20000;color:#fff;border:2px solid #c20000;}#flow-status.error span {font-weight: bold;}#venturi-status.error span {font-weight: bold;}#close {width:30px;height:30px;line-height: 30px;vertical-align: middle;text-align: center;margin:0px auto;float:right;}input.btn {height:auto;}.settings .header td, .settings .footer td {width:30%;text-align: center;}.page-title {color:#fff;margin:0px;padding:0px;text-align: center;}#settings-save {float:right;}.pager {float:left;}.bitmap .docbody table td {border:1px solid #A3A3A3;text-align: left;font-size:12px;font-weight:300;padding:0px 5px 0px 5px;}.bitmap .docbody {padding:0;}.reset p {color:#fff;}.reset .docbody table {height:auto;}span#units {font-size:30px;}#flow-to-gun, #flow-from-gun {border:3px solid #fff !important;color:#fff;padding:2% 2.5% 2% 2.5%;}#flow-status span,  #water-temp span, #venturi-status span {line-height:34px;padding:0px;margin:0px;vertical-align: middle;font-size: 21px;}.settings input[type=text], .settings select {width:100%;}.settings .docbody table td {text-align: left;padding:5px;}table.datatable td {background:#DBDBDB;}table.datatable tr.odd td {background:#eee;}.tborder {border-right:1px solid #eee;width:1px;margin:0px !important;padding:0px !important;}body .header td.logo-wrap {text-align:left;}.settings .header td, .reset .header td {width:33%;}.datatable {color:#000;}.settings .docbody {background:#B1B1B1}.webstatus {display: none;}.settings .docbody {background: #B1B1B1;}table.datatable tr.odd td {background: #292929;color: #D6D6D6;}table.datatable td {background: #E6E6E6;color: #000000;}.tborder {border-right: 1px solid #424242;border-left: 1px solid #000;width: 0px;display: none;}#close {line-height: 32px;margin-right: 15px;}.header {box-shadow: 0px 1px 1px rgb(109, 109, 109);}.btn-blue {padding: 0 30px;margin-right: 15px;}.settings select {width: 100%;}.datatable {margin-top: -1px;}table.datatable tr.odd td {background: #CACACA;color: #000;}table.datatable td {background: #D3D3D3;color: #000;}#close {line-height: 32px;margin-right: 15px;}.header {box-shadow: 0px 1px 1px rgb(109, 109, 109);}.settings .datatable td {width:auto;}.label {width:135px !important;}.label span {font-size:11px;font-style: italic;color:#636363;font-weight: 300;}#dashboard {width:100%;height:100%;border:none;overflow: hidden;}.top {vertical-align: top;}.datatable2 .label {width:130px;}.datatable2 select {width:145px;}#flow-status #flow-status-value {margin-left:2px;}#venturi-status #venturi-status-value {margin-left:2px;}.warn {background:#dfb322 top right repeat-x !important;border:3px solid #dfb322 !important;}.settings .datatable td {height:35px;line-height: 35px;vertical-align: middle;}.unit {background:#eee;padding:3px;color:#474343;text-decoration: none}.unit.selected {font-weight:bold;border:4px solid #000;background: #dfb322 top right repeat-x !important;color:#fff;}.valve-value {line-height: 20px;}.venturi-value {line-height: 20px;}.bms {font-size:10px;line-height:12px;max-height:20px;text-align: center;color:#fff;background: #267296;display: block;padding:5px;}.bitmap .docbody table td.micro {width:17px !important;padding:0 5px 0px 5px;}.bitmap .docbody table td.color {width:20px !important;padding:0 5px 0px 5px;}.bitmap .logo-wrap {width:140px !important;}.bitmap .page-title {text-align:left;padding-left:20px;}.bms {font-size:15px;font-weight: 800;font-weight:bold;}.bitmap .docbody table td.bmshead {padding:0px 5px 0px 5px !important;}";


const unsigned char page_common[] =
"<!doctype html>\
<html>\
<head>\
<title>ROCON DeltaPoint</title>";

/* index.html webpage */

const unsigned char index_html[] =
"<!doctype html>\
<html>\
<head>\
<title>ROCON DeltaPoint</title>\
<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">\
</head>\
<body class=\"home\" onload=\"init()\">\
<div id=\"docBody\">\
<div id=\"page-wrapper\" class=\"wrapper\">\
<table>\
<tr>\
<td class=\"header\">\
<table>\
<tr>\
<td>\
<a id=\"reset\" class=\"btn btn-yellow\" href=\"reset.html\">Reset</a>\
</td>\
<td>\
<a id=\"valve\" class=\"btn btn-green\" onclick=\"post_bit(1)\" href=\"\">Valve: <span id=\"valve-value\" class=\"status\"/>\
</a>\
</td>\
<td>\
<a id=\"bypass\" class=\"btn btn-green\" href=\"\" onclick=\"post_bit(0)\">BYPASS: <span id=\"bypass-value\" class=\"status\">ON</span>\
</a>\
</td>\
</tr>\
</table>\
</td>\
</tr>\
<tr>\
<td id=\"doc-body-id\" class=\"docbody\">\
<table cellpadding=0 cellspacing=0>\
<tr height=\"35px\">\
<td style=\"padding:10px\">\
<a id=\"venturi\" class=\"btn btn-green\" href=\"#\">Venturi:<span id=\"venturi-value\" class=\"status\"> OFF</span>\
</a>\
</td>\
<td class=\"w2\"/>\
<td style=\"padding:10px\">\
<a id=\"flow_ok\" class=\"btn btn-green\" href=\"#\">Flow OK : <span id=\"flowok-value\" class=\"status\"> ON</span>\
</a>\
</td>\
<td class=\"w2\"/>\
</tr>\
<tr>\
<td colspan=\"2\" id=\"flow-to-gun\" class=\"w5\">\
<span id=\"supply\">Supply </span>\
<span id=\"flow-to-gun-value\">10</span>\
<span id=\"flow-to-gun-units\"> GPM </span>\
</td>\
<td colspan=\"2\" id=\"flow-from-gun\" class=\"w5\">\
<span id=\"return\">Return </span>\
<span id=\"flow-from-gun-value\"> 12</span>\
<span id=\"flow-from-gun-units\"> GPM </span>\
</td>\
</tr>\
<tr height=\"32px\">\
<td class=\"w2\"/>\
<td colspan=\"2\" >\
<div id=\"water-temp\" style=\"background-color:#00bcc2\">\
<span> Water Temp : </span>\
<span id=\"water-temp-value\"> 12 </span>\
<span id=\"water_temp_units\">&#176 F</span>\
</div>\
</td>\
<td class=\"w2\"/>\
</tr>\
<tr height=\"5px\">\
<td colspan=\"4\"/>\
</tr>\
</table>\
</td>\
</tr>\
<tr>\
<td class=\"footer\">\
<table>\
<tr>\
<td>\
<a class=\"btn btn-blue\" href=\"settings.html\">Settings</a>\
</td>\
<td>\
<a class=\"btn btn-blue\" href=\"bitmap.html\">Bit Map</a>\
</td>\
<td colspan=\"2\">\
<span id=\"communications\" class=\"btn btn-green\" href=\"#\">EIP Communications: <span id=\"communications-status\">Active</span>\
</span>\
</td>\
</tr>\
</table>\
</td>\
</tr>\
</table>\
</div>\
</div>\
<script type=\"text/javascript\">\
\r\n\
var looper;\r\n\
var url = window.location.href;\r\n\
var oReq = new XMLHttpRequest();\r\n\
\r\n\
function display_change(classId, innerId, bitVal, boxColor) {\r\n\
var elementParent = document.getElementById(classId);\r\n\
var element = document.getElementById(innerId);\r\n\
\r\n\
if (bitVal) {\r\n\
element.innerHTML = 'ON';\r\n\
if (boxColor == 1) {\r\n\
elementParent.className = \"btn btn-green success\";\r\n\
} else if (boxColor == 0) {\r\n\
elementParent.className = \"btn btn-red error\";\r\n\
} else {\r\n\
elementParent.className = \"btn btn-yellow\";\r\n\
}\r\n\
} else {\r\n\
element.innerHTML = 'OFF';\r\n\
if (boxColor == 1) {\r\n\
elementParent.className = \"btn btn-red error\";\r\n\
} else {\r\n\
elementParent.className = \"btn btn-green success\";\r\n\
}\r\n\
}\r\n\
}\r\n\
\r\n\
\r\n\
function reqListener() {\r\n\
var data = JSON.parse(this.responseText);\r\n\
\r\n\
document.getElementById('flow-to-gun-value').innerHTML = data[0].flowToGun;\r\n\
document.getElementById('water-temp-value').innerHTML = data[0].gunTemp;\r\n\
document.getElementById('flow-from-gun-value').innerHTML = data[0].flowFromGun;\r\n\
\r\n\
display_change('flow_ok', 'flowok-value', parseInt(data[0].statusByte) & (1 << 0), 1);\r\n\
display_change('valve', 'valve-value', parseInt(data[0].statusByte) & (1 << 1), 1);\r\n\
display_change('bypass', 'bypass-value', parseInt(data[0].statusByte) & (1 << 2), 2);\r\n\
display_change('venturi', 'venturi-value', parseInt(data[0].statusByte) & (1 << 8), 0);\r\n\
display_change('communications', 'communications-status', parseInt(data[0].statusByte) & (1 << 9), 1);\r\n\
\r\n\
if (parseInt(data[0].statusByte) & (1 << 6)) {\r\n\
document.getElementById('water-temp').style = \"background-color:#c41a00\";\r\n\
} else {\r\n\
document.getElementById('water-temp').style = \"background-color:#00bcc2\";\r\n\
}\r\n\
\r\n\
if (parseInt((data[0].statusByte) & (1 << 6)) == \"0\") {\r\n\
document.getElementById('flow-to-gun-units').innerHTML = \"GPM\";\r\n\
document.getElementById('flow-from-gun-units').innerHTML = \"GPM\";\r\n\
document.getElementById('water_temp_units').innerHTML = \"&#176 F\";\r\n\
} else {\r\n\
document.getElementById('flow-to-gun-units').innerHTML = \"LPM\";\r\n\
document.getElementById('flow-from-gun-units').innerHTML = \"LPM\";\r\n\
document.getElementById('water_temp_units').innerHTML = \"&#176 C\";\r\n\
}\r\n\
\r\n\
}\r\n\
\r\n\
function reqError(err) {\r\n\
console.log('Fetch Error :-S', err);\r\n\
clearInterval(looper)\r\n\
}\r\n\
\r\n\
function init() {\r\n\
oReq.onload = reqListener;\r\n\
oReq.onerror = reqError;\r\n\
oReq.timeout = 5000;\r\n\
oReq.ontimeout = function () {\r\n\
oReq.abort();\r\n\
}\r\n\
oReq.open('get', 'values.json');\r\n\
oReq.send();\r\n\
}\r\n\
\r\n\
function post_bit(bit_val) {\r\n\
\r\n\
var bypass_value = \"1\";\r\n\
var shutoff_value = \"1\";\r\n\
if (bit_val == 0) {\r\n\
if (document.getElementById('bypass-value').innerHTML == \"ON\") {\r\n\
    bypass_value = \"0\";\r\n\
}\r\n\
if (document.getElementById('valve-value').innerHTML == \"OFF\") {\r\n\
    shutoff_value = \"0\";\r\n\
}\r\n\
\r\n\
} else {\r\n\
if (document.getElementById('bypass-value').innerHTML == \"OFF\") {\r\n\
    bypass_value = \"0\";\r\n\
}\r\n\
if (document.getElementById('valve-value').innerHTML == \"ON\") {\r\n\
    shutoff_value = \"0\";\r\n\
}\r\n\
}\r\n\
try {\r\n\
const response = fetch('indexpost', {\r\n\
            method: 'post',\r\n\
			headers: {\r\n\
				'Content-Type': 'application/json'\r\n\
			},\r\n\
            body: JSON.stringify({\r\n\
                \"bypass\": bypass_value,\r\n\
                \"valve\": shutoff_value\r\n\
            })\r\n\
        });\r\n\
console.log('Completed!', response);\r\n\
} catch (err) {\r\n\
console.error(`Error: ${err}`);\r\n\
}\r\n\
}\r\n\
\r\n\
looper = setInterval(function () {\r\n\
init();\r\n\
}, 1000);\r\n\
\r\n\
</script>\
</body>\
</html>";


/* ------------ SETTINGS.html webpage ----------------------------*/
const unsigned char settings_html[] =
"<!doctype html>\
<html>\
<head>\
<title>ROCON DeltaPoint</title>\
<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">\
</head>\
<body class=\"settings\" onload=\"init()\">\
<div class=\"wrapper\">\
<table>\
<tr>\
<td class=\"header\">\
<table>\
<tr>\
<td>\
<h1 class='page-title'> Settings</h1>\
</td>\
<td>\
<a id=\"close\" class=\"btn btn-yellow\" href=\"index.html\"><</a>\
</td>\
</tr>\
</table>\
</td>\
</tr>\
<tr>\
<td class=\"docbody\">\
Serial Number: <span id=\"serialNumber\" class=\"units\"></span>\
<form method=\"get\" id='settings-form' action=\"settings.html\">\
<table>\
<tr>\
<td width=\"50%\"  class=\"top\">\
<table class=\"datatable\">\
<tr class=\"even\">\
<td  class=\"label\">\
Units\
</td>\
<td>\
<select name=\"units\" id=\"units\">\
<option value=\"unitsFirst\">Metric</option>\
<option value=\"unitsSecond\">English</option>\
</select>\
</td>\
</tr>\
<tr class=\"odd\">\
<td  class=\"label\">\
Min Flow <span id=\"minFlow-units\" class=\"units\"></span>\
</td>\
<td>\
<input id=\"minFlow\" name=\"minFlow\"></input>\
</td>\
</tr>\
<tr class=\"even\">\
<td  class=\"label\">\
Flow Ok <span id=\"flowOk-units\" class=\"units\"></span>\
</td>\
<td>\
<input id=\"flowOk\" name=\"flowOk\"></input>\
</td>\
</tr>\
<tr class=\"odd\">\
<td  class=\"label\">\
Leak Rate <span id=\"leak-units\" class=\"units\"></span>\
</td>\
<td>\
<input id=\"leakRate\" name=\"leakRate\"></input>\
</td>\
</tr>\
\
<tr class=\"even\">\
<td  class=\"label\">\
Venturi Timer <span id=\"venturi-units\" class=\"units\"></span>\
</td>\
<td>\
<input id=\"venturiTimer\" name=\"venturiTimer\" />\
</td>\
</tr>\
\
</table>\
</td>\
<td class=\"tborder\"></td>\
<td  width=\"49%\" class=\"top\">\
<table class=\"datatable datatable2\">\
<tr class=\"even\">\
<td  class=\"label\">\
Under Temp. <span id=\"temp-units\" class=\"units\"></span>\
</td>\
<td>\
<input id=\"underTemp\" name=\"underTemp\" />\
</td>\
</tr>\
<tr class=\"odd\">\
<td  class=\"label\">\
Over Temp. <span id=\"temp-units\" class=\"units\"></span>\
</td>\
<td>\
<input id=\"overTemp\" name=\"overTemp\" />\
</td>\
</tr>\
<tr class=\"even\">\
<td  class=\"label\">\
Resp Time <span id=\"response-units\" class=\"units\"></span>\
</td>\
<td>\
<input id=\"responseTime\" name=\"responseTime\" />\
</td>\
</tr>\
<tr class=\"odd\">\
<td  class=\"label\">\
Restart Delay <span id=\"delay-units\" class=\"units\"></span>\
</td>\
<td>\
<input id=\"restartDelay\" name=\"restartDelay\" />\
</td>\
</tr>\
\
</table>\
</td>\
</tr>\
</table>\
</td>\
</tr>\
<tr>\
<td class=\"footer\">\
<table>\
<tr>\
<td>\
<a href=\"network.html\" style=\"margin-left:15px\" type=\"submit\" class=\"btn btn-blue\" >Network</a>\
</td>\
<td>\
\
</td>\
<td colspan=\"2\">\
<a href=\"\"  type=\"submit\" class=\"btn btn-blue\" onclick=\"sendPost()\" >Save</a>\
</td>\
</tr>\
</table>\
</td>\
</tr>\
</form>\
</table>\
</div>\
<script type=\"text/javascript\">\
var oReq = new XMLHttpRequest();\r\n\
var url = window.location.href;\r\n\
\r\n\
function reqListener() {\r\n\
var data = JSON.parse(this.responseText);\r\n\
var currentSelect = document.getElementById( \"units\" );\r\n\
\r\n\
document.getElementById('minFlow').value = data[0].minFlow;	\r\n\
document.getElementById('flowOk').value = data[0].flowOk;\r\n\
document.getElementById('leakRate').value = data[0].leakRate;\r\n\
document.getElementById('venturiTimer').value = data[0].venturiTimer;\r\n\
document.getElementById('overTemp').value = data[0].overTemp;\r\n\
document.getElementById('underTemp').value = data[0].underTemp;\r\n\
document.getElementById('responseTime').value = data[0].responseTime;\r\n\
document.getElementById('restartDelay').value = data[0].restartDelay;\r\n\
document.getElementById('serialNumber').innerHTML = data[0].serialNumber;\r\n\
currentSelect.selectedIndex = data[0].units;				\r\n\
}\r\n\
\r\n\
function reqError(err) {\r\n\
console.log('Fetch Error :-S', err);\r\n\
}\r\n\
\r\n\
function init() {\r\n\
oReq.onload = reqListener;\r\n\
oReq.onerror = reqError;\r\n\
oReq.timeout = 5000;\r\n\
oReq.ontimeout = function () {\r\n\
oReq.abort();\r\n\
}\r\n\
oReq.open('get', 'settings.json');\r\n\
oReq.send();\r\n\
\r\n\
\r\n\
}\r\n\
\r\n\
function sendPost() {\r\n\
var minflow = document.getElementById('minFlow').value;\r\n\
var restartDelay = document.getElementById('restartDelay').value;\r\n\
var responseTime = document.getElementById('responseTime').value;\r\n\
var overTemp = document.getElementById('overTemp').value;\r\n\
var underTemp = document.getElementById('underTemp').value;\r\n\
var flowOk = document.getElementById('flowOk').value;\r\n\
var units = document.getElementById('units').selectedIndex.toString();\r\n\
var leakRate = document.getElementById('leakRate').value;\r\n\
var venturiTimer = document.getElementById('venturiTimer').value;\r\n\
\r\n\
try {\r\n\
const response = fetch('settingspost', {\r\n\
method: 'post',\r\n\
headers: {\r\n\
    'Content-Type': 'application/json'\r\n\
},\r\n\
body: JSON.stringify({\r\n\
	\"minFlow\": minflow,\r\n\
	\"restartDelay\": restartDelay,\r\n\
	\"responseTime\" : responseTime,\r\n\
	\"overTemp\": overTemp,\r\n\
	\"underTemp\" : underTemp,\r\n\
	\"flowOk\" : flowOk,\r\n\
	\"units\" : units,\r\n\
	\"leakRate\" : leakRate,\r\n\
	\"venturiTimer\" : venturiTimer\r\n\
})\r\n\
});\r\n\
console.log('Completed!', response);\r\n\
} catch (err) {\r\n\
console.error(`Error: ${err}`);\r\n\
}\r\n\
}\r\n\
</script>\
</body>\
</html>";

/* settings.html webpage  END */



/* 404 - Page Not found */

const char page404[] =

"<!doctype html>\
<html>\
<head>\
<title>ROCON DeltaPoint</title>\
<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">\
</head>\
<body>\
<h1> 404 - Page Not Found </h1>\
<h2> Sorry! The page you are looking for is not available.</h2>\
</body>\
</html>";


const char network_html[] =
"<!doctype html>\
<html>\
<head>\
<title>ROCON DeltaPoint</title>\
<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">\
</head>\
<body onload=\"init()\" class=\"settings\">\
<div class=\"wrapper\">\
<table>\
<tr>\
<td class=\"header\">\
<table>\
<tr>\
<td class=\"logo-wrap\">\
\
</td>\
<td>\
<h1 class='page-title'>Settings</h1>\
</td>\
<td>\
<a id=\"close\" class=\"btn btn-yellow\" href=\"index.html\"><</a>\
</td>\
</tr>\
</table>\
</td>\
</tr>\
<tr>\
<td class=\"docbody\">\
<form method=\"get\" id='settings-form'>\
<input type=\"hidden\" name=\"webStatus\" id=\"webStatus-hidden\" value=\"3\" />\
<table>\
<tr>\
<td class=\"top\">\
<table class=\"datatable\">\
<tr class=\"odd\">\
<td  class=\"label\">\
Address<br/>\
<span>Page will stop responding.</span>\
</td>\
<td>\
<input id=\"ip\" type=\"text\" name=\"IP\" />\
</td>\
</tr>\
<tr class=\"even\">\
<td  class=\"label\">\
MAC Address\
</td>\
<td>\
<span id=\"macaddr\" class=\"status\"> </span>\
</td>\
</tr>\
<tr class=\"odd\">\
<td  class=\"label\">\
NetMask<br/>\
<span>Page will stop responding.</span>\
</td>\
<td>\
<input id=\"subnet\" type=\"text\" name=\"subnet\" />\
</td>\
</tr>\
</table>\
</td>\
</tr>\
</table>\
</td>\
</tr>\
<tr>\
<td class=\"footer\">\
<table>\
<tr>\
<td>\
<a href=\"settings.html\" style=\"margin-left:15px\" type=\"submit\" class=\"btn btn-blue\">Settings</a>\
</td>\
<td>\
&nbsp;\
</td>\
<td colspan=\"2\">\
<a href=\"\"  type=\"submit\" class=\"btn btn-blue\" onclick=\"sendPost()\" >Save</a>\
</td>\
</tr>\
</table>\
</td>\
</tr>\
</form>\
</table>\
</div>\
<script type=\"text/javascript\">\
var oReq = new XMLHttpRequest();\r\n\
var url = window.location.href;\r\n\
\r\n\
function reqListener() {\r\n\
var data = JSON.parse(this.responseText);\r\n\
\r\n\
document.getElementById('ip').value = data[0].ip;\r\n\
document.getElementById('subnet').value = data[0].subnet;\r\n\
document.getElementById('macaddr').innerHTML = data[0].macaddr;\r\n\
\r\n\
}\r\n\
\r\n\
function reqError(err) {\r\n\
console.log('Fetch Error :-S', err);\r\n\
}\r\n\
\r\n\
function init() {\r\n\
oReq.onload = reqListener;\r\n\
oReq.onerror = reqError;\r\n\
oReq.timeout = 1000;\r\n\
oReq.ontimeout = function () {\r\n\
oReq.abort();\r\n\
}\r\n\
oReq.open('get', 'network.json');\r\n\
oReq.send();\r\n\
}\r\n\
\r\n\
function sendPost() {\r\n\
var ip = document.getElementById('ip').value;\r\n\
var subnet = document.getElementById('subnet').value;\r\n\
\r\n\
try {\r\n\
const response = fetch(url, {\r\n\
method: 'post',\r\n\
headers: {\r\n\
    'Content-Type': 'application/json'\r\n\
},\r\n\
body: JSON.stringify({\r\n\
\"ip\" : ip,\r\n\
\"subnet\" : subnet\r\n\
})\r\n\
});\r\n\
console.log('Completed!', response);\r\n\
} catch (err) {\r\n\
console.error(`Error: ${err}`);\r\n\
}\r\n\
}\r\n\
</script>\
</body>\
</html>";

/*-------------------- NETWORK.HTML.....................................*/



const char reset_html[] =
"<!doctype html>\
<html>\
<head>\
<title>ROCON DeltaPoint</title>\
<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">\
</head>\
<body class=\"reset\">\
<div class=\"wrapper\">\
<table>\
<tr>\
<td class=\"header\">\
<table>\
<tr>\
<td class=\"logo-wrap\">\
\
</td>\
<td>\
<h1 class='page-title'>Reset</h1>\
</td>\
<td>\
<a id=\"close\" class=\"btn btn-yellow\" href=\"index.html\"><</a>\
</td>\
</tr>\
</table>\
</td>\
</tr>\
<tr>\
<td class=\"docbody\">\
<p style=\"text-align:center\">Are you sure you would like to reset?</p>\
<table>\
<tr>\
<td style=\"width:48.5%\">\
<a href=\"index.html\" class=\"btn btn-blue\" onclick=\"sendPost()\" >Yes</a>\
</td>\
<td style=\"width:3%\">\
\
</td>\
<td style=\"width:48.5%\">\
<a href=\"index.html\" class=\"btn btn-yellow\">No</a>\
</td>\
</tr>\
</table>\
</td>\
</tr>\
</table>\
</div>\
<script type=\"text/javascript\">\
var url = window.location.href;\r\n\
function sendPost() {				\r\n\
try {\r\n\
const response = fetch('indexrestart', {\r\n\
method: 'post',\r\n\
headers: {\r\n\
    'Content-Type': 'application/json'\r\n\
},\r\n\
body: JSON.stringify({\r\n\
\"restart\" : \"1\"\r\n\
})\r\n\
});\r\n\
console.log('Completed!', response);\r\n\
} catch (err) {\r\n\
console.error(`Error: ${err}`);\r\n\
}\r\n\
}\r\n\
\r\n\
</script>\
</body>\
</html>";


const char bitmap_html[] =
"<!doctype html>\
<html>\
<head>\
<title>ROCON DeltaPoint</title>\
<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">\
</head>\
<body class=\"bitmap\">\
<div class=\"wrapper\">\
<table>\
<tr>\
<td class=\"header\">\
<table>\
<tr>\
<td class=\"logo-wrap\">\
</td>\
<td>\
<h1 class='page-title'>Bitmap - EIP Input</h1>\
</td>\
<td>\
<a id=\"close\" class=\"btn btn-yellow\" href=\"index.html\"><</a>\
</td>\
</tr>\
</table>\
</td>\
</tr>\
<tr>\
<td class=\"docbody\">\
<table style=\"min-height:20px;min-width:10px;height:30px;margin-top:32px\" class=\"datatable\">\
\
<tr>\
<td class=\"bmshead\">\
<a class=\"bms\" href=\"bitmap.html\">Input Byte</a>\
</td>\
<td class=\"bmshead\">\
<a class=\"bms\" href=\"bitmap_output.html\">Output Byte</a>\
</td>\
</tr>\
</table>\
<table  style=\"min-height:20px;min-width:10px;\" class=\"datatable\">\
\
<tr class=\"odd\">\
<td class=\"micro\">\
0\
</td>\
<td class=\"color flow\">\
<div id=\"flow\"></div>\
</td>\
<td>\
Flow OK\
</td>\
<td>\
Bit on when Flow is OK\
</td>\
</tr>\
\
<tr class=\"even\">\
<td class=\"micro\">\
1\
</td>\
<td class=\"color valve\">\
<div id=\"valve\"></div>\
</td>\
<td>\
Valve\
</td>\
<td>\
Bit on when valve is closed.\
</td>\
</tr>\
\
<tr class=\"odd\">\
<td class=\"micro\">\
2\
</td>\
<td class=\"color bypass\">\
<div id=\"bypass\"></div>\
</td>\
<td>\
Bypass\
</td>\
<td>\
Bit on when unit is in bypass.\
</td>\
</tr>\
\
<tr class=\"even\">\
<td class=\"micro\">\
3\
</td>\
<td class=\"color minflow\">\
<div id=\"minflow\"></div>\
</td>\
<td>\
Min Flow\
</td>\
<td>\
Bit on when water flow is above minimum.\
</td>\
</tr>\
\
<tr class=\"odd\">\
<td class=\"micro\">\
4\
</td>\
<td class=\"color leak\">\
<div id=\"leak\"></div>\
</td>\
<td>\
Leak\
</td>\
<td>\
Bit on when cap loss detected.\
</td>\
</tr>\
\
<tr class=\"even\">\
<td class=\"micro\">\
5\
</td>\
<td class=\"color reserved\">\
<div id=\"reserved\"></div>\
</td>\
<td>\
UnderTemp\
</td>\
<td>\
Bit on when temperature is below setpoint\
</td>\
</tr>\
\
<tr class=\"odd\">\
<td class=\"micro\">\
6\
</td>\
<td class=\"color temp\">\
<div id=\"temp\"></div>\
</td>\
<td>\
High Temp\
</td>\
<td>\
Bit on when water temp less than the high temp setpoint.\
</td>\
</tr>\
\
<tr class=\"even\">\
<td class=\"micro\">\
7\
</td>\
<td class=\"color powerOk\">\
<div id=\"powerOk\"></div>\
</td>\
<td>\
Power Ok\
</td>\
<td>\
Bit on when supply to valve is good enough.\
</td>\
</tr>\
</table>\
</td>\
</tr>\
</table>\
</div>\
</body>\
</html>";

const char bitmap_output_html[] =
"<!doctype html>\
<html>\
<head>\
<title>ROCON DeltaPoint</title>\
<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">\
</head>\
<body class=\"bitmap\">\
<div class=\"wrapper\">\
<table>\
<tr>\
<td class=\"header\">\
<table>\
<tr>\
<td class=\"logo-wrap\">\
\
</td>\
<td>\
<h1 class='page-title'>Bitmap - EIP Output</h1>\
</td>\
<td>\
<a id=\"close\" class=\"btn btn-yellow\" href=\"index.html\"><</a>\
</td>\
</tr>\
</table>\
</td>\
</tr>\
<tr>\
<td class=\"docbody\">\
<table style=\"min-height:20px;min-width:10px;height:30px;margin-top:32px\" class=\"datatable\">\
<tr>\
<td class=\"bmshead\">\
<a class=\"bms\" href=\"bitmap.html\">Input Byte</a>\
</td>\
<td class=\"bmshead\">\
<a class=\"bms\" href=\"bitmap_output.html\">Output Byte</a>\
</td>\
</tr>\
</table>\
<table  style=\"min-height:20px;min-width:10px;\" class=\"datatable\">\
\
<tr class=\"odd\">\
<td class=\"micro\">\
0\
</td>\
<td class=\"color flow\">\
<div id=\"reset\"></div>\
</td>\
<td>\
Reset\
</td>\
<td>\
On when reset command sent\
</td>\
</tr>\
\
<tr class=\"even\">\
<td class=\"micro\">\
1\
</td>\
<td class=\"color valve\">\
<div id=\"shutoff\"></div>\
</td>\
<td>\
Shut-off\
</td>\
<td>\
On when shut-off sent\
</td>\
</tr>\
\
<tr class=\"odd\">\
<td class=\"micro\">\
2\
</td>\
<td class=\"color bypass\">\
<div id=\"bypass\"></div>\
</td>\
<td>\
Bypass\
</td>\
<td>\
On when bypass sent\
</td>\
</tr>\
\
<tr class=\"even\">\
<td class=\"micro\">\
3\
</td>\
<td class=\"color\">&nbsp;</td>\
<td>\
\
</td>\
<td>\
Bit not used (off)\
</td>\
</tr>\
\
<tr class=\"odd\">\
<td class=\"micro\">\
4\
</td>\
<td class=\"color\">&nbsp;</td>\
<td>\
\
</td>\
<td>\
Bit not used (off)\
</td>\
</tr>\
\
<tr class=\"even\">\
<td class=\"micro\">\
5\
</td>\
<td class=\"color\">&nbsp;</td>\
<td>\
\
</td>\
<td>\
Bit not used (off).\
</td>\
</tr>\
\
<tr class=\"odd\">\
<td class=\"micro\">\
6\
</td>\
<td class=\"color\">&nbsp;</td>\
<td>\
\
</td>\
<td>\
Bit not used (off)\
</td>\
</tr>\
\
<tr class=\"even\">\
<td class=\"micro\">\
7\
</td>\
<td class=\"color\">&nbsp;</td>\
<td>\
\
</td>\
<td>\
Bit not used (off)\
</td>\
</tr>\
\
</table>\
</td>\
</tr>\
</table>\
</div>\
</body>\
</html>";
