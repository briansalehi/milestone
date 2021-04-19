var minimum_fontlevel = 1;
var maximum_fontlevel = 10;
var current_fontlevel = localStorage.getItem('fontlevel');
if (current_fontlevel == null) {
	current_fontlevel = 3;
}

function zoominLetter() {
	if (current_fontlevel < maximum_fontlevel) {
		current_fontlevel++;
		localStorage.setItem('fontlevel', current_fontlevel);

		var p = document.getElementsByTagName('p');
		for(i=0;i<p.length;i++) {
			if(p[i].style.fontSize) {
				var s = parseInt(p[i].style.fontSize.replace("px",""));
			} else {
				var s = 14;
			}
			s += 2;

			p[i].style.fontSize = s+"px"
			localStorage.setItem('fontsize', s);
		}

		var code = document.getElementsByTagName('code');
		for(i=0;i<code.length;i++) {
			if(code[i].style.fontSize) {
				var s = parseInt(code[i].style.fontSize.replace("px",""));
			} else {
				var s = 14;
			}
			s += 2;

			code[i].style.fontSize = s+"px"
		}

		var li = document.getElementsByTagName('li');
		for(i=0;i<li.length;i++) {
			if(li[i].style.fontSize) {
				var s = parseInt(li[i].style.fontSize.replace("px",""));
			} else {
				var s = 14;
			}
			s += 2;

			li[i].style.fontSize = s+"px"
		}

		var table = document.getElementsByTagName('table');
		for(i=0;i<table.length;i++) {
			if(table[i].style.fontSize) {
				var s = parseInt(table[i].style.fontSize.replace("px",""));
			} else {
				var s = 14;
			}
			s += 2;

			table[i].style.fontSize = s+"px"
		}
	}
}

function zoomoutLetter() {
	if (current_fontlevel > minimum_fontlevel) {
		current_fontlevel--;
		localStorage.setItem('fontlevel', current_fontlevel);

		var p = document.getElementsByTagName('p');
		for(i=0;i<p.length;i++) {
			if(p[i].style.fontSize) {
				var s = parseInt(p[i].style.fontSize.replace("px",""));
			} else {
				var s = 14;
			}
			s -= 2;

			p[i].style.fontSize = s+"px"
			localStorage.setItem('fontsize', s);
		}

		var code = document.getElementsByTagName('code');
		for(i=0;i<code.length;i++) {
			if(code[i].style.fontSize) {
				var s = parseInt(code[i].style.fontSize.replace("px",""));
			} else {
				var s = 14;
			}
			s -= 2;

			code[i].style.fontSize = s+"px"
			localStorage.setItem('fontsize', s);
		}

		var li = document.getElementsByTagName('li');
		for(i=0;i<li.length;i++) {
			if(li[i].style.fontSize) {
				var s = parseInt(li[i].style.fontSize.replace("px",""));
			} else {
				var s = 14;
			}
			s -= 2;

			li[i].style.fontSize = s+"px"
			localStorage.setItem('fontsize', s);
		}

		var table = document.getElementsByTagName('table');
		for(i=0;i<table.length;i++) {
			if(table[i].style.fontSize) {
				var s = parseInt(table[i].style.fontSize.replace("px",""));
			} else {
				var s = 14;
			}
			s -= 2;

			table[i].style.fontSize = s+"px"
			localStorage.setItem('fontsize', s);
		}
	}
}

function restoreFontSize() {
	var fontsize = localStorage.getItem('fontsize');
	var p = document.getElementsByTagName('p');
	var code = document.getElementsByTagName('code');
	var li = document.getElementsByTagName('li');
	var table= document.getElementsByTagName('table');

	for(i=0;i<p.length;i++) {
		p[i].style.fontSize = fontsize+"px"
	}
	for(i=0;i<code.length;i++) {
		code[i].style.fontSize = fontsize+"px"
	}
	for(i=0;i<li.length;i++) {
		li[i].style.fontSize = fontsize+"px"
	}
	for(i=0;i<table.length;i++) {
		table[i].style.fontSize = fontsize+"px"
	}
}
restoreFontSize();
