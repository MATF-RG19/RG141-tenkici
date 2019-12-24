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
#include "objekt.h"

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
extern unsigned int trava_text;
extern unsigned int voda_text;


struct Cvor{
    int i;
    int j;
    float x_pos;
    float z_pos;
};

extern Model drvo_model;
extern Model zid_model;

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

extern Model igrac_tenk;
extern pair<int,int> tek_igrac;
class Igrac{
    public:
     float x, z;
     float px, pz;
     float cev_x;
     float cev_z;
    int sec=70;
    int brzina_napada=70;
     int health=100;
     void crtaj(){
         glEnable(GL_DEPTH_TEST);
         glColor3f(1,1,1);
         if(sec<brzina_napada)sec++;
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        GLfloat ni[]={-cev_x,3,-cev_z,0};
        
        glLightfv(GL_LIGHT0,GL_POSITION,ni);


        glEnable(GL_LIGHT1);
        GLfloat ni1[]={x,1,z,1};
        GLfloat li1[]={1,1,1,1};
        glLightfv(GL_LIGHT1,GL_POSITION,ni1);
        glLightfv(GL_LIGHT1,GL_DIFFUSE,li1);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


        glPushMatrix();
         glTranslatef(x,0.25,z);
         glRotatef((-angle*180)/3.14+90,0,1,0);
         glScalef(0.5,0.5,0.5);
         crtaj_objekat(igrac_tenk.objekti[1]);
        glPopMatrix();
        glPushMatrix();
         glTranslatef(x,0.25,z);
         glRotatef((-angle_up*180)/3.14+90,0,1,0);
         glScalef(0.5,0.5,0.5);
         crtaj_objekat(igrac_tenk.objekti[0]);
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
        GLfloat niz[]={0.9,0.9,0.9,1};
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,niz);
        if(nas_metak)
        glColor3f(0.9,0.9,0.9);
        else{
            GLfloat niz1[]={0.0,0.0,0.0,1};
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,niz1);
        glColor3f(0,0,0);
        }
        glTranslatef(x,0.3f,z);
        glScalef(0.7,0.7,0.7);
        glutSolidSphere(0.1,10,10);
        x+=dx*0.2;
        z+=dz*0.2;
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,niz);
    glPopMatrix();
 }
};

extern vector<unique_ptr<Metak>> nivo_granate;
#endif