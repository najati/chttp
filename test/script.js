
function ready(fn) {
  if (document.attachEvent ? document.readyState === "complete" : document.readyState !== "loading"){
    fn();
  } else {
    document.addEventListener('DOMContentLoaded', fn);
  }
}

ready(function() {
	var counter = 0;
	setInterval(function() {
		counter += 1;
		document.querySelector(".counter").innerHTML = counter;
	}, 1000);
});
