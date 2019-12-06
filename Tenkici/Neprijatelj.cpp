#include "Neprijatelj.h"


Neprijatelj::Neprijatelj(float x,float z){
    this->x=x;
    this->z=z;
}

float dis(float x,float y,float x_,float y_){
    return sqrt((x-x_)*(x-x_)+(y_-y)*(y_-y));
}

void Neprijatelj::crtaj(){
    glLineWidth(2);
    glPushMatrix();
    glTranslatef(x,0,z);
    glRotatef(angle,0,1,0);
    glColor3f(0.3,0.1,0.4);
    glutSolidCube(0.8);
    glColor3f(0,0,0);
    glutWireCube(0.8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(x,0.5,z);
    glRotatef(angle_up,0,1,0);
    glColor3f(0.3,0.1,0.4);
    glutSolidCube(0.5);
    glutSolidCylinder(0.1,0.8,10,10);
    glColor3f(0,0,0);
    glutWireCube(0.5);
    glutWireCylinder(0.1,0.8,10,10);
    glPopMatrix();
}

void Neprijatelj::crtaj_mrtvog(){
    glLineWidth(2);
    glPushMatrix();
    glTranslatef(x,0,z);
    glRotatef(angle,0,1,0);
    glColor3f(0.1,0.1,0.1);
    glutSolidCube(0.8);
    glColor3f(0,0,0);
    glutWireCube(0.8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(x,0.5,z);
    glRotatef(angle_up,0,1,0.2);
    glColor3f(0.1,0.1,0.1);
    glutSolidCube(0.5);
    glutSolidCylinder(0.1,0.8,10,10);
    glColor3f(0,0,0);
    glutWireCube(0.5);
    glutWireCylinder(0.1,0.8,10,10);
    glPopMatrix();
}

bool rotiraj_ka_tacki(float &ang,float px,float pz,float cx,float cz){
    float ang2=(atan2(cx-px,cz-pz)*180/3.14);
    if(abs(ang2-ang)<4){
        ang=ang2;
        return true;
    }
    if(ang2>ang)
        ang+=1;
    else ang-=1;
    return false;
}

void pomeri_ka_tacki(float &px,float &pz,float cx,float cz){
    float tx=cx-px;
    float tz=cz-pz;
    float norm=sqrt(tx*tx+tz*tz);
    px+=(tx/norm)*0.05;
    pz+=(tz/norm)*0.05;
}

void Neprijatelj::radi_nesto(Nivo *nivo,pair<float,float> igrac){
    if(sec<brzina_napada)
        sec++;
    if(put.empty()){
       
        int i=rand()%nivo->n;
        int j=rand()%nivo->m;
        vector<pair<float,float>> p=nivo->bfs(nivo->vrati_indexe_od_koord(x,z),make_pair(i,j));
        for(int l=p.size()-1;l>=0;l--)
            put.push(p[l]);
    }
    if(dis(x,z,put.front().first,put.front().second)<0.05)
        put.pop();
    else if(put.empty()==false){
        if(rotiraj_ka_tacki(angle,x,z,put.front().first,put.front().second))
        pomeri_ka_tacki(x,z,put.front().first,put.front().second);
        if(dis(igrac.first,igrac.second,x,z)<15){
            if(rotiraj_ka_tacki(angle_up,x,z,igrac.first,igrac.second)){
                if(sec==brzina_napada){
                float tx=igrac.first-x;
                float tz=igrac.second-z;
                float norm=sqrt(tx*tx+tz*tz);
                tx/=norm;
                tz/=norm;
                nivo_granate.push_back(make_unique<Metak>(x+tx,z+tz,tx,tz));
                nivo_granate.back()->nas_metak=false;
                sec=0;
                }
               
            }
        }
        else rotiraj_ka_tacki(angle_up,x,z,put.front().first,put.front().second);
    }
    x+=vx;
    z+=vz;
}