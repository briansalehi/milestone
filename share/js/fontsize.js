var min_level  = 1;
var max_level  = 12;
var fontlevel  = localStorage.getItem('fontlevel');
var fontsize   = localStorage.getItem('fontsize');
var h2fontsize = localStorage.getItem('h2fontsize');
var h3fontsize = localStorage.getItem('h3fontsize');
var h4fontsize = localStorage.getItem('h4fontsize');

if (fontlevel  == null) { fontlevel  =  3; }
if (fontsize   == null) { fontsize   = 14; }
if (h2fontsize == null) { h2fontsize = 30; }
if (h3fontsize == null) { h3fontsize = 24; }
if (h4fontsize == null) { h4fontsize = 18; }

function defaultFontSize() {
	fontlevel  =  3;
	fontsize   = 14;
	h2fontsize = 30;
	h3fontsize = 24;
	h4fontsize = 18;
	localStorage.setItem('fontlevel' , fontlevel );
	localStorage.setItem('fontsize'  , fontsize  );
	localStorage.setItem('h2fontsize', h2fontsize);
	localStorage.setItem('h3fontsize', h3fontsize);
	localStorage.setItem('h4fontsize', h3fontsize);

	restoreFontSize();
	document.getElementById('dropdown-content').style.display = 'none';
}

function zoominLetter() {
	if (fontlevel < max_level) {
		fontlevel++;
		fontsize += 2;
		h2fontsize += 2;
		h3fontsize += 2;
		h4fontsize += 2;

		localStorage.setItem('fontlevel' , fontlevel );
		localStorage.setItem('fontsize'  , fontsize  );
		localStorage.setItem('h2fontsize', h2fontsize);
		localStorage.setItem('h3fontsize', h3fontsize);
		localStorage.setItem('h4fontsize', h4fontsize);

		restoreFontSize();
	}
}

function zoomoutLetter() {
	if (fontlevel > min_level) {
		fontlevel--;
		fontsize -= 2;
		h2fontsize -= 2;
		h3fontsize -= 2;
		h4fontsize -= 2;

		localStorage.setItem('fontlevel' , fontlevel );
		localStorage.setItem('fontsize'  , fontsize  );
		localStorage.setItem('h2fontsize', h2fontsize);
		localStorage.setItem('h3fontsize', h3fontsize);
		localStorage.setItem('h4fontsize', h4fontsize);

		restoreFontSize();
	}
}

function restoreFontSize() {
	var fontsize   = localStorage.getItem('fontsize');
	var h2fontsize = localStorage.getItem('h2fontsize');
	var h3fontsize = localStorage.getItem('h3fontsize');
	var h4fontsize = localStorage.getItem('h4fontsize');

	var p     = document.getElementsByTagName('p');
	var pre   = document.getElementsByTagName('pre');
	var ul    = document.getElementsByTagName('ul');
	var ol    = document.getElementsByTagName('ol');
	var table = document.getElementsByTagName('table');
	var cite  = document.getElementsByTagName('cite');
	var toc   = document.getElementsByClassName('list-group');
	var bar   = document.getElementsByClassName('difficulty');
	var h2    = document.getElementsByTagName('h2');
	var h3    = document.getElementsByTagName('h3');
	var h4    = document.getElementsByTagName('h4');

	for(i=0 ; i<p.length ; i++) {
		p[i].style.fontSize     = fontsize+"px"
	}
	for(i=0;i<pre.length;i++) {
		pre[i].style.fontSize = fontsize+"px"
	}
	for(i=0;i<ul.length;i++) {
		ul[i].style.fontSize = fontsize+"px"
	}
	for(i=0;i<ol.length;i++) {
		ol[i].style.fontSize = fontsize+"px"
	}
	for(i=0;i<table.length;i++) {
		table[i].style.fontSize = fontsize+"px"
	}
	for(i=0;i<cite.length;i++) {
		cite[i].style.fontSize = fontsize+"px"
	}
	for(i=0;i<toc.length;i++) {
		toc[i].style.fontSize = fontsize+"px"
	}
	for(i=0;i<bar.length;i++) {
		bar[i].style.fontSize = fontsize+"px"
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
