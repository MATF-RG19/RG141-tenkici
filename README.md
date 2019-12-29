# RG141-tenkici
Tenkici

Ovo je 3d igra u kojoj igrac kontrolise svog tenkica i ima ulogu da unisti sve neprijateljske tenkice kako bi zavrsio nivo.Ima mogucnost kreiranja svojih nivoa pomocu alatke nivo editora.

**Pokretanje**:  
Pozicionirati se u folder Tenkici zatim izvrsiti narednu komandu iz terminala:  
**g++ -std=c++14 Tenkici.cpp Nivo.cpp Neprijatelj.cpp gui.cpp objekt.cpp -lGL -lglut -lm -lGLU**  
  
za windows: *g++ -std=c++14 Tenkici.cpp Nivo.cpp Neprijatelj.cpp gui.cpp objekt.cpp -lfreeglut -lopengl32 -lm -lglu32*
  (Potreban je instaliran glut sa bibliotekama za windows da bi radilo)
 
zatim izvrsiti:  
./a.out   
  Napomena u editoru je potrebno postaviti igraca na neku poziciju da bi radila igra


#### Kontrole za editor:

| Taster      | Funkcija |
| ----------- | ----------- |
| **w,a,s,d**       | pomeranje kamere       |
| **q,e**   | spustanje/podizanje kamere        |
| **t**   | cuvanje terena u fajl        |
| **p**   | ucitavanje terena iz fajla        |
| **f**   | obrada terena        |
| **g**   | postavljanje neprijatelja        |
| **h**   | postavljanje igraca        |
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
| **mis pomeraj**   | Rotiraj gornji deo tenka levo/desno        |
| **mis klik**   | pucanje (otprilike 1 sekunda se ceka do sledeceg pucanja)        |



