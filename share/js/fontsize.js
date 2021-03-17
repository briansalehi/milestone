var minimum_fontsize=1;
var maximum_fontsize=3;
var current_fontsize=2;
var fontsize_growth = "upward";

function zoominLetter() {
   var p = document.getElementsByTagName('p');
   for(i=0;i<p.length;i++) {
      if(p[i].style.fontSize) {
         var s = parseInt(p[i].style.fontSize.replace("px",""));
      } else {
         var s = 16;
      }
	   s += 1;

      p[i].style.fontSize = s+"px"
   }
}

function zoomoutLetter() {
   var p = document.getElementsByTagName('p');
   for(i=0;i<p.length;i++) {
      if(p[i].style.fontSize) {
         var s = parseInt(p[i].style.fontSize.replace("px",""));
      } else {
         var s = 16;
      }
	   s -= 1;

      p[i].style.fontSize = s+"px"
   }
}

function toggle_font() {
	if (fontsize_growth == "downward") {
		zoomoutLetter();
		--current_fontsize;
		if (current_fontsize == minimum_fontsize) {
			fontsize_growth = "upward";
		}
	} else {
		zoominLetter();
		++current_fontsize;
		if (current_fontsize == maximum_fontsize) {
			fontsize_growth = "downward";
		}
	}
	console.log(current_fontsize);
}
