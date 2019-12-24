#include "objekt.h"

unsigned int ucitaj_sliku(string putanja){
    FILE *file=fopen(putanja.c_str(),"rb");
    if(file==NULL){
        return 10000;
    }
    unsigned int sirina;
    unsigned int visina;
    unsigned short bit_c;
    unsigned int djubre;

  fread(&djubre, 2, 1, file);
  fread(&djubre, 4, 1, file);
  fread(&djubre, 2, 1, file);
  fread(&djubre, 2, 1, file);
  fread(&djubre, 4, 1, file);

  /* Ocitavaju se podaci drugog zaglavlja. */
  fread(&djubre, 4, 1, file);
  fread(&sirina, 4, 1, file);
  fread(&visina, 4, 1, file);
  fread(&djubre, 2, 1, file);
  fread(&bit_c, 2, 1, file);
  fread(&djubre, 4, 1, file);
  fread(&djubre, 4, 1, file);
  fread(&djubre, 4, 1, file);
  fread(&djubre, 4, 1, file);
  fread(&djubre, 4, 1, file);
  fread(&djubre, 4, 1, file);

  char *pixeli;
  unsigned char r,g,b,a;
  if(bit_c==24)
    pixeli=(char *)malloc(3*sirina*visina*sizeof(char));
else if(bit_c==32)
    pixeli=(char *)malloc(4*sirina*visina*sizeof(char));
else 
    return 10001;
    if(bit_c==24)
    for (int i = 0; i < sirina * visina; i++) {
      fread(&b, sizeof(char), 1, file);
      fread(&g, sizeof(char), 1, file);
      fread(&r, sizeof(char), 1, file);

      pixeli[3 * i] =r;
      pixeli[3 * i + 1] = g;
      pixeli[3 * i + 2] = b;
    }
    if(bit_c==32)
    for (int i = 0; i < sirina * visina; i++) {
      fread(&b, sizeof(char), 1, file);
      fread(&g, sizeof(char), 1, file);
      fread(&r, sizeof(char), 1, file);
      fread(&a, sizeof(char), 1, file);

      pixeli[4 * i] = g;
      pixeli[4 * i + 1] = b;
      pixeli[4 * i + 2] = r;
      pixeli[4 * i + 3] = a;
    }
    unsigned int id;
    glGenTextures(1,&id);
    glBindTexture(GL_TEXTURE_2D,id);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 sirina, visina, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, pixeli);
    free(pixeli);
    fclose(file);
    glBindTexture(GL_TEXTURE_2D,0);
    cout<<"id je "<<id<<endl;
  return id;
}
//Citamo red po red ako naletimo na teme ucitamo isto za koordinatu texture i normalu
//na kraju samo rasporedimo preko datim pljosnima sto pise u fajlu i dobijemo model
Model ucitaj_obj_fajl(string putanja){
  Model tekuci;
  vector<vektor3> temena;
  vector<vektor3> normale;
  vector<vektor2> tex_cord;
  ifstream citac(putanja);
  if(citac.is_open()){
    string linija;
    while(getline(citac,linija)){
      if(linija.rfind("v ",0)==0){
        float x,y,z;
        sscanf(linija.c_str(),"v %f%f%f",&x,&y,&z);
        temena.push_back({x,y,z});
      }
      if(linija.rfind("vn ",0)==0){
        float x,y,z;
        sscanf(linija.c_str(),"vn %f%f%f",&x,&y,&z);
        normale.push_back({x,y,z});
      }
      if(linija.rfind("vt ",0)==0){
        double x,y;
        sscanf(linija.c_str(),"vt %lf%lf",&x,&y);
        tex_cord.push_back({x,y});
      }
      if(linija.rfind("o ",0)==0){
        string ime=linija.substr(2);
        Objekat obj;
        obj.ime=ime;
        tekuci.objekti.push_back(obj);
      }
      if(linija.rfind("usemtl ",0)==0){
        string ime=linija.substr(7);
        Material mat;
        mat.ime=ime;
        tekuci.objekti.back().materiali.push_back(mat);
      }
      if(linija.rfind("f ",0)==0){
        int x1,x2,x3;
        int y1,y2,y3;
        int z1,z2,z3;
        sscanf(linija.c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d",&x1,&y1,&z1 ,&x2,&y2,&z2, &x3,&y3,&z3);
        tekuci.objekti.back().materiali.back().temena.push_back(temena[x1-1]);
        tekuci.objekti.back().materiali.back().tex_cord.push_back(tex_cord[y1-1]);
        tekuci.objekti.back().materiali.back().normale.push_back(normale[z1-1]);

        tekuci.objekti.back().materiali.back().temena.push_back(temena[x2-1]);
        tekuci.objekti.back().materiali.back().tex_cord.push_back(tex_cord[y2-1]);
        tekuci.objekti.back().materiali.back().normale.push_back(normale[z2-1]);

        tekuci.objekti.back().materiali.back().temena.push_back(temena[x3-1]);
        tekuci.objekti.back().materiali.back().tex_cord.push_back(tex_cord[y3-1]);
        tekuci.objekti.back().materiali.back().normale.push_back(normale[z3-1]);
      }
    }
  }
  citac.close();
  return tekuci;
}

unsigned int ucitaj_sliku1(string putanja){
  FILE *file=fopen(putanja.c_str(),"rb");
    if(file==NULL){
        return 10000;
    }
    unsigned int sirina;
    unsigned int visina;
    unsigned short bit_c;
    unsigned int djubre;

  fread(&djubre, 2, 1, file);
  fread(&djubre, 4, 1, file);
  fread(&djubre, 2, 1, file);
  fread(&djubre, 2, 1, file);
  fread(&djubre, 4, 1, file);

  /* Ocitavaju se podaci drugog zaglavlja. */
  fread(&djubre, 4, 1, file);
  fread(&sirina, 4, 1, file);
  fread(&visina, 4, 1, file);
  fread(&djubre, 2, 1, file);
  fread(&bit_c, 2, 1, file);
  fread(&djubre, 4, 1, file);
  fread(&djubre, 4, 1, file);
  fread(&djubre, 4, 1, file);
  fread(&djubre, 4, 1, file);
  fread(&djubre, 4, 1, file);
  fread(&djubre, 4, 1, file);

  char *pixeli;
  unsigned char r,g,b,a;
  if(bit_c==24)
    pixeli=(char *)malloc(3*sirina*visina*sizeof(char));
else if(bit_c==32)
    pixeli=(char *)malloc(4*sirina*visina*sizeof(char));
else 
    return 10001;
    if(bit_c==24)
    for (int i = 0; i < sirina * visina; i++) {
      fread(&b, sizeof(char), 1, file);
      fread(&g, sizeof(char), 1, file);
      fread(&r, sizeof(char), 1, file);

      pixeli[3 * i] =g;
      pixeli[3 * i + 1] = b;
      pixeli[3 * i + 2] = r;
    }
    if(bit_c==32)
    for (int i = 0; i < sirina * visina; i++) {
      fread(&b, sizeof(char), 1, file);
      fread(&g, sizeof(char), 1, file);
      fread(&r, sizeof(char), 1, file);
      fread(&a, sizeof(char), 1, file);

      pixeli[4 * i] = g;
      pixeli[4 * i + 1] = b;
      pixeli[4 * i + 2] = r;
      pixeli[4 * i + 3] = a;
    }
    unsigned int id;
    glGenTextures(1,&id);
    glBindTexture(GL_TEXTURE_2D,id);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 sirina, visina, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, pixeli);
    free(pixeli);
    fclose(file);
    glBindTexture(GL_TEXTURE_2D,0);
    cout<<"id je "<<id<<endl;
  return id;
}

void crtaj_model(Model m){
  glColor3f(1,1,1);
  for(Objekat o:m.objekti)
    crtaj_objekat(o);
}
void crtaj_objekat(Objekat o){
  for(Material m:o.materiali)
    crtaj_material(m);
}
void crtaj_material(Material m){
  glColor3f(1,1,1);
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,m.tex_id);
  glBegin(GL_TRIANGLES);
  for(int i=0;i<m.temena.size();i++){
    glNormal3f(m.normale[i].x,m.normale[i].y,m.normale[i].z);
    glTexCoord2f(m.tex_cord[i].x,m.tex_cord[i].y);
    glVertex3f(m.temena[i].x,m.temena[i].y,m.temena[i].z);
  }
  glEnd();
  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D,0);
}