#include<GL/glut.h>
#include<GL/gl.h>
#include "Nivo.h"
#include "Neprijatelj.h"
#include "gui.h"
#include "objekt.h"

bool pauza=false;

float cam_pos_x=0;
float cam_pos_y=-19.8;
float cam_pos_z=0;
float cam_f_y=1;
int mouse_click=0;

bool prvo_pokretanje=true;

static Nivo *tekuci_nivo;


static unsigned int select_nivo=1;
static int select_tip=1;

static int mis_x;
static int mis_y;

double m[16];
double p[16];
int v[4];

float dx=0;
float dy=0;
float dz=0;
int az=0;
bool keys[256];

float cam_igra_x=0;
float cam_igra_y=2;
float cam_igra_z=-5;

Igrac *tekuci_igrac;


void meni_tastatura(unsigned char taster, int x, int y);

void meni_mis(int x,int y);

void meni_klik(int klik,int stanje,int x,int y);
void meni_render();

void pauza_render();

void pauza_klik(int klik,int stanje,int x,int y);

void mis_pauza(int x,int y);

void pauza_tastatura(unsigned char taster, int x, int y);

void pauza_keyup(unsigned char key,int x,int y);


pair<int,int> pocetak=make_pair(-1,-1);
pair<int,int> cilj=make_pair(-1,-1);

float angle=-3.14;

int mouse_x=0;

vector<Neprijatelj *> neprijatelji;


void mis_racunaj(int x,int y){
    GLdouble farx,fary,farz;
    GLdouble nearx,neary,nearz;
    gluUnProject(x,glutGet(GLUT_WINDOW_HEIGHT)-y,1, m, p, v, &farx, &fary, &farz);
    gluUnProject(x,glutGet(GLUT_WINDOW_HEIGHT)-y,0, m, p, v, &nearx, &neary, &nearz);

    float vector_x =farx-nearx;
    float vector_y=fary-neary;
    float vector_z=farz-nearz;

    float t=(-cam_pos_y)/(vector_y);

    dx=cam_pos_x+t*vector_x;
    dy=cam_pos_y+t*vector_y;
    dz=cam_pos_z+t*vector_z;
}

vector<pair<float,float>> put;

float moj_distanca(float x,float y,float x_,float y_){
    return sqrt((x-x_)*(x-x_)+(y_-y)*(y_-y));
}

bool metak_kolizija(unique_ptr<Metak> &m){
    if(moj_distanca(tekuci_igrac->x,tekuci_igrac->z,m->x,m->z)<0.5f && m->nas_metak==false){
        tekuci_igrac->health-=20;
        return true;
    }
    for(Neprijatelj* nep:neprijatelji){
        if(moj_distanca(m->x,m->z,nep->x,nep->z)<0.5f && m->nas_metak==true){
            nep->helti-=50;
            return true;
        }
    }
    if(tekuci_nivo->proveri_koliziju_metak(m->x,m->z)==false){
        return true;
    }
    return false;
}


void tastatura_editor(unsigned char taster, int x, int y){
    if(taster=='a')
        cam_pos_x-=1;
    if(taster=='d')
        cam_pos_x+=1;
    if(taster=='w')
        cam_pos_z+=1;
    if(taster=='s')
        cam_pos_z-=1;
    if(taster=='q')
        cam_pos_y+=1;
    if(taster=='e')
        cam_pos_y-=1;
    if(taster=='z')
        select_tip=1;
    if(taster=='x')
        select_tip=2;
    if(taster=='c')
        select_tip=3;
    if(taster=='v')
        select_tip=4;
    if(taster=='g')
        select_tip=5;
    if(taster=='h')
        select_tip=6;
    if(taster=='t')
        tekuci_nivo->sacuvaj_teren();
    if(taster=='f')
        tekuci_nivo->procesuj();
    if(taster=='m')
        tekuci_nivo->prikazi_tacke(!tekuci_nivo->nabavi_prikaz_tacke());
    if(taster=='['){
        mis_racunaj(x,y);
        pocetak=tekuci_nivo->vrati_indexe_od_koord(dx,dz);
        put.clear();
        az=0;
    }
    if(taster==']'){
        mis_racunaj(x,y);
        cilj=tekuci_nivo->vrati_indexe_od_koord(dx,dz);
        put.clear();
        az=0;
        
    }
    if(taster=='j'){
        if(pocetak!=make_pair(-1,-1) &&  cilj!=make_pair(-1,-1)){
        put=tekuci_nivo->bfs(pocetak,cilj);
        az=1;
        }
    }
    if(taster=='p'){
        delete(tekuci_nivo);
        tekuci_nivo=tekuci_nivo->ucitaj_teren("1.nivo");
    }
    if(taster>='1' && taster<='5')
        select_nivo=(taster-'1')*3;

}

