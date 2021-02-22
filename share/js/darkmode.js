function darkmode(manual) {
	const hours = new Date().getHours();
	const isNight = !(hours > 6 && hours < 20);
	var bodystyle = document.body;
	if (isNight || manual) {
		bodystyle.classList.add("dark-mode");
	} else {
		bodystyle.classList.remove("dark-mode");
	}
}
darkmode();
