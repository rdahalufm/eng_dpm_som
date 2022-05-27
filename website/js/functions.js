function decbin(dec, length) {
	var out = "";
	while (length--)
		if((dec << length ) & 128)
			out = 1 + out;
		else
			out = 0 + out;
	return out;
}

function bit_test(num,bit) {
	return ((num>>bit) % 2 != 0)
}

function bit_set(num,bit) {
	return num | 1<<bit;
}

function bit_clear(num,bit) {
	return num & ~(1<<bit);
}

function bit_tottle(num,bit) {
	return this.test(num,bit)?this.clear(num,bit):this.set(num,bit);
}

function process_webstatus(value) {
	var form = document.getElementById('input'); 
	var element = document.getElementById('webstatus');
	element.value = value;

	form.submit();
}


function display_valve(value) {
	var element = document.getElementById('valve-value');
	var elementParent = document.getElementById('valve');
	if (!value) {
		element.innerHTML = status = 'OPEN';
		elementParent.className = "btn btn-green success";
	// If valve is true, valve is closed
	} else {
		element.innerHTML = status = 'CLOSED';
		elementParent.className = "btn btn-green error";
	}
}

function display_venturi(value) {
	var element = document.getElementById('venturi-value');
	var elementParent = document.getElementById('venturi');
	
    if (!value){
        element.innerHTML = status = 'ON';
		elementParent.className = "btn btn-green success";
	// If valve is true, valve is closed
	} else {
		element.innerHTML = status = 'OFF';
		elementParent.className = "btn btn-green error";
	} 
}

function display_bypass(value) {
	var element = document.getElementById('bypass-value');
	var elementParent = document.getElementById('bypass');
	// If value is true, bypass is ON
	if (value) {
		element.innerHTML = 'ON';
		elementParent.className = "btn btn-green error";
	// If value is false, bypass is OFF
	} else {
		element.innerHTML = 'OFF';
		elementParent.className = "btn btn-green success";
	}
}

function display_minFlow(value) {
		//If value is true, flow is OK
	var elementParent = document.getElementById('flow-to-gun');
	if (value) {
		elementParent.className = "w5 success";
	//If flow is false, flow is minimal 
	} else {
		elementParent.className = "w5 error";
	}
}

function display_returnLeak(value) {
	var elementParent = document.getElementById('flow-from-gun');
	if (!value) {
		elementParent.className = "w5 success";
	//If leak is true. Throw error
	} else {
		elementParent.className = "w5 error";
	}
}
function display_weld(weld, minFlow, leak, valve) {
	var elementParent = document.getElementById('flow-status');
	var element = document.getElementById('flow-status-value');

	if (weld) {
		
		elementParent.className = "success";
		document.getElementById('flow-to-gun').className = "w5 success";
		document.getElementById('flow-from-gun').className = "w5 success";
		element.innerHTML = "OK";

	} else if (leak) {
        elementParent.className = "warn";
		element.innerHTML = "LEAK";
    } else if (minFlow) {
		elementParent.className = "warn";
		element.innerHTML = "LOW FLOW";
	} else if ( !weld && !minFlow && !leak && !valve) { 
		elementParent.className = "warn";
		element.innerHTML = "MIN FLOW";
	} else {
		elementParent.className = "error";
		document.getElementById('flow-to-gun').className = "w5 error";
		document.getElementById('flow-from-gun').className = "w5 error";
		element.innerHTML = "FAULT";
	}
}

function display_tempFault(value) {
	// Temp OK
	var elementParent = document.getElementById('water-temp');
	if (!value) {
		elementParent.className = "success";
	//If leak is true. Throw error
	} else {
		elementParent.className = "error";
	}
}

function display_units(value) {
	var element = document.getElementById('units');

	if (!value) {
		element.innerHTML = '&deg;F';

	} else {
		element.innerHTML = '&deg;C';
	}
}
function display_communications(value) {
	var elementParent = document.getElementById('communications');
	var element = document.getElementById('communications-status');
	
	if (value) {
		elementParent.className = "btn btn-green success";
		element.innerHTML = 'On';
	} else {
		elementParent.className = "btn btn-green error";
		element.innerHTML = 'Off';
	}
}
function GetUrlValue(VarSearch){
    var SearchString = window.location.search.substring(1);
    var VariableArray = SearchString.split('&');
    for(var i = 0; i < VariableArray.length; i++){
        var KeyValuePair = VariableArray[i].split('=');
        if(KeyValuePair[0] == VarSearch){
            return KeyValuePair[1];
        }
    }
}

function isInt(n) {
	return n % 1 === 0;
}