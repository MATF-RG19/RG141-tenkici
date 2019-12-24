#include "Neprijatelj.h"
Model nep_model;

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
    glTranslatef(x,0.3,z);
    glRotatef(angle,0,1,0);
    glScalef(0.6,0.6,0.6);
    crtaj_objekat(nep_model.objekti[1]);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(x,0.3,z);
    glRotatef(angle_up,0,1,0);
    glScalef(0.6,0.6,0.6);
    crtaj_objekat(nep_model.objekti[0]);
    glPopMatrix();
}

void Neprijatelj::crtaj_mrtvog(){
    glLineWidth(2);
    glPushMatrix();
    glTranslatef(x,0.3,z);
    glRotatef(angle,0,1,0);
    glScalef(0.6,0.6,0.6);
    crtaj_objekat(nep_model.objekti[1]);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(x,0.3,z);
    glRotatef(angle_up,0,1,0.2);
    glScalef(0.6,0.6,0.6);
    crtaj_objekat(nep_model.objekti[0]);
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
//Radi bfs ka cilju , ako je igrac tu takodje rotira gornji deo i puca ako je rotiran dovoljno
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