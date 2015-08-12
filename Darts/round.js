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
			var mother = document.createElement('div');
			mother.className = "main";
			mother.style.top = "-250px";
			mother.style.left = "-250px";
			mother.style.transform = "rotate("+counter*angle+"deg)";
			mother.appendChild(part);
			main.appendChild(mother);
			circle_parts.push(mother);
			counter ++;
		}
		for (counter = 1; counter < circle_parts.length; counter++) 	{
			circle_parts[counter].style.transform = "rotate("+counter*angle+"deg)";
			counter ++;
			if (circle_parts[counter].style.transform = "rotate(360deg)"){
				circle_parts[counter].style.transform = "rotate(0deg)";
				}
		}
	test.innerHTML = random;
}