//FUNKCIJA ZA TRAZENJE PRESEKA MISA I TERENA
void mis(int dugme, int stanje, int x,int y){
    GLdouble farx,fary,farz;
    GLdouble nearx,neary,nearz;
    gluUnProject(x,glutGet(GLUT_WINDOW_HEIGHT)-y,1, m, p, v, &farx, &fary, &farz);
    gluUnProject(x,glutGet(GLUT_WINDOW_HEIGHT)-y,0, m, p, v, &nearx, &neary, &nearz);

    //racunanje preseka misa sa daljom i blizom ravni

    float vector_x =farx-nearx;
    float vector_y=fary-neary;
    float vector_z=farz-nearz;

    //racunanje preseka vectora misa sa ravni terena 
    float t=(-cam_pos_y)/(vector_y);

    dx=cam_pos_x+t*vector_x;
    dy=cam_pos_y+t*vector_y;
    dz=cam_pos_z+t*vector_z;
    tekuci_nivo->izaberi_plocicu(dx,dz,select_nivo,select_tip);
    if(stanje==GLUT_DOWN && dugme==GLUT_LEFT_BUTTON)
    azuriraj_mis(x,y,1);
}

void mis_pomera(int x,int y){
    GLdouble farx,fary,farz;
    GLdouble nearx,neary,nearz;
    gluUnProject(x,glutGet(GLUT_WINDOW_HEIGHT)-y,1, m, p, v, &farx, &fary, &farz);
    gluUnProject(x,glutGet(GLUT_WINDOW_HEIGHT)-y,0, m, p, v, &nearx, &neary, &nearz);

    float vector_x =farx-nearx;
    float vector_y=fary-neary;
    float vector_z=farz-nearz;

    float t=(-cam_pos_y)/(vector_y);

    dx=cam_pos_x+t*vector_x;
    dy=cam_pos_y+t*vector_y;
    dz=cam_pos_z+t*vector_z;
    tekuci_nivo->izaberi_plocicu(dx,dz,select_nivo,select_tip);
    azuriraj_mis(x,y,0);
}


void init_GL(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    
}


void render_func_editor(){
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0,1920.0/1080.0,0.1,250.0);
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(135/256.0f,206/256.0f,235/256.0f,1);
    glGetDoublev(GL_PROJECTION_MATRIX,p);
    
    glPushMatrix();

    gluLookAt(cam_pos_x,cam_pos_y,cam_pos_z,
    cam_pos_x,0,cam_pos_z,
    0,0,1
    );
    glGetDoublev(GL_MODELVIEW_MATRIX,m);
    
    glGetIntegerv(GL_VIEWPORT,v);
    tekuci_nivo->crtaj_teren();
    glColor3f(0,0,0);
    
    glPointSize(10);
    glBegin(GL_LINES);
    if(az)
    for(int i=0;i<put.size()-1;i++){
    glVertex3f(put[i].first,0,put[i].second);
    glVertex3f(put[i+1].first,0,put[i+1].second);
    }
    glEnd();
    glBegin(GL_POINTS);
    for(pair<float,float> cvor:put)
    glVertex3f(cvor.first,0,cvor.second);
    if(pocetak!=make_pair(-1,-1)){
        glColor3f(0,0,1);
        Plocica * pl=tekuci_nivo->izaberi_plocicu(pocetak.first,pocetak.second);
        glVertex3f(pl->temena[1][1].first.first,0,pl->temena[1][1].first.second);
    }
    if(cilj!=make_pair(-1,-1)){
        glColor3f(0.8,0.2,0.5);
        Plocica * pl=tekuci_nivo->izaberi_plocicu(cilj.first,cilj.second);
        glVertex3f(pl->temena[1][1].first.first,0,pl->temena[1][1].first.second);
    }
    glEnd();
    glPopMatrix();

    //gki
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,1920,0,1080);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_DEPTH_TEST);
    frejm(1920-200,0,200,1080);
    if(dugme_slika(trava_slika,1920-125,900,50,50))
        select_tip=1;
    if(dugme_slika(zid_slika,1920-125,825,50,50))
        select_tip=2;
    if(dugme_slika(voda_slika,1920-125,825-75,50,50))
        select_tip=3;
    if(dugme_slika(drvo_slika,1920-125,825-150,50,50))
        select_tip=4;
    if(dugme("igrac",1920-175,825-225,150,50))
        select_tip=6;
    if(dugme("nep",1920-175,825-300,150,50))
        select_tip=5;
        label(to_string(select_nivo),1920-175,825-375,50,50);
        if(dugme_manji("-",1920-125,825-375,50,25))
            if(select_nivo>1)
            select_nivo--;
        if(dugme_manji("+",1920-125,825-350,50,25))
            if(select_nivo<10)
            select_nivo++;
    if(dugme_manji("sacuvaj",1920-175,825-450,150,50))
        tekuci_nivo->sacuvaj_teren();
    if(dugme_manji("izadji",1920-175,825-525,150,50)){
        
        glutKeyboardFunc(meni_tastatura);
        glutPassiveMotionFunc(meni_mis);
        glutMouseFunc(meni_klik);
        glutDisplayFunc(meni_render);
    }
    glEnable(GL_DEPTH_TEST);

    glutSwapBuffers();
    glutPostRedisplay();
    glFlush();
}



