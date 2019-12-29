#include "Nivo.h"

 unsigned int trava_slika;
 unsigned int zid_slika;
 unsigned int drvo_slika;
 unsigned int voda_slika;
 unsigned int trava_text;
 unsigned int voda_text;

Model drvo_model;
Model zid_model;

bool prikazi_cvorove=false;
Model igrac_tenk;

vector<unique_ptr<Metak>> nivo_granate;

float udaljenost(float x,float y,float x_,float y_);
pair<int,int> tek_igrac=make_pair(-1,-1);
Plocica::Plocica(float x,float z){
    hodljiv=true;
    tip=ZEMLJA;
    float x_it=x;
    float z_it=z;
    for(int i=0;i<3;i++){
        x_it=x;
    for(int j=0;j<3;j++){
        temena[i][j]=make_pair(make_pair(x_it,z_it),true);
        x_it+=0.5f;
        }
        z_it-=0.5f;
    }
}


bool Plocica::jel_hodljiv(){
    return hodljiv;
}

void Plocica::postavi(int x,int y,bool vrednost){
    temena[x][y].second=vrednost;
}

//FUNKCIJA KOJA CRTA PLOCICE I DATE TACKE ZA KRETANJE U SKLADU SA TIPOM PLOCICE
void Plocica::crtaj(){
    if(tip==ZEMLJA){
        glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,trava_slika);
    }
    if(tip==ZID){
        glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,zid_slika);
    }
    if(tip==VODA){
        glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,voda_slika);
    }
    if(tip==DRVO){
        glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,drvo_slika);
    }
    if(tip==Ig)
    glColor3f(0.3,0.38,0.8);
    if(tip==Nep)
    glColor3f(1,0,0);
    glBegin(GL_QUADS);
    glTexCoord2f(0,1);
    glVertex3f(temena[0][0].first.first,0,temena[0][0].first.second);
    glTexCoord2f(1,1);
    glVertex3f(temena[0][2].first.first,0,temena[0][2].first.second);
    glTexCoord2f(1,0);
    glVertex3f(temena[2][2].first.first,0,temena[2][2].first.second);
    glTexCoord2f(0,0);
    glVertex3f(temena[2][0].first.first,0,temena[2][0].first.second);
    glEnd();
    if(hodljiv && prikazi_cvorove ){
        for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
            glPointSize(5);
            glColor3f(1,0,0.76);
            glBegin(GL_POINTS);
            if(temena[i][j].second)
            glVertex3f(temena[i][j].first.first,0,temena[i][j].first.second);
            glEnd();
        }
    }
    glBindTexture(GL_TEXTURE_2D,0);
}
//postavljanja plocice na neki tip
void Plocica::postavi_tip(int tip){
    if(this->tip==6 && tip!=6)
        tek_igrac=make_pair(-1,-1);
    this->tip=tip;
    if(tip!=ZEMLJA && tip!=Ig && tip!=Nep)
    this->hodljiv=false;
    else {
        for(int l=0;l<=2;l++)
        for(int d=0;d<=2;d++)
        temena[l][d].second=true;
        hodljiv=true;
    }
}

int Plocica::daj_tip(){
    return this->tip;
}

Nivo::Nivo(int n,int m){
    this->n=n;
    this->m=m;
    teren.resize(n);
    for(int i=0;i<n;i++)
    teren[i].resize(m);

    float pocetak_x=-(float)n/2;
    float pocetak_z=(float)m/2;

    for(int i=0;i<n;i++){
        pocetak_x=-(float)n/2;
    for(int j=0;j<m;j++){
        teren[i][j]=new Plocica(pocetak_x,pocetak_z);
        pocetak_x+=1.0f;
        }
        pocetak_z-=1.0f;
    }
}

Nivo::~Nivo(){
    for(int i=0;i<n;i++)
    for(int j=0;j<m;j++)
    delete(teren[i][j]);

    for(int i=0;i<n;i++)
    teren[i].clear();
    teren.clear();


}

