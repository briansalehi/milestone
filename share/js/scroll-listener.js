function scrollDownListener() {
  window.addEventListener(
    "keydown",
    function(event) {
      if (event.key == "j") {
        var screen_height = window.screen.height / 4;
        window.scrollTo({top: screen_height, behavior: 'smooth'})
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
        window.scrollTo({top: -screen_height, behavior: 'smooth'})
      }
    }
  )
}

scrollDownListener()
scrollUpListener()
