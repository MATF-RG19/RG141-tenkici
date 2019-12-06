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
#include<queue>
#include "Nivo.h"

#ifndef NEPRIJATELJ
#define NEPRIJATELJ

using namespace std;
#define Setanje 0
#define Napad 1


class Neprijatelj{
public:
    Neprijatelj(float x,float z);
    void radi_nesto(Nivo *nivo,pair<float,float> igrac);
    int helti=100;
    void crtaj();
    void crtaj_mrtvog();
    float x,z;
    float angle=0;
    float angle_up=0;
    int mode=Setanje;
    queue<pair<float,float>> put;
    float vx=0;
    float vz=0;
    int sec=100;
    int brzina_napada=100;
};

#endif