void Nivo::crtaj_teren(){
    glColor3f(1,0,0);
    for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
    teren[i][j]->crtaj();
}
//FUNKCIJA ZA ODABIR PLOCICE U ODNOSU NA PRESECNE TACKE MISA I TERENA
void Nivo::izaberi_plocicu(float x,float z,int n2,int tip){
    int x_loc=floor(x)+n/2;
    int z_loc=abs(floor(z)-m/2);

    int pocetak_z=z_loc-1-n2/2;
    int kraj_z=z_loc-1+n2/2;

    int pocetak_x=x_loc-n2/2;
    int kraj_x=x_loc+n2/2;

//za pronadjednu plocicu i datu sirina obelezava sve plocice oko nje
    for(int i=pocetak_z;i<=kraj_z;i++)
    for(int j=pocetak_x;j<=kraj_x;j++)
    if(i>=0 && i<m && j>=0 &&  j<n){
        if(tip==Ig && tek_igrac==make_pair(-1,-1)){
            tek_igrac=make_pair(i,j);
        }
        else if(tek_igrac!=make_pair(-1,-1) && tip==Ig){
            teren[tek_igrac.first][tek_igrac.second]->postavi_tip(ZEMLJA);
            tek_igrac=make_pair(i,j);
        }
         teren[i][j]->postavi_tip(tip);
    }
}

//FUNKCIJA KOJA RACUNA ZA SVAKU PLOCICU TERENA KUDA JE MOGUCE HODATI
void Nivo::procesuj(){
//za svaku plocicu proverava 8 plocica oko nje i postavlja vrednosti odgovarajuce vrednosti
    for(int i =0;i<n;i++)
    for(int j=0;j<m;j++)
    {

        if(i+1<n && j+1<m){
            if(teren[i+1][j+1]->jel_hodljiv()==false){
                teren[i][j]->postavi(2,2,false);
            }
        }

        if(i-1>=0 && j-1>=0){
            if(teren[i-1][j-1]->jel_hodljiv()==false){
                teren[i][j]->postavi(0,0,false);
            }
        }

        if(i-1>=0 && j+1<m){
            if(teren[i-1][j+1]->jel_hodljiv()==false){
                teren[i][j]->postavi(0,2,false);
            }
        }

        if(i+1<n && j-1>=0){
            if(teren[i+1][j-1]->jel_hodljiv()==false){
                teren[i][j]->postavi(2,0,false);
            }
        }

        if(i-1>=0){
            if(teren[i-1][j]->jel_hodljiv()==false){
                teren[i][j]->postavi(0,0,false);
                teren[i][j]->postavi(0,1,false);
                teren[i][j]->postavi(0,2,false);
            }
        } else {
                teren[i][j]->postavi(0,0,false);
                teren[i][j]->postavi(0,1,false);
                teren[i][j]->postavi(0,2,false);
        }
        if(i+1<n){
            if(teren[i+1][j]->jel_hodljiv()==false){
                teren[i][j]->postavi(2,0,false);
                teren[i][j]->postavi(2,1,false);
                teren[i][j]->postavi(2,2,false);
            }
        } else {
            teren[i][j]->postavi(2,0,false);
                teren[i][j]->postavi(2,1,false);
                teren[i][j]->postavi(2,2,false);
        }
        if(j-1>=0){
            if(teren[i][j-1]->jel_hodljiv()==false){
                teren[i][j]->postavi(0,0,false);
                teren[i][j]->postavi(1,0,false);
                teren[i][j]->postavi(2,0,false);
            }
        } else {
            teren[i][j]->postavi(0,0,false);
                teren[i][j]->postavi(1,0,false);
                teren[i][j]->postavi(2,0,false);
        }
        if(j+1<m){
            if(teren[i][j+1]->jel_hodljiv()==false){
                teren[i][j]->postavi(0,2,false);
                teren[i][j]->postavi(1,2,false);
                teren[i][j]->postavi(2,2,false);
            }
        } else {
                teren[i][j]->postavi(0,2,false);
                teren[i][j]->postavi(1,2,false);
                teren[i][j]->postavi(2,2,false);
        }
    }
}
//cuvamo teren u fajl
void Nivo::sacuvaj_teren(){
    ofstream pisac;
    pisac.open("1.nivo");
    pisac<<"n="<<n<<" m="<<m<<endl;
    for(int i=0;i<n;i++)
    for(int j=0;j<m;j++)
    pisac<<"tip="<<teren[i][j]->daj_tip()<<endl;
    pisac.close();
}
//citamo teren iz tog fajla
Nivo* Nivo::ucitaj_teren(string path){
    ifstream citac;
    citac.open(path);
    Nivo *tekuci;
    if(citac.is_open()){
        string linija;
        getline(citac,linija);
        int n1,m1;
        sscanf(linija.c_str(),"n=%d m=%d",&n1,&m1);
        tekuci=new Nivo(n1,m1);
        for(int i=0;i<n1;i++)
        for(int j=0;j<m1;j++){
            getline(citac,linija);
            int tip;
            sscanf(linija.c_str(),"tip=%d",&tip);
            if(tip==Ig)
            tek_igrac=make_pair(i,j);
            tekuci->teren[i][j]->postavi_tip(tip);
            }
        }

    citac.close();
    return tekuci;
}