void igra_render(){

    
        glutSetCursor(GLUT_CURSOR_NONE);
    if(keys['w']==true){
        if(tekuci_nivo->proveri_koliziju(tekuci_igrac->x+tekuci_igrac->px,
        tekuci_igrac->pz+tekuci_igrac->z))
        tekuci_igrac->pomeri_napred();
    }
    if(keys['s']==true){
        if(tekuci_nivo->proveri_koliziju(tekuci_igrac->x-tekuci_igrac->px,
        tekuci_igrac->z-tekuci_igrac->pz))
        tekuci_igrac->pomeri_nazad();
    }
    if(keys['d']==true){
    tekuci_igrac->angle+=0.05;
    }
    if(keys['a']==true){
    tekuci_igrac->angle-=0.05f;
    }
    
    
    tekuci_igrac->pz=sin(tekuci_igrac->angle);
    tekuci_igrac->px=cos(tekuci_igrac->angle);
    tekuci_igrac->cev_x=cos(tekuci_igrac->angle_up);
    tekuci_igrac->cev_z=sin(tekuci_igrac->angle_up);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(135/256.0f,206/256.0f,235/256.0f,1);

    
    
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0,1920.0/1080.0,0.1,250.0);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    cam_igra_x=2*cos(tekuci_igrac->angle_up+3.14);
    cam_igra_z=2*sin(tekuci_igrac->angle_up+3.14);
    gluLookAt(tekuci_igrac->x+cam_igra_x,2,tekuci_igrac->z+cam_igra_z,
    tekuci_igrac->x+2*tekuci_igrac->cev_x,0,tekuci_igrac->z+2*tekuci_igrac->cev_z,
    0,1,0
    );
    tekuci_nivo->crtaj_teren_igra();  
    tekuci_igrac->crtaj();
    glLineWidth(10);
    for(Neprijatelj* nep:neprijatelji){
    if(nep->helti>0){
    nep->radi_nesto(tekuci_nivo,make_pair(tekuci_igrac->x,tekuci_igrac->z));
    nep->crtaj();

    glPushMatrix();
   
    glTranslatef(nep->x,1.25f,nep->z);
    glRotatef(-tekuci_igrac->angle_up*180/3.14+90,0,1,0);
    glScalef(1,0.1,1);
    glTranslatef(0.5,0,0);
    float odnos=(float)nep->helti/100.0;
    glColor3f(1,0,0);
    glBegin(GL_QUADS);
    glVertex3f(0,0,0);
    glVertex3f(-1*odnos,0,0);
    glVertex3f(-1*odnos,1,0);
    glVertex3f(0,1,0);
    glEnd();
    glColor3f(0.2,0.2,0.2);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0,0,0);
    glVertex3f(-1,0,0);
    glVertex3f(-1,1,0);
    glVertex3f(0,1,0);
    glVertex3f(0,0,0);
    glEnd();

    glPopMatrix();
    } else nep->crtaj_mrtvog();
    }
    for(auto it=nivo_granate.begin();it<nivo_granate.end();it++){
        (*it)->Crtaj();
        if(metak_kolizija(*it)==true)
        nivo_granate.erase(it);
    }
    //KOD ZA GUI
    glPopMatrix();

    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,1920,0,1080);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_DEPTH_TEST);
    helt_bar(0,0,300,40,100,tekuci_igrac->health);
    
    glEnable(GL_DEPTH_TEST);


    if(tekuci_igrac->health<=0){
        cout<<"Izgubili ste"<<endl;
        exit(0);
    }
    int br_zivih_nep=neprijatelji.size();
    for(Neprijatelj *n:neprijatelji)
        if(n->helti<=0)
        br_zivih_nep--;
    if(br_zivih_nep==0){
        cout<<"Pobedili ste"<<endl;
        exit(0);
        }
    


        glutSwapBuffers();
        glutPostRedisplay();
        glFlush();
    
}

