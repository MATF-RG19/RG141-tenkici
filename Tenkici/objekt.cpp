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