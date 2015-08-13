function game1024(){
	var counter = 0;
	var rows = 4;
	var position = 110;
	var i = 0;
	var main = document.createElement('div');
	main.id = 'main';
	document.getElementsByTagName('body')[0].appendChild(main);
	
	for (i; i < rows; i++){
		while (counter < rows) {
			var tile = document.createElement('div');
			tile.className = "tile";
			tile.style.left = position * counter + "px";
			main.appendChild(tile);
			counter ++
		}	
		tile.style.top = position *counter + "px";
	}
}