#include "gui.h"

int m_x;
int m_y;
int m_click;
int p_visina;
int p_sirina;

bool provera(int x,int y,int sirina,int visina){
    return (m_x<=x+sirina && m_x>=x) && (m_y<=y+visina && m_y>=y); 
}

void azuriraj_mis(int x,int y,int click){
    m_x=x;
    m_y=p_visina-y;
    m_click=click;
}
void reset(){
    m_click=0;
}

void azuriraj_dimenzije(int sirina,int visina){
    cout<<sirina<<endl;
    p_sirina=sirina;
    p_visina=visina;
}

bool dugme(string text,int x,int y,int sirina,int visina){
    if(provera(x,y,sirina,visina)){
        glColor3ub(47,46,48);
        glBegin(GL_QUADS);
        glVertex2f(x,y);
        glVertex2f(x+sirina,y);
        glVertex2f(x+sirina,y+visina);
        glVertex2f(x,y+visina);
        glEnd();
        glColor3f(0,0,0);
        glBegin(GL_LINE_STRIP);
        glVertex2f(x,y);
        glVertex2f(x+sirina,y);
        glVertex2f(x+sirina,y+visina);
        glVertex2f(x,y+visina);
        glVertex2f(x,y);
        glEnd();
        if(m_click)
        glColor3ub(184,0,0);
        else
        glColor3ub(204,102,0);

        float y_pos=(visina-24)/2+6;
        float x_pos=(sirina-24*text.size())/2+text.size()*6;
        glRasterPos2f(x+x_pos,y+y_pos);
    for(auto it=text.begin();it!=text.end();it++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*it);
        if(m_click==1){
            m_click=0;
            return true;
        }
    }
    else {
        glColor3ub(40,37,38);
        glBegin(GL_QUADS);
        glVertex2f(x,y);
        glVertex2f(x+sirina,y);
        glVertex2f(x+sirina,y+visina);
        glVertex2f(x,y+visina);
        glEnd();
        glColor3f(0,0,0);
        glBegin(GL_LINE_STRIP);
        glVertex2f(x,y);
        glVertex2f(x+sirina,y);
        glVertex2f(x+sirina,y+visina);
        glVertex2f(x,y+visina);
        glVertex2f(x,y);
        glEnd();
        glColor3ub(200,201,199);

        float y_pos=(visina-24)/2+6;
        float x_pos=(sirina-24*text.size())/2+text.size()*6;
        glRasterPos2f(x+x_pos,y+y_pos);
    for(auto it=text.begin();it!=text.end();it++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*it);
    }

        
    return false;
}

