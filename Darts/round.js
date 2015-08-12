function round(get){

	function getRandom (min, max) {
		return Math.floor(Math.random() * (max - min)) + 1;
	}
	
	var counter = 0;
	var parts = 35;
	var angle = 10;
	var color = ['red', 'blue', 'yellow', 'white', 'khaki', 'green', 'brown', 'cyan', 'magenta', 'orange', 'violet', 'pink'];
	var circle_parts=[];
	var random = getRandom(0,11);

	var main = document.createElement('div');
	main.id = "main";
	document.getElementsByTagName('body')[0].appendChild(main);
	
	var test = document.createElement('div');
	test.className = 'test';
	document.getElementsByTagName('body')[0].appendChild(test);
	
	while(counter < parts) {
		var part = document.createElement('div');
		part.className = 'part';
		var getColor = color[random];
		part.style.backgroundColor = '-webkit-linear-gradient(' + ((counter+1)*angle) + ', transparent: 50%, ' + getColor + ':50%;)';
		part.style.zIndex = 1000;
		main.appendChild(part);
		circle_parts.push(part);
		counter++;
	}
	
	test.innerHTML = random;
}