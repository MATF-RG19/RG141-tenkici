# RG141-tenkici
Tenkici

Ovo je 3d igra u kojoj igrac kontrolise svog tenkica i ima ulogu da unisti sve neprijateljske tenkice kako bi zavrsio nivo.Ima mogucnost kreiranja svojih nivoa pomocu alatke nivo editora.

Pokretanje:  
Pozicionirati se u folder Tenkici zatim izvrsiti narednu komandu iz terminala:  
g++ -std=c++11 Tenkici.cpp Nivo.cpp -lGL -lGLU -lglut  
zatim izvrsiti:  
./a.out  

Nivo editor komande:  
w,a,s,d - pomeranje kamere  
q,e - spustanje/podizanje kamere  
t - cuvanje terena u fajl 1.nivo  
p - ucitavanje terena iz fajla 1.nivo (ukoliko postoji)  
f - obrada terena tj. racunanje cvorova po kojim moze da se krece kompjuter  
m - ukljuci/iskljuci prikazivanje cvorova za kretanje kompjutera  
1..5 - sirina za crtanje po terenu  
z,x,c,v - tipovi terena redom : zemlja , zid , voda , drvo  
[ - postavi pocetak za trazenje puta  
] - postavi cilj za trazenje puta  
j - trazi put i prikazi  

mis klik - postavi trenutno izabrani tip sa trenutnom sirinom



