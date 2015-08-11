function getRandomInt(min, max) {
	return Math.floor(Math.random() * (max - min)) + 1 ;
}
	
function geronimo (tablica, wheight, predkosci, wwidth) {	
	for (var licznik=0, random_speed=getRandomInt(1,5); 
	licznik < tablica.length; licznik++,
	random_speed=getRandomInt(1,10)) {
		var val1 = tablica[licznik].offsetTop;
		tablica[licznik].style.top = (val1 + predkosci[licznik]) + "px";
		document.getElementById('test').innerHTML = licznik;
		if(val1 > wheight){
			tablica[licznik].style.top = -10 + "px";
			tablica[licznik].style.left = getRandomInt(-50, wwidth)+"px";
			predkosci[licznik] = getRandomInt(1,10);
		}


	}
}

function snieg() {
	var licznik = 0;
	var max = 50;
	var wwidth = innerWidth;
	var wheight = innerHeight;
	var tablica = [];
	var predkosci = [];
	var sniezyca = document.createElement('div');
	sniezyca.id = "sniezyca";
	sniezyca.style.top = 0;
	sniezyca.style.left = 0;
	sniezyca.style.height = "100%";
	sniezyca.style.width = "100%";
	sniezyca.style.color = "white";
	sniezyca.style.position = "fixed";
	document.getElementsByTagName('body')[0].appendChild(sniezyca);

		
	while(licznik < max) {
		var platek = document.createElement('div');
		platek.className = "platek";
		platek.style.fontSize = getRandomInt(10,40) + "px";
		platek.style.top = getRandomInt(-50, wheight)+"px";
		platek.style.left = getRandomInt(-50, wwidth)+"px";
		platek.style.color = "white";
		platek.style.position = "absolute";
		platek.innerHTML = "*";
		var newplatek = sniezyca.appendChild(platek);
		tablica.push(newplatek);
		predkosci.push(getRandomInt(1,10));
		licznik ++;
	}
	var ojakspadaja = setInterval(function() { geronimo(tablica, wheight, predkosci, wwidth); }, 1);
}