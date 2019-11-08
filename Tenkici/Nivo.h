#include<GL/gl.h>
#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
#include<fstream>
#include<string>

using namespace std;

#ifndef NIVO
#define NIVO

#define IZABRANA 8
#define ZEMLJA 1
#define ZID 2
#define VODA 3
#define DRVO 4


//Sadrzi podatak o jednoj plocici njen tip kao i tacke za kretanje po njoj
class Plocica{
public:

    Plocica(float x,float z);
    void crtaj();
    bool jel_hodljiv();
    void postavi_tip(int tip);
    void postavi(int x,int y,bool vrednost);
    int  daj_tip();
    
private:
    pair<pair<float,float>,bool> temena[3][3];
    bool hodljiv;
    int tip;
};

//Sadrzi podatak o terenu za dati nivo u vidu matrice klasa plocica
class Nivo{
public:

    Nivo(int n,int m);
    ~Nivo();

    void procesuj();
    void crtaj_teren();
    void izaberi_plocicu(float x,float z,int n,int tip);
    void sacuvaj_teren();
    Nivo* ucitaj_teren(string path);
    void prikazi_tacke(bool vr);
    bool nabavi_prikaz_tacke();

private:
    vector<vector<Plocica*>> teren;
    int n,m;

};

#endif