void klik(int klik,int stanje,int x,int y){
    if(klik==GLUT_LEFT_BUTTON && stanje==GLUT_DOWN && tekuci_igrac->sec==tekuci_igrac->brzina_napada){
        nivo_granate.push_back(make_unique<Metak>(tekuci_igrac->x+tekuci_igrac->cev_x,tekuci_igrac->z+tekuci_igrac->cev_z,tekuci_igrac->cev_x,tekuci_igrac->cev_z));
        nivo_granate.back()->nas_metak=true;
        tekuci_igrac->sec=0;
        azuriraj_mis(x,y,1);
    }
}

void mis_igra(int x,int y){
    int razlika=x-mouse_x;
    mouse_x=x;
    if(razlika>0)
        tekuci_igrac->angle_up+=0.05f;
    if(razlika<0) tekuci_igrac->angle_up-=0.05f;
    
    azuriraj_mis(x,y,0);
}

void igra_tastatura(unsigned char taster, int x, int y){
    
    keys[taster]=true;
    
}

void keyup(unsigned char key,int x,int y){
    if(keys[27]==true && key==27){
        keys[key]=false;
        glutPassiveMotionFunc(mis_pauza);
            glutKeyboardFunc(pauza_tastatura);
            glutMouseFunc(pauza_klik);
            glutKeyboardUpFunc(pauza_keyup);
            glutDisplayFunc(pauza_render);
    }
    keys[key]=false;
}

void meni_tastatura(unsigned char taster, int x, int y){
    
}

void meni_mis(int x,int y){
    azuriraj_mis(x,y,0);
}

