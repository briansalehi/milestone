var min_level  = 1;
var max_level  = 12;
var fontlevel  = parseInt(localStorage.getItem('fontlevel'));
var fontsize   = parseInt(localStorage.getItem('fontsize'));
var h1fontsize = parseInt(localStorage.getItem('h1fontsize'));
var h2fontsize = parseInt(localStorage.getItem('h2fontsize'));
var h3fontsize = parseInt(localStorage.getItem('h3fontsize'));
var h4fontsize = parseInt(localStorage.getItem('h4fontsize'));

if (!fontlevel)  { fontlevel  =  3; localStorage.setItem('fontlevel', 3 ); }
if (!fontsize)   { fontsize   = 14; localStorage.setItem('fontsize',  14); }
if (!h1fontsize) { h1fontsize = 32; localStorage.setItem('h1fontsize',32); }
if (!h2fontsize) { h2fontsize = 24; localStorage.setItem('h2fontsize',24); }
if (!h3fontsize) { h3fontsize = 18; localStorage.setItem('h3fontsize',18); }
if (!h4fontsize) { h4fontsize = 16; localStorage.setItem('h4fontsize',16); }

function defaultFontSize() {
	fontlevel  =  3;
	fontsize   = 14;
	h1fontsize = 32;
	h2fontsize = 24;
	h3fontsize = 18;
	h4fontsize = 16;
	localStorage.setItem('fontlevel',  fontlevel );
	localStorage.setItem('fontsize',   fontsize  );
	localStorage.setItem('h1fontsize', h1fontsize);
	localStorage.setItem('h2fontsize', h2fontsize);
	localStorage.setItem('h3fontsize', h3fontsize);
	localStorage.setItem('h4fontsize', h3fontsize);

	restoreFontSize();
	document.getElementById('dropdown-content').style.display = 'none';
}

function zoominLetter() {
	if (fontlevel < max_level) {
		fontlevel += 1;
		fontsize += 2;
		h1fontsize += 2;
		h2fontsize += 2;
		h3fontsize += 2;
		h4fontsize += 2;

		localStorage.setItem('fontlevel', fontlevel);
		localStorage.setItem('fontsize', fontsize);
		localStorage.setItem('h1fontsize', h1fontsize);
		localStorage.setItem('h2fontsize', h2fontsize);
		localStorage.setItem('h3fontsize', h3fontsize);
		localStorage.setItem('h4fontsize', h4fontsize);

		restoreFontSize();
	}
}

function zoomoutLetter() {
	if (fontlevel > min_level) {
		fontlevel -= 1;
		fontsize -= 2;
		h1fontsize -= 2;
		h2fontsize -= 2;
		h3fontsize -= 2;
		h4fontsize -= 2;

		localStorage.setItem('fontlevel', fontlevel);
		localStorage.setItem('fontsize', fontsize);
		localStorage.setItem('h1fontsize', h1fontsize);
		localStorage.setItem('h2fontsize', h2fontsize);
		localStorage.setItem('h3fontsize', h3fontsize);
		localStorage.setItem('h4fontsize', h4fontsize);

		restoreFontSize();
	}
}

function restoreFontSize() {
	fontsize   = parseInt(localStorage.getItem('fontsize'));
	h1fontsize = parseInt(localStorage.getItem('h1fontsize'));
	h2fontsize = parseInt(localStorage.getItem('h2fontsize'));
	h3fontsize = parseInt(localStorage.getItem('h3fontsize'));
	h4fontsize = parseInt(localStorage.getItem('h4fontsize'));

	var p     = document.getElementsByTagName('p');
	var pre   = document.getElementsByTagName('pre');
	var ul    = document.getElementsByTagName('ul');
	var ol    = document.getElementsByTagName('ol');
	var table = document.getElementsByTagName('table');
	var cite  = document.getElementsByTagName('cite');
	var toc   = document.getElementsByClassName('list-group');
	var bar   = document.getElementsByClassName('difficulty');
	var h1    = document.getElementsByTagName('h1');
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
	for(i=0;i<h1.length;i++) {
		h1[i].style.fontSize = h1fontsize+"px"
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
