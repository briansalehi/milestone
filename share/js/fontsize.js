var minimum_fontlevel = 1;
var maximum_fontlevel = 12;
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

		var pre = document.getElementsByTagName('pre');
		for(i=0;i<pre.length;i++) {
			if(pre[i].style.fontSize) {
				var s = parseInt(pre[i].style.fontSize.replace("px",""));
			} else {
				var s = 14;
			}
			s += 2;

			pre[i].style.fontSize = s+"px"
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

		var cite = document.getElementsByTagName('cite');
		for(i=0;i<cite.length;i++) {
			if(cite[i].style.fontSize) {
				var s = parseInt(cite[i].style.fontSize.replace("px",""));
			} else {
				var s = 14;
			}
			s += 2;

			cite[i].style.fontSize = s+"px"
		}

		var h2 = document.getElementsByTagName('h2');
		for(i=0;i<h2.length;i++) {
			if(h2[i].style.fontSize) {
				var s = parseInt(h2[i].style.fontSize.replace("px",""));
			} else {
				var s = 30;
			}
			s += 2;

			h2[i].style.fontSize = s+"px"
			localStorage.setItem('h2-fontsize', s);
		}

		var h3 = document.getElementsByTagName('h3');
		for(i=0;i<h3.length;i++) {
			if(h3[i].style.fontSize) {
				var s = parseInt(h3[i].style.fontSize.replace("px",""));
			} else {
				var s = 24;
			}
			s += 2;

			h3[i].style.fontSize = s+"px"
			localStorage.setItem('h3-fontsize', s);
		}

		var h4 = document.getElementsByTagName('h4');
		for(i=0;i<h4.length;i++) {
			if(h4[i].style.fontSize) {
				var s = parseInt(h4[i].style.fontSize.replace("px",""));
			} else {
				var s = 20;
			}
			s += 2;

			h4[i].style.fontSize = s+"px"
			localStorage.setItem('h4-fontsize', s);
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

		var pre = document.getElementsByTagName('pre');
		for(i=0;i<pre.length;i++) {
			if(pre[i].style.fontSize) {
				var s = parseInt(pre[i].style.fontSize.replace("px",""));
			} else {
				var s = 14;
			}
			s -= 2;

			pre[i].style.fontSize = s+"px"
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
		}

		var cite = document.getElementsByTagName('cite');
		for(i=0;i<cite.length;i++) {
			if(cite[i].style.fontSize) {
				var s = parseInt(cite[i].style.fontSize.replace("px",""));
			} else {
				var s = 14;
			}
			s -= 2;

			cite[i].style.fontSize = s+"px"
		}

		var h2 = document.getElementsByTagName('h2');
		for(i=0;i<h2.length;i++) {
			if(h2[i].style.fontSize) {
				var s = parseInt(h2[i].style.fontSize.replace("px",""));
			} else {
				var s = 30;
			}
			s -= 2;

			h2[i].style.fontSize = s+"px"
			localStorage.setItem('h2-fontsize', s);
		}

		var h3 = document.getElementsByTagName('h3');
		for(i=0;i<h3.length;i++) {
			if(h3[i].style.fontSize) {
				var s = parseInt(h3[i].style.fontSize.replace("px",""));
			} else {
				var s = 24;
			}
			s -= 2;

			h3[i].style.fontSize = s+"px"
			localStorage.setItem('h3-fontsize', s);
		}

		var h4 = document.getElementsByTagName('h4');
		for(i=0;i<h4.length;i++) {
			if(h4[i].style.fontSize) {
				var s = parseInt(h4[i].style.fontSize.replace("px",""));
			} else {
				var s = 24;
			}
			s -= 2;

			h4[i].style.fontSize = s+"px"
			localStorage.setItem('h4-fontsize', s);
		}
	}
}

function restoreFontSize() {
	var fontsize = localStorage.getItem('fontsize');
	if (fontsize == null)
		return;

	var h2fontsize = localStorage.getItem('h2-fontsize');
	var h3fontsize = localStorage.getItem('h3-fontsize');
	var h4fontsize = localStorage.getItem('h4-fontsize');

	var p = document.getElementsByTagName('p');
	var pre = document.getElementsByTagName('pre');
	var li = document.getElementsByTagName('li');
	var table= document.getElementsByTagName('table');
	var cite= document.getElementsByTagName('cite');
	var h2= document.getElementsByTagName('h2');
	var h3= document.getElementsByTagName('h3');
	var h4= document.getElementsByTagName('h4');

	for(i=0;i<p.length;i++) {
		p[i].style.fontSize = fontsize+"px"
	}
	for(i=0;i<pre.length;i++) {
		pre[i].style.fontSize = fontsize+"px"
	}
	for(i=0;i<li.length;i++) {
		li[i].style.fontSize = fontsize+"px"
	}
	for(i=0;i<table.length;i++) {
		table[i].style.fontSize = fontsize+"px"
	}
	for(i=0;i<cite.length;i++) {
		cite[i].style.fontSize = fontsize+"px"
	}
	for(i=0;i<h2.length;i++) {
		h2[i].style.fontSize = h2fontsize+"px"
	}
	for(i=0;i<h3.length;i++) {
		h3[i].style.fontSize = h3fontsize+"px"
	}
	for(i=0;i<h4.length;i++) {
		h4[i].style.fontSize = h4fontsize+"px"
	}
}
restoreFontSize();