void meni_klik(int klik,int stanje,int x,int y){
    if(stanje==GLUT_DOWN && klik==GLUT_LEFT_BUTTON){
        azuriraj_mis(x,y,1);
    }
    if(stanje==GLUT_UP && klik==GLUT_LEFT_BUTTON){

        azuriraj_mis(x,y,0);
    }
}
void meni_render(){
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(55/256.0f,54/256.0f,56/256.0f,1);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,1920,0,1080);
    glMatrixMode(GL_MODELVIEW);
    glColor3f(1,0,0);
    glDisable(GL_DEPTH_TEST);
    frejm(710,100,400,800);
    if(dugme("Igraj",730,790,360,50)){
        neprijatelji.clear();
        nivo_granate.clear();
        glutSetCursor(GLUT_CURSOR_NONE);
        delete(tekuci_nivo);
        tekuci_nivo=tekuci_nivo->ucitaj_teren("1.nivo");
        delete(tekuci_igrac);
        for(int i=0;i<tekuci_nivo->n;i++)
        for(int j=0;j<tekuci_nivo->m;j++){
            if(tekuci_nivo->teren[i][j]->daj_tip()==Ig){
                tekuci_igrac=new Igrac();
                tekuci_igrac->x=tekuci_nivo->teren[i][j]->temena[1][1].first.first;
                tekuci_igrac->z=tekuci_nivo->teren[i][j]->temena[1][1].first.second;
                tekuci_nivo->teren[i][j]->postavi_tip(ZEMLJA);
            }
            if(tekuci_nivo->teren[i][j]->daj_tip()==Nep){
                neprijatelji.push_back(new Neprijatelj(tekuci_nivo->teren[i][j]->temena[0][0].first.first,tekuci_nivo->teren[i][j]->temena[0][0].first.second));
                tekuci_nivo->teren[i][j]->postavi_tip(ZEMLJA);
            }
        }
        glutPassiveMotionFunc(mis_igra);
        glutKeyboardFunc(igra_tastatura);
        glutMouseFunc(klik);
        glutKeyboardUpFunc(keyup);
        glutDisplayFunc(igra_render);
    }
    if(dugme("Napravi nivo",730,730,360,50)){
        tekuci_nivo=new Nivo(32,32);
        glutKeyboardFunc(tastatura_editor);
        glutMouseFunc(mis);
        glutMotionFunc(mis_pomera);
        glutDisplayFunc(render_func_editor);

    }
    if(dugme("Izmeni nivo",730,670,360,50)){
        delete(tekuci_nivo);
        tekuci_nivo=tekuci_nivo->ucitaj_teren("1.nivo");
        glutKeyboardFunc(tastatura_editor);
        glutMouseFunc(mis);
        glutMotionFunc(mis_pomera);
        glutDisplayFunc(render_func_editor);
    }
    if(dugme("Izadji :'(",730,120,360,50)){
        exit(0);
    }
    glEnable(GL_DEPTH_TEST);
    glutSwapBuffers();
    glutPostRedisplay();
    glFlush();
    
}


void pauza_render(){

        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glClearColor(55/256.0f,54/256.0f,56/256.0f,1);
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0,1920,0,1080);
        glMatrixMode(GL_MODELVIEW);
        glDisable(GL_DEPTH_TEST);
        frejm(710,100,400,800);
        if(dugme("nastavi",735,830,350,50)){
            glutPassiveMotionFunc(mis_igra);
            glutKeyboardFunc(igra_tastatura);
            glutMouseFunc(klik);
            glutKeyboardUpFunc(keyup);
            glutDisplayFunc(igra_render);
        }
        if(dugme("nazad u meni",735,210,350,50)){
            glutKeyboardFunc(meni_tastatura);
            glutPassiveMotionFunc(meni_mis);
            glutMouseFunc(meni_klik);
            glutDisplayFunc(meni_render);
        }
        if(dugme("izadji",735,130,350,50)){
            exit(0);
        }

         glutSwapBuffers();
        glutPostRedisplay();
        glFlush();
}

void pauza_klik(int klik,int stanje,int x,int y){
    if(klik==GLUT_LEFT_BUTTON && stanje==GLUT_DOWN){
        azuriraj_mis(x,y,1);
    }
}

void mis_pauza(int x,int y){
    
    azuriraj_mis(x,y,0);
}

void pauza_tastatura(unsigned char taster, int x, int y){
    keys[taster]=true;
    
}

void pauza_keyup(unsigned char key,int x,int y){
    if(keys[27]==true && key==27){
        keys[key]=false;
        glutPassiveMotionFunc(mis_igra);
            glutKeyboardFunc(igra_tastatura);
            glutMouseFunc(klik);
            glutKeyboardUpFunc(keyup);
            glutDisplayFunc(igra_render);
    }
    keys[key]=false;
}

int main(int argc,char *argv[]){
    glutInit(&argc,argv);
    glutInitWindowSize(1920,1080);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH|GLUT_DOUBLE);
    glutCreateWindow("Tenkici");
    glutFullScreen();
    init_GL();
    glutIgnoreKeyRepeat(0);
    glutReshapeFunc(azuriraj_dimenzije);
    glutKeyboardFunc(meni_tastatura);
    glutPassiveMotionFunc(meni_mis);
    glutMouseFunc(meni_klik);
    trava_slika=ucitaj_sliku("../resorsi/texture/trava.bmp");
    zid_slika=ucitaj_sliku("../resorsi/texture/wall.bmp");
    voda_slika=ucitaj_sliku("../resorsi/texture/voda.bmp");
    drvo_slika=ucitaj_sliku("../resorsi/texture/drvo.bmp");
    glutDisplayFunc(meni_render);
    glutMainLoop();
    return 0;
}