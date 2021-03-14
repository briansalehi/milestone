var current_position = 0;

function scrollDownListener() {
  window.addEventListener(
    "keydown",
    function(event) {
      if (event.key == "j") {
        var screen_height = window.screen.height / 4;
		current_position += screen_height;
        window.scrollTo({top: current_position, behavior: 'smooth'})
      }
    }
  )
}

function scrollUpListener() {
  window.addEventListener(
    "keydown",
    function(event) {
      if (event.key == "k") {
        var screen_height = window.screen.height / 4;
		current_position -= screen_height;
		if (current_position < 0) {
			current_position = 0;
		}
        window.scrollTo({top: current_position, behavior: 'smooth'})
      }
    }
  )
}

scrollDownListener()
scrollUpListener()
