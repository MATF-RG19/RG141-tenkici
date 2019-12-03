# RG141-tenkici
Tenkici

Ovo je 3d igra u kojoj igrac kontrolise svog tenkica i ima ulogu da unisti sve neprijateljske tenkice kako bi zavrsio nivo.Ima mogucnost kreiranja svojih nivoa pomocu alatke nivo editora.

Pokretanje:  
Pozicionirati se u folder Tenkici zatim izvrsiti narednu komandu iz terminala:  
g++ -std=c++11 Tenkici.cpp Nivo.cpp -lGL -lGLU -lglut  
zatim izvrsiti:  
./a.out  
Pri pokretanju se nalazite u meniju i potrebno je pritisnuti 1 ili 2 da bi ste usli u editor/igru  
(Vracanje nazad trenutno ne radi mrzi me da popravljam)


#### Kontrole za meni:

| Taster      | Funkcija |
| ----------- | ----------- |
| **1**       | Pokreni editor nivoa       |
| **2**   | Pokreni 1.nivo (mora da postoji fajl)        |


#### Kontrole za editor:

| Taster      | Funkcija |
| ----------- | ----------- |
| **w,a,s,d**       | pomeranje kamere       |
| **q,e**   | spustanje/podizanje kamere        |
| **t**   | cuvanje terena u fajl        |
| **p**   | ucitavanje terena iz fajla        |
| **f**   | obrada terena        |
| **m**   | prikaz cvorova za kretanje (ukljuci/iskljuci)        |
| **1 .. 5**   | sirina za crtanje        |
| **z,x,c,v**   | tip terena:zemlja,zid,voda,drvo        |
| **[**   | pocetak za trazenje puta        |
| **]**   | cilj za trazenje puta        |
| **j**   | prikazi put od pocetka do cilja        |


#### Kontrole za igru:

| Taster      | Funkcija |
| ----------- | ----------- |
| **w,s**       | Pokreni tenk napred/nazad       |
| **a,d**   | Rotiraj tenk levo/desno        |



