function darkmode() {
	var bodystyle = document.body;
	var icon = document.getElementById('darkmode-icon');
	const dark = sessionStorage.getItem('darkmode');

	if (dark === 'true' || dark == 'undefined') {
		bodystyle.classList.add("dark-mode");
		sessionStorage.setItem('darkmode', true);
		icon.innerHTML = '&#x2600;';
	} else {
		sessionStorage.setItem('darkmode', false);
		bodystyle.classList.remove("dark-mode");
		icon.innerHTML = '&#x2600;';
	}
}
darkmode();

function toggle_darkmode() {
	var bodystyle = document.body;
	var icon = document.getElementById('darkmode-icon');
	const dark = sessionStorage.getItem('darkmode');

	if (dark === 'true' || dark == 'undefined') {
		bodystyle.classList.remove("dark-mode");
		sessionStorage.setItem('darkmode', false);
		icon.innerHTML = '&#x2600;';
		toggle_settings();
	} else {
		sessionStorage.setItem('darkmode', true);
		bodystyle.classList.add("dark-mode");
		icon.innerHTML = '&#x2600;';
		toggle_settings();
	}
}