void frejm(int x,int y,int sirina,int visina){
    glColor3ub(44,41,42);
    glBegin(GL_QUADS);
    glVertex2f(x,y);
    glVertex2f(x+sirina,y);
    glVertex2f(x+sirina,y+visina);
    glVertex2f(x,y+visina);
    glEnd();
    glColor3f(0,0,0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(x,y);
    glVertex2f(x+sirina,y);
    glVertex2f(x+sirina,y+visina);
    glVertex2f(x,y+visina);
    glVertex2f(x,y);
    glEnd();
}

bool dugme_slika(unsigned int slika,int x,int y,int sirina,int visina){
    
    glBindTexture(GL_TEXTURE_2D,slika);
    if(provera(x,y,sirina,visina)){
        glColor3f(1,1,1);
        glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex2f(x,y);
        glTexCoord2f(1,0);
        glVertex2f(x+sirina,y);
        glTexCoord2f(1,1);
        glVertex2f(x+sirina,y+visina);
        glTexCoord2f(0,1);
        glVertex2f(x,y+visina);
        glEnd();
        glColor3f(0,0,0);
        glBegin(GL_LINE_STRIP);
        glVertex2f(x,y);
        glVertex2f(x+sirina,y);
        glVertex2f(x+sirina,y+visina);
        glVertex2f(x,y+visina);
        glVertex2f(x,y);
        glEnd();
        if(m_click==1){
            m_click=0;
            return true;
        }
    }
    else {
        glColor3f(1,1,1);
        glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex2f(x,y);
        glTexCoord2f(1,0);
        glVertex2f(x+sirina,y);
        glTexCoord2f(1,1);
        glVertex2f(x+sirina,y+visina);
        glTexCoord2f(0,1);
        glVertex2f(x,y+visina);
        glEnd();
        glColor3f(0,0,0);
        glBegin(GL_LINE_STRIP);
        glVertex2f(x,y);
        glVertex2f(x+sirina,y);
        glVertex2f(x+sirina,y+visina);
        glVertex2f(x,y+visina);
        glVertex2f(x,y);
        glEnd();
    }
    glBindTexture(GL_TEXTURE_2D,0);
    return false;
}

bool dugme_manji(string text,int x,int y,int sirina,int visina){
    if(provera(x,y,sirina,visina)){
        glColor3ub(47,46,48);
        glBegin(GL_QUADS);
        glVertex2f(x,y);
        glVertex2f(x+sirina,y);
        glVertex2f(x+sirina,y+visina);
        glVertex2f(x,y+visina);
        glEnd();
        glColor3f(0,0,0);
        glBegin(GL_LINE_STRIP);
        glVertex2f(x,y);
        glVertex2f(x+sirina,y);
        glVertex2f(x+sirina,y+visina);
        glVertex2f(x,y+visina);
        glVertex2f(x,y);
        glEnd();
        if(m_click)
        glColor3ub(184,0,0);
        else
        glColor3ub(204,102,0);
        if(m_click==1){
            m_click=0;
            return true;
        }
    }
    else {
        glColor3ub(40,37,38);
        glBegin(GL_QUADS);
        glVertex2f(x,y);
        glVertex2f(x+sirina,y);
        glVertex2f(x+sirina,y+visina);
        glVertex2f(x,y+visina);
        glEnd();
        glColor3f(0,0,0);
        glBegin(GL_LINE_STRIP);
        glVertex2f(x,y);
        glVertex2f(x+sirina,y);
        glVertex2f(x+sirina,y+visina);
        glVertex2f(x,y+visina);
        glVertex2f(x,y);
        glEnd();
        glColor3ub(200,201,199);
    }

        float y_pos=(visina-18)/2+4;
        float x_pos=(sirina-18*text.size())/2+text.size()*4;
        glRasterPos2f(x+x_pos,y+y_pos);
    for(auto it=text.begin();it!=text.end();it++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*it);
    return false;
}

void label(string text,int x,int y,int sirina,int visina){

        glColor3ub(40,37,38);
        glBegin(GL_QUADS);
        glVertex2f(x,y);
        glVertex2f(x+sirina,y);
        glVertex2f(x+sirina,y+visina);
        glVertex2f(x,y+visina);
        glEnd();
        glColor3f(0,0,0);
        glBegin(GL_LINE_STRIP);
        glVertex2f(x,y);
        glVertex2f(x+sirina,y);
        glVertex2f(x+sirina,y+visina);
        glVertex2f(x,y+visina);
        glVertex2f(x,y);
        glEnd();
        glColor3ub(200,201,199);

        float y_pos=(visina-24)/2+6;
        float x_pos=(sirina-24*text.size())/2+text.size()*6;
        glRasterPos2f(x+x_pos,y+y_pos);
    for(auto it=text.begin();it!=text.end();it++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*it);
    
}

void helt_bar(int x,int y,int sirina,int visina,int max_x,int tek){
    glColor3f(1,0,0);
    float odnos=(float)tek/max_x;
    glBegin(GL_QUADS);
    glVertex2f(x,y);
    glVertex2f(x+sirina*odnos,y);
    glVertex2f(x+sirina*odnos,y+visina);
    glVertex2f(x,y+visina);
    glEnd();

    glColor3ub(40,37,38);
    glBegin(GL_QUADS);
    glVertex2f(x+sirina*odnos,y);
    glVertex2f(x+sirina,y);
    glVertex2f(x+sirina,y+visina);
    glVertex2f(x+sirina*odnos,y+visina);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(x,y);
    glVertex2f(x+sirina*odnos,y);
    glVertex2f(x+sirina*odnos,y+visina);
    glVertex2f(x,y+visina);
    glVertex2f(x,y);
    glEnd();

    string txt=to_string(tek) + "/" + to_string(max_x);
    float x_pos=(sirina-18*txt.size())/2+txt.size()*4;
    float y_pos=(visina-18)/2+4;
    glRasterPos2f(x+x_pos,y+y_pos);
    for(auto it=txt.begin();it!=txt.end();it++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*it);
}