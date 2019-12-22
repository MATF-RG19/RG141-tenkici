#include<GL/gl.h>
#include<GL/glut.h>
#include<iostream>
#include<string>

using namespace std;

#ifndef GUI
#define GUI

void azuriraj_dimenzije(int sirina,int visina);
void azuriraj_mis(int x,int y,int click);
bool dugme(string text,int x,int y,int sirina,int visina);
void label(string text,int x,int y,int sirina,int visina);
bool dugme_manji(string text,int x,int y,int sirina,int visina);
bool dugme_slika(unsigned int slika,int x,int y,int sirina,int visina);
void frejm(int x,int y,int sirina,int visina);
void helt_bar(int x,int y,int sirina,int visina,int max,int tek);
void reset();
#endif