function round(get){

	function getRandom (min, max) {
		return Math.floor(Math.random() * (max - min)) + 1;
	}
	
	var counter = 1;
	var parts = 36;
	var angle = 10;
	var color = ['red', 'blue', 'yellow', 'white', 'khaki', 'green', 'brown', 'cyan', 'magenta', 'orange', 'violet', 'pink'];
	var circle_parts=[];
	
	var main = document.createElement('div');
	main.id = "main";
	var random = getRandom(0,11);
	var getColor = color[random];
	main.style.backgroundColor = getColor;
	document.getElementsByTagName('body')[0].appendChild(main);
	
	var test = document.createElement('div');
	test.className = 'test';
	document.getElementsByTagName('body')[0].appendChild(test);
	
		while (counter < parts) {
			var part = document.createElement('div');
			part.className = 'part';
			random = getRandom(0,11);
			getColor = color[random];
			part.style.backgroundColor = getColor;
			part.style.backgroundImage = "-webkit-linear-gradient (" + ((counter+1)*angle) + "deg, transparent:50%," + getColor + ":50%)",
										"-webkit-linear-gradient (" + (counter*angle) + "deg," + getColor + ":50%, transparent: 50%)";

			main.appendChild(part);
			circle_parts.push(part);
			counter ++;
		}
	test.innerHTML = random;
}