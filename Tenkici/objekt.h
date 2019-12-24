#include<GL/gl.h>
#include<GL/glut.h>
#include<iostream>
#include<vector>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>

using namespace std;

#ifndef OBJEKT
#define OBJEKT

//strukture za objekte koji se ucitavaju iz obj fajlova

    struct vektor3{
        float x,y,z;
    };

    struct vektor2{
        double x,y;
    };

    class Material{
        public:
        vector<vektor3> temena;
        vector<vektor3> normale;
        vector<vektor2> tex_cord;
        unsigned int tex_id;
        string ime;
    };
    class Objekat{
        public:
        vector<Material> materiali;
        string ime;
    };
    class Model{
        public:
        vector<Objekat> objekti;
    };

    unsigned int ucitaj_sliku(string putanja);
    unsigned int ucitaj_sliku1(string putanja);
    Model ucitaj_obj_fajl(string putanja);
    void crtaj_model(Model m);
    void crtaj_objekat(Objekat o);
    void crtaj_material(Material m);
#endif