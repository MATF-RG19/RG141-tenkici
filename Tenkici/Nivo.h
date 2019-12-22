#include<GL/gl.h>
#include<GL/glut.h>
#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
#include<fstream>
#include<string>
#include <unistd.h>
#include <GL/freeglut.h>
#include <set>
#include <memory>

using namespace std;

#ifndef NIVO
#define NIVO

#define IZABRANA 8
#define ZEMLJA 1
#define ZID 2
#define VODA 3
#define DRVO 4
#define Nep 5
#define Ig 6

extern unsigned int trava_slika;
extern unsigned int zid_slika;
extern unsigned int drvo_slika;
extern unsigned int voda_slika;

struct Cvor{
    int i;
    int j;
    float x_pos;
    float z_pos;
};

//Sadrzi podatak o jednoj plocici njen tip kao i tacke za kretanje po njoj
class Plocica{
public:

    Plocica(float x,float z);
    void crtaj();
    void crtaj_igra();
    bool jel_hodljiv();
    void postavi_tip(int tip);
    void postavi(int x,int y,bool vrednost);
    pair<pair<float,float>,bool> temena[3][3];
    int  daj_tip();
    
private:
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
    void crtaj_teren_igra();
    void izaberi_plocicu(float x,float z,int n,int tip);
    Plocica* izaberi_plocicu(float i,float j);
    void sacuvaj_teren();
    Nivo* ucitaj_teren(string path);
    void prikazi_tacke(bool vr);
    bool nabavi_prikaz_tacke();
    vector<pair<float,float>> bfs(pair<int,int> lok,pair<int,int> cilj);
    pair<int,int> vrati_indexe_od_koord(float x,float z);
    bool proveri_koliziju(float x,float z);
    bool proveri_koliziju_metak(float x,float z);
    vector<vector<Plocica*>> teren;
    int n,m;
};

class Igrac{
    public:
     float x, z;
     float px, pz;
     float cev_x;
     float cev_z;
    int sec=100;
    int brzina_napada=100;
     int health=100;
     void crtaj(){
         if(sec<brzina_napada)sec++;
        glPushMatrix();
         glColor3f(1,0,0);
         glTranslatef(x,0,z);
         glRotatef((-angle*180)/3.14,0,1,0);
         glutSolidCube(0.8);
         glColor3f(0,0,0);
         glutWireCube(0.8);
        glPopMatrix();
        glPushMatrix();
         glTranslatef(x,0.5,z);
         glRotatef((-angle_up*180)/3.14+90,0,1,0);
         glColor3f(1,0,0);
         glutSolidCube(0.5);
         glutSolidCylinder(0.1,0.8,10,10);
         glColor3f(0,0,0);
         glutWireCube(0.5);
         glutWireCylinder(0.1,0.8,10,10);
        glPopMatrix();
     }
     void pomeri_napred(){
         x+=px*0.06f;
         z+=pz*0.06f;
     }
     void pomeri_nazad(){
         x-=px*0.06f;
         z-=pz*0.06f;
     }
     float angle;
     float angle_up;
     Igrac(){
         x=0;
         z=0;
         px=0;
         pz=0;
         health=100;
         angle=0;
         angle_up=0;
         cev_z=0;
         cev_x=0;
     }
};

class Metak{
public:
float dx,dz;
float x,z;
bool nas_metak;
 Metak(float x,float z,float dx,float dz){
     float norm=sqrt(dx*dx+dz*dz);
     this->dx=dx/norm;
     this->dz=dz/norm;
     this->x=x;
     this->z=z;
 }
 void Crtaj(){
    glPushMatrix();
        if(nas_metak)
        glColor3f(1,0,0);
        else
        glColor3f(0,0,0);
        glTranslatef(x,0.6f,z);
        glutSolidSphere(0.1,10,10);
        x+=dx*0.2;
        z+=dz*0.2;
    glPopMatrix();
 }
};

extern vector<unique_ptr<Metak>> nivo_granate;
#endif