void Nivo::prikazi_tacke(bool vr){
    prikazi_cvorove=vr;
}

bool Nivo::nabavi_prikaz_tacke(){
    return prikazi_cvorove;
}


//FUNKCIJA ZA TRAZENJE PUTA U OBRADJENOJ MREZI
vector<pair<float,float>> Nivo::bfs(pair<int,int> lok,pair<int,int> cilj){
    vector<pair<float,float>> put;
    vector<vector<pair<int,int>>> roditelj(n);
    vector<vector<bool>> zauzet(n);
    bool naso=false;
    for(int i=0;i<n;i++){
        roditelj[i].resize(m);
        zauzet[i].resize(m,false);
    }
    roditelj[lok.first][lok.second]=lok;
    queue<pair<int,int>> red;
    red.push(lok);
    while(red.empty()==false){
        pair<int,int> vrh=red.front();
        red.pop();
        if(vrh==cilj){
            naso=true;
            break;
        }

        int i=vrh.first;
        int j=vrh.second;

        //provera susednih cvorova
        if(i+1<n && zauzet[i+1][j]==false && teren[i+1][j]->jel_hodljiv()){
            zauzet[i+1][j]=true;
            roditelj[i+1][j]=make_pair(i,j);
            red.push(make_pair(i+1,j));
        }
        if(i-1>=0 && zauzet[i-1][j]==false && teren[i-1][j]->jel_hodljiv()){
            zauzet[i-1][j]=true;
            roditelj[i-1][j]=make_pair(i,j);
            red.push(make_pair(i-1,j));
        }
        if(j+1<m && zauzet[i][j+1]==false && teren[i][j+1]->jel_hodljiv()){
            zauzet[i][j+1]=true;
            roditelj[i][j+1]=make_pair(i,j);
            red.push(make_pair(i,j+1));
        }
        if(j-1>=0 && zauzet[i][j-1]==false && teren[i][j-1]->jel_hodljiv()){
            zauzet[i][j-1]=true;
            roditelj[i][j-1]=make_pair(i,j);
            red.push(make_pair(i,j-1));
        }

        if(i+1<n && j+1<m && zauzet[i+1][j+1]==false && teren[i+1][j+1]->jel_hodljiv())
        if(teren[i+1][j]->jel_hodljiv() && teren[i][j+1]->jel_hodljiv())
        {
            zauzet[i+1][j+1]=true;
            roditelj[i+1][j+1]=make_pair(i,j);
            red.push(make_pair(i+1,j+1));
        }

        if(i+1<n && j-1>=0 && zauzet[i+1][j-1]==false && teren[i+1][j-1]->jel_hodljiv())
        if(teren[i+1][j]->jel_hodljiv() && teren[i][j-1]->jel_hodljiv())
        {
            zauzet[i+1][j-1]=true;
            roditelj[i+1][j-1]=make_pair(i,j);
            red.push(make_pair(i+1,j-1));
        }

        if(i-1>=0 && j+1<m && zauzet[i-1][j+1]==false && teren[i-1][j+1]->jel_hodljiv())
        if(teren[i-1][j]->jel_hodljiv() && teren[i][j+1]->jel_hodljiv())
        {
            zauzet[i-1][j+1]=true;
            roditelj[i-1][j+1]=make_pair(i,j);
            red.push(make_pair(i-1,j+1));
        }

        if(i-1>=0 && j-1>=0 && zauzet[i-1][j-1]==false && teren[i-1][j-1]->jel_hodljiv())
        if(teren[i-1][j]->jel_hodljiv() && teren[i][j-1]->jel_hodljiv())
        {
            zauzet[i-1][j-1]=true;
            roditelj[i-1][j-1]=make_pair(i,j);
            red.push(make_pair(i-1,j-1));
        }

    }
    if(naso)
    while(cilj!=lok){
        put.push_back(teren[cilj.first][cilj.second]->temena[1][1].first);
        cilj=roditelj[cilj.first][cilj.second];
    }
    put.push_back(teren[lok.first][lok.second]->temena[1][1].first);
    if(put.empty())
        cout<<"NEMA PUTA"<<endl;
    return put;
}
//od float x z dobijamo indexe i j koji odgovaraju matrici 
pair<int,int> Nivo::vrati_indexe_od_koord(float x,float z){
    int x_loc=floor(x)+n/2;
    int z_loc=(abs(floor(z)-m/2))-1;

    if(x_loc>=0 && x_loc<n && z_loc>=0 && z_loc<m)
        return make_pair(z_loc,x_loc);
    return make_pair(-1,-1);
}

 Plocica* Nivo::izaberi_plocicu(float i,float j){
     return teren[i][j];
 }
 //funkcija za crtanje tokom igre
