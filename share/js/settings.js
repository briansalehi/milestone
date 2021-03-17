function toggle_settings() {
	var button_list = document.getElementById('dropdown-content');

	if (button_list.style.display != "none") {
		button_list.style.display = "none";
	} else {
		button_list.style.display = "block";
	}
}
toggle_settings();
