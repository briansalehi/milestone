function darkmode() {
	var bodystyle = document.body;
	const dark = sessionStorage.getItem('darkmode');
	console.log(dark);

	if (dark === 'true' || dark == 'undefined') {
		bodystyle.classList.add("dark-mode");
		sessionStorage.setItem('darkmode', true);
	} else {
		sessionStorage.setItem('darkmode', false);
		bodystyle.classList.remove("dark-mode");
	}
}
darkmode();

function toggle_darkmode() {
	var bodystyle = document.body;
	const dark = sessionStorage.getItem('darkmode');
	console.log(dark);

	if (dark === 'true' || dark == 'undefined') {
		bodystyle.classList.remove("dark-mode");
		sessionStorage.setItem('darkmode', false);
	} else {
		sessionStorage.setItem('darkmode', true);
		bodystyle.classList.add("dark-mode");
	}
}