void Plocica::crtaj_igra(){
    if(tip==ZEMLJA || tip==5 || tip==6){
    glColor3f(1,1,1);
    //ako je plocica trava samo uzimamo tu teksturu
    glBindTexture(GL_TEXTURE_2D,trava_text);
    }
    if(tip==ZID){
        //ako je plocica zid onda crtamo model zida
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(temena[1][1].first.first,0,temena[1][1].first.second);
    glScalef(0.5,0.5,0.5);
    crtaj_model(zid_model);
    glPopMatrix();
    }
    if(tip==VODA){
    glColor3f(1,1,1);
    //ako je plocica vod samo uzimamo tu teksturu
    glBindTexture(GL_TEXTURE_2D,voda_text);
    }
    if(tip==DRVO){
        //ako je plocica drvo crtamo model drveta
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(temena[1][1].first.first,0,temena[1][1].first.second);
    glScalef(3,3,3);
    crtaj_model(drvo_model);
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D,trava_text);
    }
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glTexCoord2f(0,1);
    glVertex3f(temena[0][0].first.first,0,temena[0][0].first.second);
    glNormal3f(0,1,0);
    glTexCoord2f(1,1);
    glVertex3f(temena[0][2].first.first,0,temena[0][2].first.second);
    glNormal3f(0,1,0);
    glTexCoord2f(1,0);
    glVertex3f(temena[2][2].first.first,0,temena[2][2].first.second);
    glNormal3f(0,1,0);
    glTexCoord2f(0,0);
    glVertex3f(temena[2][0].first.first,0,temena[2][0].first.second);
    glEnd();
    glBindTexture(GL_TEXTURE_2D,0);
}

 void Nivo::crtaj_teren_igra(){
    for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
    teren[i][j]->crtaj_igra();
 }

float udaljenost(float x,float y,float x_,float y_){
    return sqrt((x-x_)*(x-x_)+(y_-y)*(y_-y));
}

//gleda cvorove unutar suseda jednog indeksa za koliziju preko sfera
//koriscenjem distance proverava da li je kolidiralo ili ne
bool Nivo::proveri_koliziju(float x,float z){
    pair<int,int> tek_koord=vrati_indexe_od_koord(x,z);
    if(tek_koord==make_pair(-1,-1))
        return false;
    for(int i=tek_koord.first-1;i<=tek_koord.first+1;i++)
    for(int j=tek_koord.second-1;j<=tek_koord.second+1;j++){
        if(i>=0 && i<n && j>=0 && j<m){
            if(udaljenost(x,z,teren[i][j]->temena[0][0].first.first,
            teren[i][j]->temena[0][0].first.second)<0.3 && teren[i][j]->jel_hodljiv()==false)
                return false;
            if(udaljenost(x,z,teren[i][j]->temena[0][2].first.first,
            teren[i][j]->temena[0][2].first.second)<0.3 && teren[i][j]->jel_hodljiv()==false)
                return false;
            if(udaljenost(x,z,teren[i][j]->temena[2][0].first.first,
            teren[i][j]->temena[2][0].first.second)<0.3 && teren[i][j]->jel_hodljiv()==false)
                return false;
            if(udaljenost(x,z,teren[i][j]->temena[2][2].first.first,
            teren[i][j]->temena[2][2].first.second)<0.3 && teren[i][j]->jel_hodljiv()==false)
                return false;
            if(udaljenost(x,z,teren[i][j]->temena[1][1].first.first,
            teren[i][j]->temena[1][1].first.second)<0.5 && teren[i][j]->jel_hodljiv()==false)
                return false;
        }
    }
    return true;
}
//provera kolizije za metak moze se dodati da proverava malo vise vrednosti od centra plocice radi realnosti ali i ovo je
//zadovoljavajuce
bool Nivo::proveri_koliziju_metak(float x,float z){
    pair<int,int> tek_koord=vrati_indexe_od_koord(x,z);
    if(tek_koord==make_pair(-1,-1))
        return false;
    for(int i=tek_koord.first-1;i<=tek_koord.first+1;i++)
    for(int j=tek_koord.second-1;j<=tek_koord.second+1;j++){
        if(i>=0 && i<n && j>=0 && j<m){
            if(udaljenost(x,z,teren[i][j]->temena[1][1].first.first,
            teren[i][j]->temena[1][1].first.second)<0.5 && (teren[i][j]->jel_hodljiv()==false && teren[i][j]->daj_tip()!=VODA))
                return false;
        }
    }
    return true;
}