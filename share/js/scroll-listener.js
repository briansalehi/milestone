function scrollDownListener() {
  window.addEventListener(
    "keydown",
    function(event) {
      if (event.key == "j") {
        window.scrollBy(0, window.screen.height / 4)
      }
    }
  )
}

function scrollUpListener() {
  window.addEventListener(
    "keydown",
    function(event) {
      if (event.key == "k") {
        window.scrollBy(0, -(window.screen.height / 4))
      }
    }
  )
}

scrollDownListener()
scrollUpListener()
