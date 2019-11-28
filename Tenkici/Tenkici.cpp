#include<GL/glut.h>
#include<GL/gl.h>
#include "Nivo.h"

float cam_pos_x=0;
float cam_pos_y=-10;
float cam_pos_z=0;
float cam_f_y=1;

static Nivo *tekuci_nivo;

static int select_nivo=1;
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

pair<int,int> pocetak=make_pair(-1,-1);
pair<int,int> cilj=make_pair(-1,-1);

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
void tastatura(unsigned char taster, int x, int y){
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
}


void init_GL(){
    tekuci_nivo=new Nivo(32,32);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(90.0,1920.0/1080.0,0.1,250.0);
    glMatrixMode(GL_MODELVIEW);
    
}


void render_func(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
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
        glColor3f(0.4,0.1,0.5);
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
    glutSwapBuffers();
    glutPostRedisplay();
    glFlush();
}



int main(int argc,char *argv[]){
    glutInit(&argc,argv);
    glutInitWindowSize(1920,1080);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutCreateWindow("Tenkici");
    glutKeyboardFunc(tastatura);
    glutMouseFunc(mis);
    glutMotionFunc(mis_pomera);
    glutDisplayFunc(render_func);
    init_GL();
    glutMainLoop();
    return 0;
}