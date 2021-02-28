function darkmode() {
	var bodystyle = document.body;
	var icon = document.getElementById('darkmode-icon');
	const dark = sessionStorage.getItem('darkmode');
	console.log(dark);

	if (dark === 'true' || dark == 'undefined') {
		bodystyle.classList.add("dark-mode");
		sessionStorage.setItem('darkmode', true);
		icon.innerHTML = '&#x1F312;';
	} else {
		sessionStorage.setItem('darkmode', false);
		bodystyle.classList.remove("dark-mode");
		icon.innerHTML = '&#x1F315;';
	}
}
darkmode();

function toggle_darkmode() {
	var bodystyle = document.body;
	var icon = document.getElementById('darkmode-icon');
	const dark = sessionStorage.getItem('darkmode');
	console.log(dark);

	if (dark === 'true' || dark == 'undefined') {
		bodystyle.classList.remove("dark-mode");
		sessionStorage.setItem('darkmode', false);
		icon.innerHTML = '&#x1F315;';
	} else {
		sessionStorage.setItem('darkmode', true);
		bodystyle.classList.add("dark-mode");
		icon.innerHTML = '&#x1F312;';
	}
}
