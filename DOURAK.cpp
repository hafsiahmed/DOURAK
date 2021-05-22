#include <stack>//pile
#include <vector>//tableau dynamique
#include <cstdlib> //srand, randy
#include <ctime>   // time
#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;
class Joueur ;
class Carte ;
class Bioche;
class Partie
{
private:
    vector<Carte> tab;
    vector<Partie>::iterator pos; // un vector contenat les cartes sur table
public:
    vector<Carte> getTab();
    void fail(); // methode qui prend les elements sur la tables el les vide
    void fail(Joueur&);//methode qui prend les cartes sur table et les ajoute aux carte joueurs
    void ajouter (Carte&) ;//pour ajouter une carte � la fin du vector /:friend avec classe carte
    int longueur(); //retourne le size du vector
friend void one_gain(Joueur&, Partie& , Carte );
friend void gain(vector<Joueur*>, Joueur*  , Partie  );
friend void deffensing_process(bool&,Joueur*,Partie& ,string );
friend void attacking_process(bool&,Joueur*,Partie&);
friend void affichage(Partie);
friend void one_vs_one(bool&,vector<Joueur*>&,string,Partie&,Joueur*,vector<Joueur*>);
friend void tour_de_table(bool&,int,vector<Joueur*>&,vector<Joueur*>&,string,Partie&,Joueur*,Bioche&);
};
class Bioche
{
private:
    vector <Carte> PileBioche ;//pile des cartes


public:
    Bioche(vector <Carte>);
    void Distribuer(Joueur&);
    ~Bioche();
    void Distribuer1(Joueur&);
    void Distribuer2(Joueur*);
    int nbre_des_cartes();
    Carte getDernierCarte();
};
class Carte
{
protected:
    string symbole;
    int  Numero;
public:

    Carte(int,string);
    Carte (const Carte&);
    ~Carte();
    string GetSymbole() ;
    int GetNumero() ;
    void setSymbole(string);
    void setNumero(int);
    //surcharge de l'opperateur egale .
    bool operator ==(Carte);
    bool operator !=(Carte);;
friend void Partie :: ajouter(Carte&);
friend Carte Bioche :: getDernierCarte();
friend void one_gain(vector<Joueur*> ,Joueur*, Partie , Carte );
friend bool isAtout(string ,Carte);
friend bool exist(vector<Carte>,Carte);
friend void tour_de_table(bool&,int,vector<Joueur*>&,vector<Joueur*>&,string,Partie&,Joueur*,Bioche&);
};
Carte::Carte(int Numero,string symbole)
 {
     this->Numero=Numero;
     this->symbole=symbole;
 }
 /*----------------------------------------------------
----------------------------------------------------*/
 Carte::Carte (const Carte& c)
 {Numero=c.Numero ;
  symbole = c.symbole ;}
 Carte::~Carte(){}
 /*----------------------------------------------------
----------------------------------------------------*/
 int Carte::GetNumero()
{
     return this->Numero;

}
 /*----------------------------------------------------
----------------------------------------------------*/

 string Carte::GetSymbole()
{
     return this->symbole;

}
 /*----------------------------------------------------
----------------------------------------------------*/
 void Carte::setNumero(int Numero)
{
     this->Numero=Numero;

}
 /*----------------------------------------------------
----------------------------------------------------*/
 void Carte::setSymbole(string symbole)
{
     this->symbole=symbole;

}
 /*----------------------------------------------------
----------------------------------------------------*/
 bool Carte::operator ==(Carte c)
{
     return((this->Numero==c.Numero)&&(this->symbole==c.symbole));
}
 bool Carte::operator !=(Carte c)
{
    return((Numero!=c.GetNumero())||(symbole!=c.GetSymbole()));
}


class Joueur
{
private:

    string etat;
    int ingame;
    vector <Carte> cartej;
    int num;
public:
    Joueur();
    Joueur(string,int,int);

    ~Joueur() ;
        //attaque and deffence method

    bool attaque(vector <Carte> ,Carte ) ;
    bool deffence(vector <Carte>,Carte ,string symb);
        //methode to get the player's number of cards
    int nbre () ;
        //set and get of etat

    string get_etat();
    void set_etat(string);
        //set and get of ingame
    int get_ingame() ;
    void set_ingame(int) ;
        //set and get of cartej
    vector<Carte> getcartej() ;
        //get of num
    int Getnum();
    void add_c(Carte);
    vector<Carte> remove_c(Carte) ;
friend void Bioche::Distribuer(Joueur&) ;
friend void Bioche::Distribuer1(Joueur&) ;
friend void Partie::fail(Joueur&);
friend void one_gain(Joueur&, Partie& , Carte );
friend void gain(Joueur  , Partie  );
friend void deffensing_process(bool&,Joueur* ,Partie& ,string );
friend void attacking_process(bool&,Joueur*,Partie&,string);
friend void actualiser( vector<Joueur*>& );
friend Joueur* get_next (vector<Joueur*>& ,Joueur*);
friend Joueur* get_prev (vector<Joueur*>& ,Joueur*);
friend void AffichageMainJoueur(Joueur );
friend void one_vs_one(bool&,vector<Joueur*>&,string,Partie&,Joueur*);
friend bool exist(vector<Carte>,Carte);
friend void tour_de_table(bool&,int,vector<Joueur*>&,vector<Joueur*>&,string,Partie&,Joueur*,Bioche&);
friend int actualiser_nbre(vector<Joueur*>);
friend vector<Joueur> convertir(vector<Joueur*>);
};

Bioche::Bioche(vector <Carte> Pile)
    {
        for(Carte c : Pile)
        {
         this->PileBioche.push_back(c);
        }

    }

/*----------------------------------------------------
----------------------------------------------------*/
int Bioche::nbre_des_cartes()
{
    return PileBioche.size();
}
/*----------------------------------------------------
----------------------------------------------------*/
        void Bioche::Distribuer(Joueur&j)
        {
            int numero;
            string symbole;
            Carte c(numero,symbole);
            while(j.getcartej().size() < 6 )
            {
                c=PileBioche[PileBioche.size()] ;
                PileBioche.pop_back();
                //j.getcartej()[1+j.getcartej().size()] = c ;   // cartej:tableau dynamique des cartes d' un joueur donn� fausse
                j.add_c(c);
            }
        }


    // je pense qu on aura besoin que de get pour afficher l atout car les cartes du bioche vont pas etre remplacer
     Carte Bioche::getDernierCarte()
    {
     Carte c=PileBioche[PileBioche.size()-1];
      PileBioche.pop_back();
      return c;

    }
/*----------------------------------------------------
----------------------------------------------------*/
     Bioche::~Bioche()
     {
     }
/*----------------------------------------------------
----------------------------------------------------*/
     void Bioche::Distribuer1(Joueur & j )
        {

            Carte c=PileBioche.back() ;
            PileBioche.pop_back() ;
            //j.getcartej()[1+j.getcartej().size()]  = c ; // distribuer 1 carte
            j.add_c(c);
        }
/*----------------------------------------------------
----------------------------------------------------*/
    void Bioche::Distribuer2(Joueur* j )
        {

            Carte c=PileBioche.back() ;
            PileBioche.pop_back() ;
            //j.getcartej()[1+j.getcartej().size()]  = c ; // distribuer 1 carte
            j->add_c(c);
        }



Joueur::Joueur(){}//constructeur par defaut
Joueur::Joueur(string etat,int ingame,int num)
 {      //-----remarque : on peut pas choisir vector pour placer les cartes du joueur -------
        vector<Carte> CJ;
        vector<Carte>::iterator it ;
        this->etat=etat;
        this->ingame=ingame;
        this->cartej=CJ;
        this->num=num;
        //tab[num-1]= *(this);
        /*next =new Joueur();
        prev =new Joueur();*/

 }
 /*----------------------------------------------------
 ----------------------------------------------------*/

 Joueur::~Joueur(){}

 /*----------------------------------------------------
 ----------------------------------------------------*/

 /*----------------------------------------------------
 ----------------------------------------------------*/
 //methode defence qui retourne si on peut faire la defence avec une telle carte ou pas
  bool Joueur::attaque(vector<Carte> cst,Carte ca)
 {
     bool cattaque=false;
        if (cst.size()==0)
            cattaque=true;

     for (Carte c : cst)
         {
             if ((c.GetNumero() == ca.GetNumero()))
             {
               cattaque=true;
             }

         }
     return cattaque;
 }
 /*----------------------------------------------------
 ----------------------------------------------------*/
 //methode defence qui retourne si on peut faire la defence avec une telle carte ou pas
 bool Joueur::deffence(vector<Carte> cst,Carte ca,string symb)
 {
     bool deffence=false;
     /*if (((ca.GetSymbole()==cst.back().GetSymbole())&&(ca.GetNumero()>=cst.back().GetNumero()&&(ca.GetNumero()!=1)) )||(ca.GetSymbole()==cst.back().GetSymbole()&&ca.GetNumero()==1)||((ca.GetSymbole()==symb)||(ca.GetNumero()== 1 )) )
    {
      deffence=true;
    }

    return deffence;


 }*/
 if(((ca.GetSymbole()==cst.back().GetSymbole())&&(ca.GetNumero()>cst.back().GetNumero()&&(cst.back().GetNumero()!=1)) ))
 {
     deffence=true;
 }
 else if((ca.GetNumero()==1))
  {
     deffence=true;
 }
 else if(ca.GetSymbole()==symb)
 {
    deffence=true;
 }
 return deffence;
 }
 /*----------------------------------------------------
 ----------------------------------------------------*/
 //retourne le nombre de carte dans la main du joueur
 int Joueur::nbre()
 {
     return cartej.size() ;
 }
 /*----------------------------------------------------
 ----------------------------------------------------*/
 string Joueur::get_etat()
 {
     return this->etat ;
 }
 /*----------------------------------------------------
 ----------------------------------------------------*/
 void Joueur::set_etat(string E)
 {
     this->etat=E ;
 }
 /*----------------------------------------------------
 ----------------------------------------------------*/
 int Joueur::get_ingame()
 {
     return this-> ingame ;
 }
 /*----------------------------------------------------
 ----------------------------------------------------*/
 void Joueur::set_ingame(int n)
 {
     this->ingame=n;
 }
 /*----------------------------------------------------
 ----------------------------------------------------*/
 vector<Carte> Joueur::getcartej()
 {
     return (this->cartej);
 }
 /*----------------------------------------------------
 ----------------------------------------------------*/
 void Joueur::add_c(Carte c)
 {
     cartej.push_back(c);
 }
 /*----------------------------------------------------
 ----------------------------------------------------*/
 //remove une carte donn� de la main de joueur et retourne le nouveau cartej
 vector<Carte> Joueur::remove_c(Carte c)
 {   int i=0,b;
     vector<Carte> kaf ;
     /*for(i=0;i<cartej.size();i++)
     {
         if (this->cartej[i]==c)
         {
             b=i;
         }

     }
     for(i=0;i<cartej.size();i++)
     {
         if (i!=b)
         { kaf.push_back(cartej.back()) ;
            cartej.pop_back() ;


         }
         else
         {
             cartej.pop_back() ;
         }

     }*/


     /*while((cartej[i].GetNumero()!=c.GetNumero())||(cartej[i].GetSymbole()!=c.GetSymbole()))
     {
         kaf.push_back(cartej.back()) ;
         cartej.pop_back() ;
         i++;
     }
     cartej.pop_back() ;*/
     if(cartej[0]==c)
     {
         for(int j=1;j<cartej.size();j++)
         {
             kaf.push_back(cartej[j]);
         }
     }
     else if(cartej[cartej.size()-1]==c)
     {

         for(int j=0;j<cartej.size()-1;j++)
         {
             kaf.push_back(cartej[j]);
         }
     }
     else
        {
            while((cartej[i].GetNumero()!=c.GetNumero())||(cartej[i].GetSymbole()!=c.GetSymbole()))
            {
                kaf.push_back(cartej[i]);
                i++;
            }
            i++;
            while(i<cartej.size())
            {
                kaf.push_back(cartej[i]);
                i++;
            }

        }





     cartej=kaf;




     return kaf ;
 }
 /*----------------------------------------------------
 ----------------------------------------------------*/

int Joueur::Getnum()
{
    return(this->num);
}
vector<Carte> Partie::getTab()
{
    return(this->tab);
}
/*----------------------------------------------------
----------------------------------------------------*/

void Partie::fail()
{
   tab.erase(tab.begin(),tab.end());
}
/*----------------------------------------------------
----------------------------------------------------*/

void Partie::fail(Joueur& j)
{
    for (int k=0;k<tab.size();k++)
    {
        j.add_c(tab[k]);

    }

    tab.erase(tab.begin(),tab.end());
}
/*----------------------------------------------------
----------------------------------------------------*/
void Partie::ajouter(Carte & c)
{
    tab.push_back(c) ;
}
/*----------------------------------------------------
----------------------------------------------------*/
int Partie::longueur()
{
    return (tab.size());
}
/*----------------------------------------------------
----------------------------------------------------*/

bool isAtout(string symb,Carte c)
{
    return(c.GetSymbole()==symb);
}

Joueur* FirstPlayer(vector<Joueur*> tab,string symb)
{
    int b=0;
   /* Carte c1(0,symb);
    Joueur *joueur;

    for(Joueur *j : tab)
    {
        if(j->get_etat()=="maitreDurak")
        {
            return(j);
        }

        else{
                for(Carte c:j->getcartej())
                {

                    if(isAtout(symb,c))
                    {
                        if(c.GetNumero()==1)
                        {
                        return(j);
                        }
                        else if(c.GetNumero()>c1.GetNumero())
                        {
                            c1=c;
                            joueur=j;
                            b++;

                        }
                    }
                }
           }
           if(b!=0)
           {
               return(joueur);
           }

    }*/
    return(tab[2]);

}


void one_gain(Joueur &j , Partie &p , Carte c)

{
     j.remove_c(c);
     p.ajouter(c) ;
}

/*----------------------------------------------------
----------------------------------------------------*/

void gain(vector<Joueur*> T ,Joueur *j , Partie & p ) //lorsque l'attaquant gagne le tour
{


     for(Carte c  :p.getTab())
    {


        get_next(T,j)->add_c(c);

    }
 }

/*----------------------------------------------------
----------------------------------------------------*/

void AffichageCarte(Carte c)
{
    if(c.GetSymbole()=="Coeur")
    {
        if(c.GetNumero()==6)
        {
            cout<<char(186)<<"6      "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(3)<<"   "<<char(3)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(3)<<"   "<<char(3)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(3)<<"   "<<char(3)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<"      6"<<char(186)<<"\n";

        }
        if(c.GetNumero()==7)
        {
            cout<<char(186)<<"7      "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(3)<<"   "<<char(3)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(3)<<" "<<char(3)<<" "<<char(3)<<" "<<char(186)<<"\n";
            cout<<char(186)<<" "<<char(3)<<"   "<<char(3)<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      7"<<char(186)<<"\n";

        }
        if(c.GetNumero()==8)
        {
            cout<<char(186)<<"8      "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(3)<<" "<<char(3)<<" "<<char(3)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(3)<<"   "<<char(3)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(3)<<" "<<char(3)<<" "<<char(3)<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      8"<<char(186)<<"\n";

        }
        if(c.GetNumero()==9)
        {
            cout<<char(186)<<"9      "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(3)<<" "<<char(3)<<" "<<char(3)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(3)<<" "<<char(3)<<" "<<char(3)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(3)<<" "<<char(3)<<" "<<char(3)<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      9"<<char(186)<<"\n";

        }
        if(c.GetNumero()==10)
        {
            cout<<char(186)<<"10     "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<char(3)<<" "<<char(3)<<" "<<char(3)<<" "<<char(3)<<""<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(3)<<" "<<" "<<" "<<char(3)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<char(3)<<" "<<char(3)<<" "<<char(3)<<" "<<char(3)<<""<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"     10"<<char(186)<<"\n";

        }
        if(c.GetNumero()==11)
        {
            cout<<char(186)<<"J      "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<"A"<<" "<<" "<<char(3)<<"  "<<""<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<" "<<" "<<"C"<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<char(3)<<" "<<" "<<"K"<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      J"<<char(186)<<"\n";

        }
        if(c.GetNumero()==12)
        {
            cout<<char(186)<<"Q      "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<char(3)<<"  "<<""<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<" "<<" "<<char(3)<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<char(3)<<" "<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      Q"<<char(186)<<"\n";

        }
        if(c.GetNumero()==13)
        {
            cout<<char(186)<<"k      "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<char(3)<<"  "<<""<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<char(3)<<" "<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      k"<<char(186)<<"\n";

        }
        if(c.GetNumero()==1)
        {
            cout<<char(186)<<char(3)<<"A     "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<" "<<char(3)<<" "<<"  "<<""<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"     "<<char(3)<<"A"<<char(186)<<"\n";

        }

    }
    if(c.GetSymbole()=="carreau")
    {
       if(c.GetNumero()==6)
        {
            cout<<char(186)<<"6      "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(4)<<"   "<<char(4)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(4)<<"   "<<char(4)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(4)<<"   "<<char(4)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<"      6"<<char(186)<<"\n";

        }
        if(c.GetNumero()==7)
        {
            cout<<char(186)<<"7      "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(4)<<"   "<<char(4)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(4)<<" "<<char(4)<<" "<<char(4)<<" "<<char(186)<<"\n";
            cout<<char(186)<<" "<<char(4)<<"   "<<char(4)<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      7"<<char(186)<<"\n";

        }
        if(c.GetNumero()==8)
        {
            cout<<char(186)<<"8      "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(4)<<" "<<char(4)<<" "<<char(4)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(4)<<"   "<<char(4)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(4)<<" "<<char(4)<<" "<<char(4)<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      8"<<char(186)<<"\n";

        }
        if(c.GetNumero()==9)
        {
            cout<<char(186)<<"9      "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(4)<<" "<<char(4)<<" "<<char(4)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(4)<<" "<<char(4)<<" "<<char(4)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(4)<<" "<<char(4)<<" "<<char(4)<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      9"<<char(186)<<"\n";

        }
        if(c.GetNumero()==10)
        {
            cout<<char(186)<<"10     "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<char(4)<<" "<<char(4)<<" "<<char(4)<<" "<<char(4)<<""<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(4)<<" "<<" "<<" "<<char(4)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<char(4)<<" "<<char(4)<<" "<<char(4)<<" "<<char(4)<<""<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"     10"<<char(186)<<"\n";

        }
        if(c.GetNumero()==11)
        {
            cout<<char(186)<<"J      "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<"A"<<" "<<" "<<char(4)<<"  "<<""<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<" "<<" "<<"C"<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<char(4)<<" "<<" "<<"K"<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      J"<<char(186)<<"\n";

        }
        if(c.GetNumero()==12)
        {
            cout<<char(186)<<"Q      "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<char(4)<<"  "<<""<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<" "<<" "<<char(4)<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<char(4)<<" "<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      Q"<<char(186)<<"\n";

        }
        if(c.GetNumero()==13)
        {
            cout<<char(186)<<"k      "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<char(4)<<"  "<<""<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<char(4)<<" "<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      k"<<char(186)<<"\n";

        }
        if(c.GetNumero()==1)
        {
            cout<<char(186)<<char(4)<<"A     "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<" "<<char(4)<<" "<<"  "<<""<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"     "<<char(4)<<"A"<<char(186)<<"\n";

        }

    }
    if(c.GetSymbole()=="trefle")
    {
        if(c.GetNumero()==6)
        {
            cout<<char(186)<<"6      "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(5)<<"   "<<char(5)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(5)<<"   "<<char(5)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(5)<<"   "<<char(5)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<"      6"<<char(186)<<"\n";

        }
        if(c.GetNumero()==7)
        {
            cout<<char(186)<<"7      "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(5)<<"   "<<char(5)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(5)<<" "<<char(5)<<" "<<char(5)<<" "<<char(186)<<"\n";
            cout<<char(186)<<" "<<char(5)<<"   "<<char(5)<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      7"<<char(186)<<"\n";

        }
        if(c.GetNumero()==8)
        {
            cout<<char(186)<<"8      "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(5)<<" "<<char(5)<<" "<<char(5)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(5)<<"   "<<char(5)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(5)<<" "<<char(5)<<" "<<char(5)<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      8"<<char(186)<<"\n";

        }
        if(c.GetNumero()==9)
        {
            cout<<char(186)<<"9      "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(5)<<" "<<char(5)<<" "<<char(5)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(5)<<" "<<char(5)<<" "<<char(5)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(5)<<" "<<char(5)<<" "<<char(5)<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      9"<<char(186)<<"\n";

        }
        if(c.GetNumero()==10)
        {
            cout<<char(186)<<"10     "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<char(5)<<" "<<char(5)<<" "<<char(5)<<" "<<char(5)<<""<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(5)<<" "<<" "<<" "<<char(5)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<char(5)<<" "<<char(5)<<" "<<char(5)<<" "<<char(5)<<""<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"     10"<<char(186)<<"\n";

        }
        if(c.GetNumero()==11)
        {
            cout<<char(186)<<"J      "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<"A"<<" "<<" "<<char(5)<<"  "<<""<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<" "<<" "<<"C"<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<char(5)<<" "<<" "<<"K"<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      J"<<char(186)<<"\n";

        }
        if(c.GetNumero()==12)
        {
            cout<<char(186)<<"Q      "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<char(5)<<"  "<<""<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<" "<<" "<<char(5)<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<char(5)<<" "<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      Q"<<char(186)<<"\n";

        }
        if(c.GetNumero()==13)
        {
            cout<<char(186)<<"k      "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<char(5)<<"  "<<""<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<char(5)<<" "<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      k"<<char(186)<<"\n";

        }
        if(c.GetNumero()==1)
        {
            cout<<char(186)<<char(5)<<"A     "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<" "<<char(5)<<" "<<"  "<<""<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"     "<<char(5)<<"A"<<char(186)<<"\n";

        }

    }
    if(c.GetSymbole()=="pique")
    {
        if(c.GetNumero()==6)
        {
            cout<<char(186)<<"6      "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(6)<<"   "<<char(6)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(6)<<"   "<<char(6)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(6)<<"   "<<char(6)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<"      6"<<char(186)<<"\n";

        }
        if(c.GetNumero()==7)
        {
            cout<<char(186)<<"7      "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(6)<<"   "<<char(6)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(6)<<" "<<char(6)<<" "<<char(6)<<" "<<char(186)<<"\n";
            cout<<char(186)<<" "<<char(6)<<"   "<<char(6)<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      7"<<char(186)<<"\n";

        }
        if(c.GetNumero()==8)
        {
            cout<<char(186)<<"8      "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(6)<<" "<<char(6)<<" "<<char(6)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(6)<<"   "<<char(6)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(6)<<" "<<char(6)<<" "<<char(6)<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      8"<<char(186)<<"\n";

        }
        if(c.GetNumero()==9)
        {
            cout<<char(186)<<"9      "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(6)<<" "<<char(6)<<" "<<char(6)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(6)<<" "<<char(6)<<" "<<char(6)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(6)<<" "<<char(6)<<" "<<char(6)<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      9"<<char(186)<<"\n";

        }
        if(c.GetNumero()==10)
        {
            cout<<char(186)<<"10     "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<char(6)<<" "<<char(6)<<" "<<char(6)<<" "<<char(6)<<""<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<char(6)<<" "<<" "<<" "<<char(6)<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<char(6)<<" "<<char(6)<<" "<<char(6)<<" "<<char(6)<<""<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"     10"<<char(186)<<"\n";

        }
        if(c.GetNumero()==11)
        {
            cout<<char(186)<<"J      "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<"A"<<" "<<" "<<char(6)<<"  "<<""<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<" "<<" "<<"C"<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<char(6)<<" "<<" "<<"K"<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      J"<<char(186)<<"\n";

        }
        if(c.GetNumero()==12)
        {
            cout<<char(186)<<"Q      "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<char(6)<<"  "<<""<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<" "<<" "<<char(6)<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<char(6)<<" "<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      Q"<<char(186)<<"\n";

        }
        if(c.GetNumero()==13)
        {
            cout<<char(186)<<"k      "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<char(6)<<"  "<<""<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<char(6)<<" "<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"      k"<<char(186)<<"\n";

        }
        if(c.GetNumero()==1)
        {
            cout<<char(186)<<char(6)<<"A     "<<char(186)<<"\n";
            cout<<""<<char(186)<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<" "<<char(6)<<" "<<"  "<<""<<char(186)<<"\n";
            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\n";
            cout<<""<<""<<char(186)<<"     "<<char(6)<<"A"<<char(186)<<"\n";

        }

    }
}
    void AffichageMainJoueur(Joueur j)
    {
        for(Carte c : j.getcartej()  )
        {
            AffichageCarte(c);
        }
    }

    void AffichageCartePlateau(Partie p)
    {
        for (Carte c : p.getTab())
        {
            cout<<"Numero:"<<c.GetNumero()<<" | Symbole:"<<c.GetSymbole();
        }
    }
void AffichageMainJoueur2(vector<Carte> tab)
    {
        int i=0;
        int n=tab.size();
        vector <Carte> tab1;

        if(n<=6)
        {

            for(int j=0;j<n;j++)
            {
                tab1.push_back(tab[j]);
            }

        }


        while(i<5)
        {
            for(Carte c: tab1)
            {
                if(i==0)
                {

                    if(c.GetSymbole()=="Coeur")
                    {
                        if(c.GetNumero()==6)
                        {
                            cout<<char(186)<<"6      "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==7)
                        {
                            cout<<char(186)<<"7      "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==8)
                        {
                            cout<<char(186)<<"8      "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==9)
                        {
                            cout<<char(186)<<"9      "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==10)
                        {
                            cout<<char(186)<<"10     "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==11)
                        {
                            cout<<char(186)<<"J      "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==12)
                        {
                            cout<<char(186)<<"Q      "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==13)
                        {
                            cout<<char(186)<<"k      "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==1)
                        {
                            cout<<char(186)<<char(3)<<"A     "<<char(186)<<"\t";


                        }

                    }
                    if(c.GetSymbole()=="carreau")
                    {
                    if(c.GetNumero()==6)
                        {
                            cout<<char(186)<<"6      "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==7)
                        {
                            cout<<char(186)<<"7      "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==8)
                        {
                            cout<<char(186)<<"8      "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==9)
                        {
                            cout<<char(186)<<"9      "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==10)
                        {
                            cout<<char(186)<<"10     "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==11)
                        {
                            cout<<char(186)<<"J      "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==12)
                        {
                            cout<<char(186)<<"Q      "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==13)
                        {
                            cout<<char(186)<<"k      "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==1)
                        {
                            cout<<char(186)<<char(4)<<"A     "<<char(186)<<"\t";


                        }

                    }
                    if(c.GetSymbole()=="trefle")
                    {
                        if(c.GetNumero()==6)
                        {
                            cout<<char(186)<<"6      "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==7)
                        {
                            cout<<char(186)<<"7      "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==8)
                        {
                            cout<<char(186)<<"8      "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==9)
                        {
                            cout<<char(186)<<"9      "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==10)
                        {
                            cout<<char(186)<<"10     "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==11)
                        {
                            cout<<char(186)<<"J      "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==12)
                        {
                            cout<<char(186)<<"Q      "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==13)
                        {
                            cout<<char(186)<<"k      "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==1)
                        {
                            cout<<char(186)<<char(5)<<"A     "<<char(186)<<"\t";


                        }

                    }
                    if(c.GetSymbole()=="pique")
                    {
                        if(c.GetNumero()==6)
                        {
                            cout<<char(186)<<"6      "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==7)
                        {
                            cout<<char(186)<<"7      "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==8)
                        {
                            cout<<char(186)<<"8      "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==9)
                        {
                            cout<<char(186)<<"9      "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==10)
                        {
                            cout<<char(186)<<"10     "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==11)
                        {
                            cout<<char(186)<<"J      "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==12)
                        {
                            cout<<char(186)<<"Q      "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==13)
                        {
                            cout<<char(186)<<"k      "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==1)
                        {
                            cout<<char(186)<<char(6)<<"A     "<<char(186)<<"\t";

                        }

                     }


                }
                if(i==1)
                {
                    if(c.GetSymbole()=="Coeur")
                    {
                        if(c.GetNumero()==6)
                        {

                            cout<<""<<char(186)<<" "<<char(3)<<"   "<<char(3)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==7)
                        {

                            cout<<""<<char(186)<<" "<<char(3)<<"   "<<char(3)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==8)
                        {

                            cout<<""<<char(186)<<" "<<char(3)<<" "<<char(3)<<" "<<char(3)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==9)
                        {

                            cout<<""<<char(186)<<" "<<char(3)<<" "<<char(3)<<" "<<char(3)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==10)
                        {

                            cout<<""<<char(186)<<""<<char(3)<<" "<<char(3)<<" "<<char(3)<<" "<<char(3)<<""<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==11)
                        {

                            cout<<""<<char(186)<<""<<" "<<"A"<<" "<<" "<<char(3)<<"  "<<""<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==12)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<char(3)<<"  "<<""<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==13)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<char(3)<<"  "<<""<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==1)
                        {

                            cout<<""<<char(186)<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\t";


                        }

                    }
                    if(c.GetSymbole()=="carreau")
                    {
                    if(c.GetNumero()==6)
                        {

                            cout<<""<<char(186)<<" "<<char(4)<<"   "<<char(4)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==7)
                        {

                            cout<<""<<char(186)<<" "<<char(4)<<"   "<<char(4)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==8)
                        {

                            cout<<""<<char(186)<<" "<<char(4)<<" "<<char(4)<<" "<<char(4)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==9)
                        {

                            cout<<""<<char(186)<<" "<<char(4)<<" "<<char(4)<<" "<<char(4)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==10)
                        {

                            cout<<""<<char(186)<<""<<char(4)<<" "<<char(4)<<" "<<char(4)<<" "<<char(4)<<""<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==11)
                        {

                            cout<<""<<char(186)<<""<<" "<<"A"<<" "<<" "<<char(4)<<"  "<<""<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==12)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<char(4)<<"  "<<""<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==13)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<char(4)<<"  "<<""<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==1)
                        {

                            cout<<""<<char(186)<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\t";


                        }

                    }
                    if(c.GetSymbole()=="trefle")
                    {
                        if(c.GetNumero()==6)
                        {

                            cout<<""<<char(186)<<" "<<char(5)<<"   "<<char(5)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==7)
                        {

                            cout<<""<<char(186)<<" "<<char(5)<<"   "<<char(5)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==8)
                        {

                            cout<<""<<char(186)<<" "<<char(5)<<" "<<char(5)<<" "<<char(5)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==9)
                        {

                            cout<<""<<char(186)<<" "<<char(5)<<" "<<char(5)<<" "<<char(5)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==10)
                        {

                            cout<<""<<char(186)<<""<<char(5)<<" "<<char(5)<<" "<<char(5)<<" "<<char(5)<<""<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==11)
                        {

                            cout<<""<<char(186)<<""<<" "<<"A"<<" "<<" "<<char(5)<<"  "<<""<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==12)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<char(5)<<"  "<<""<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==13)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<char(5)<<"  "<<""<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==1)
                        {

                            cout<<""<<char(186)<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\t";

                        }

                    }
                    if(c.GetSymbole()=="pique")
                    {
                        if(c.GetNumero()==6)
                        {

                            cout<<""<<char(186)<<" "<<char(6)<<"   "<<char(6)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==7)
                        {

                            cout<<""<<char(186)<<" "<<char(6)<<"   "<<char(6)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==8)
                        {

                            cout<<""<<char(186)<<" "<<char(6)<<" "<<char(6)<<" "<<char(6)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==9)
                        {

                            cout<<""<<char(186)<<" "<<char(6)<<" "<<char(6)<<" "<<char(6)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==10)
                        {

                            cout<<""<<char(186)<<""<<char(6)<<" "<<char(6)<<" "<<char(6)<<" "<<char(6)<<""<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==11)
                        {

                            cout<<""<<char(186)<<""<<" "<<"A"<<" "<<" "<<char(6)<<"  "<<""<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==12)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<char(6)<<"  "<<""<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==13)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<char(6)<<"  "<<""<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==1)
                        {

                            cout<<""<<char(186)<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\t";


                        }

                     }

                }
                if(i==2)
                {
                    if(c.GetSymbole()=="Coeur")
                    {
                        if(c.GetNumero()==6)
                        {

                            cout<<""<<char(186)<<" "<<char(3)<<"   "<<char(3)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==7)
                        {

                            cout<<""<<char(186)<<" "<<char(3)<<" "<<char(3)<<" "<<char(3)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==8)
                        {

                            cout<<""<<char(186)<<" "<<char(3)<<"   "<<char(3)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==9)
                        {

                            cout<<""<<char(186)<<" "<<char(3)<<" "<<char(3)<<" "<<char(3)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==10)
                        {

                            cout<<""<<char(186)<<" "<<char(3)<<" "<<" "<<" "<<char(3)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==11)
                        {

                            cout<<""<<char(186)<<" "<<" "<<" "<<"C"<<" "<<" "<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==12)
                        {

                            cout<<""<<char(186)<<" "<<" "<<" "<<char(3)<<" "<<" "<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==13)
                        {

                            cout<<""<<char(186)<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==1)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<" "<<char(3)<<" "<<"  "<<""<<char(186)<<"\t";

                        }

                    }
                    if(c.GetSymbole()=="carreau")
                    {
                    if(c.GetNumero()==6)
                        {

                            cout<<""<<char(186)<<" "<<char(4)<<"   "<<char(4)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==7)
                        {

                            cout<<""<<char(186)<<" "<<char(4)<<" "<<char(4)<<" "<<char(4)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==8)
                        {

                            cout<<""<<char(186)<<" "<<char(4)<<"   "<<char(4)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==9)
                        {

                            cout<<""<<char(186)<<" "<<char(4)<<" "<<char(4)<<" "<<char(4)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==10)
                        {

                            cout<<""<<char(186)<<" "<<char(4)<<" "<<" "<<" "<<char(4)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==11)
                        {

                            cout<<""<<char(186)<<" "<<" "<<" "<<"C"<<" "<<" "<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==12)
                        {

                            cout<<""<<char(186)<<" "<<" "<<" "<<char(4)<<" "<<" "<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==13)
                        {

                            cout<<""<<char(186)<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==1)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<" "<<char(4)<<" "<<"  "<<""<<char(186)<<"\t";

                        }

                    }
                    if(c.GetSymbole()=="trefle")
                    {
                        if(c.GetNumero()==6)
                        {

                            cout<<""<<char(186)<<" "<<char(5)<<"   "<<char(5)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==7)
                        {

                            cout<<""<<char(186)<<" "<<char(5)<<" "<<char(5)<<" "<<char(5)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==8)
                        {

                            cout<<""<<char(186)<<" "<<char(5)<<"   "<<char(5)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==9)
                        {

                            cout<<""<<char(186)<<" "<<char(5)<<" "<<char(5)<<" "<<char(5)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==10)
                        {

                            cout<<""<<char(186)<<" "<<char(5)<<" "<<" "<<" "<<char(5)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==11)
                        {

                            cout<<""<<char(186)<<" "<<" "<<" "<<"C"<<" "<<" "<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==12)
                        {

                            cout<<""<<char(186)<<" "<<" "<<" "<<char(5)<<" "<<" "<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==13)
                        {

                            cout<<""<<char(186)<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==1)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<" "<<char(5)<<" "<<"  "<<""<<char(186)<<"\t";

                        }

                    }
                    if(c.GetSymbole()=="pique")
                    {
                        if(c.GetNumero()==6)
                        {

                            cout<<""<<char(186)<<" "<<char(6)<<"   "<<char(6)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==7)
                        {

                            cout<<""<<char(186)<<" "<<char(6)<<" "<<char(6)<<" "<<char(6)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==8)
                        {

                            cout<<""<<char(186)<<" "<<char(6)<<"   "<<char(6)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==9)
                        {

                            cout<<""<<char(186)<<" "<<char(6)<<" "<<char(6)<<" "<<char(6)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==10)
                        {

                            cout<<""<<char(186)<<" "<<char(6)<<" "<<" "<<" "<<char(6)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==11)
                        {

                            cout<<""<<char(186)<<" "<<" "<<" "<<"C"<<" "<<" "<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==12)
                        {

                            cout<<""<<char(186)<<" "<<" "<<" "<<char(6)<<" "<<" "<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==13)
                        {

                            cout<<""<<char(186)<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==1)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<" "<<char(6)<<" "<<"  "<<""<<char(186)<<"\t";

                        }

                     }

                }
                if(i==3)
                {
                    if(c.GetSymbole()=="Coeur")
                    {
                        if(c.GetNumero()==6)
                        {

                            cout<<""<<char(186)<<" "<<char(3)<<"   "<<char(3)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==7)
                        {

                            cout<<char(186)<<" "<<char(3)<<"   "<<char(3)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==8)
                        {

                            cout<<""<<char(186)<<" "<<char(3)<<" "<<char(3)<<" "<<char(3)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==9)
                        {

                            cout<<""<<char(186)<<" "<<char(3)<<" "<<char(3)<<" "<<char(3)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==10)
                        {

                            cout<<""<<char(186)<<""<<char(3)<<" "<<char(3)<<" "<<char(3)<<" "<<char(3)<<""<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==11)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<char(3)<<" "<<" "<<"K"<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==12)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<char(3)<<" "<<" "<<" "<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==13)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<char(3)<<" "<<" "<<" "<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==1)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\t";

                        }

                    }
                    if(c.GetSymbole()=="carreau")
                    {
                    if(c.GetNumero()==6)
                        {

                            cout<<""<<char(186)<<" "<<char(4)<<"   "<<char(4)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==7)
                        {

                            cout<<char(186)<<" "<<char(4)<<"   "<<char(4)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==8)
                        {

                            cout<<""<<char(186)<<" "<<char(4)<<" "<<char(4)<<" "<<char(4)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==9)
                        {

                            cout<<""<<char(186)<<" "<<char(4)<<" "<<char(4)<<" "<<char(4)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==10)
                        {

                            cout<<""<<char(186)<<""<<char(4)<<" "<<char(4)<<" "<<char(4)<<" "<<char(4)<<""<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==11)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<char(4)<<" "<<" "<<"K"<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==12)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<char(4)<<" "<<" "<<" "<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==13)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<char(4)<<" "<<" "<<" "<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==1)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\t";


                        }

                    }
                    if(c.GetSymbole()=="trefle")
                    {
                        if(c.GetNumero()==6)
                        {

                            cout<<""<<char(186)<<" "<<char(5)<<"   "<<char(5)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==7)
                        {

                            cout<<char(186)<<" "<<char(5)<<"   "<<char(5)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==8)
                        {


                            cout<<""<<char(186)<<" "<<char(5)<<" "<<char(5)<<" "<<char(5)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==9)
                        {

                            cout<<""<<char(186)<<" "<<char(5)<<" "<<char(5)<<" "<<char(5)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==10)
                        {

                            cout<<""<<char(186)<<""<<char(5)<<" "<<char(5)<<" "<<char(5)<<" "<<char(5)<<""<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==11)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<char(5)<<" "<<" "<<"K"<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==12)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<char(5)<<" "<<" "<<" "<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==13)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<char(5)<<" "<<" "<<" "<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==1)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\t";


                        }

                    }
                    if(c.GetSymbole()=="pique")
                    {
                        if(c.GetNumero()==6)
                        {

                            cout<<""<<char(186)<<" "<<char(6)<<"   "<<char(6)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==7)
                        {

                            cout<<char(186)<<" "<<char(6)<<"   "<<char(6)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==8)
                        {

                            cout<<""<<char(186)<<" "<<char(6)<<" "<<char(6)<<" "<<char(6)<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==9)
                        {

                            cout<<""<<char(186)<<" "<<char(6)<<" "<<char(6)<<" "<<char(6)<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==10)
                        {

                            cout<<""<<char(186)<<""<<char(6)<<" "<<char(6)<<" "<<char(6)<<" "<<char(6)<<""<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==11)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<char(6)<<" "<<" "<<"K"<<" "<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==12)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<char(6)<<" "<<" "<<" "<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==13)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<char(6)<<" "<<" "<<" "<<" "<<char(186)<<"\t";


                        }
                        if(c.GetNumero()==1)
                        {

                            cout<<""<<char(186)<<""<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<char(186)<<"\t";


                        }

                     }

                }
                if(i==4)
                {
                      if(c.GetSymbole()=="Coeur")
                    {
                        if(c.GetNumero()==6)
                        {

                            cout<<""<<char(186)<<"      6"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==7)
                        {

                            cout<<""<<""<<char(186)<<"      7"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==8)
                        {

                            cout<<""<<""<<char(186)<<"      8"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==9)
                        {

                            cout<<""<<""<<char(186)<<"      9"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==10)
                        {

                            cout<<""<<""<<char(186)<<"     10"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==11)
                        {

                            cout<<""<<""<<char(186)<<"      J"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==12)
                        {

                            cout<<""<<""<<char(186)<<"      Q"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==13)
                        {

                            cout<<""<<""<<char(186)<<"      k"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==1)
                        {

                            cout<<""<<""<<char(186)<<"     "<<char(3)<<"A"<<char(186)<<"\t";

                        }

                    }
                    if(c.GetSymbole()=="carreau")
                    {
                    if(c.GetNumero()==6)
                        {
                            cout<<""<<char(186)<<"      6"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==7)
                        {

                            cout<<""<<""<<char(186)<<"      7"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==8)
                        {

                            cout<<""<<""<<char(186)<<"      8"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==9)
                        {

                            cout<<""<<""<<char(186)<<"      9"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==10)
                        {

                            cout<<""<<""<<char(186)<<"     10"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==11)
                        {

                            cout<<""<<""<<char(186)<<"      J"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==12)
                        {

                            cout<<""<<""<<char(186)<<"      Q"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==13)
                        {

                            cout<<""<<""<<char(186)<<"      k"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==1)
                        {

                            cout<<""<<""<<char(186)<<"     "<<char(4)<<"A"<<char(186)<<"\t";

                        }

                    }
                    if(c.GetSymbole()=="trefle")
                    {
                        if(c.GetNumero()==6)
                        {

                            cout<<""<<char(186)<<"      6"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==7)
                        {

                            cout<<""<<""<<char(186)<<"      7"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==8)
                        {

                            cout<<""<<""<<char(186)<<"      8"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==9)
                        {

                            cout<<""<<""<<char(186)<<"      9"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==10)
                        {

                            cout<<""<<""<<char(186)<<"     10"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==11)
                        {

                            cout<<""<<""<<char(186)<<"      J"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==12)
                        {

                            cout<<""<<""<<char(186)<<"      Q"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==13)
                        {

                            cout<<""<<""<<char(186)<<"      k"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==1)
                        {

                            cout<<""<<""<<char(186)<<"     "<<char(5)<<"A"<<char(186)<<"\t";

                        }

                    }
                    if(c.GetSymbole()=="pique")
                    {
                        if(c.GetNumero()==6)
                        {

                            cout<<""<<char(186)<<"      6"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==7)
                        {

                            cout<<""<<""<<char(186)<<"      7"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==8)
                        {

                            cout<<""<<""<<char(186)<<"      8"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==9)
                        {

                            cout<<""<<""<<char(186)<<"      9"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==10)
                        {

                            cout<<""<<""<<char(186)<<"     10"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==11)
                        {

                            cout<<""<<""<<char(186)<<"      J"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==12)
                        {

                            cout<<""<<""<<char(186)<<"      Q"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==13)
                        {

                            cout<<""<<""<<char(186)<<"      k"<<char(186)<<"\t";

                        }
                        if(c.GetNumero()==1)
                        {

                            cout<<""<<""<<char(186)<<"     "<<char(6)<<"A"<<char(186)<<"\t";

                        }

                     }

                }


    }
    i++;
    cout<<endl;
    }
    cout<<endl;

     if(n>6)
               {
            vector <Carte> tab1;
            vector <Carte> tab2;

            for(int j=0;j<6;j++)
            {
                tab1.push_back(tab[j]);
            }

            AffichageMainJoueur2(tab1);
            cout<<endl;

            for(int j=6;j<n;j++)
            {
                tab2.push_back(tab[j]);
            }
            AffichageMainJoueur2(tab2);

            }







    }

/*-------------------------------------------
-------------------------------------------*/
vector<Joueur> tab4;
bool exist(vector<Carte> kaf , Carte Cst )
{
    for(Carte c: kaf )
    {
        if((c.GetNumero()==Cst.GetNumero())&&(c.GetSymbole()==Cst.GetSymbole()))
        {
            return true;
        }
    }
return false;
}
void deffensing_process(bool& k,Joueur* j,Partie& p,string symbole)
{
   if (j->Getnum()==1)
    {
        bool A;
        string B;

        
        cout<<"THIS ARE YOUR CARDS "<<endl;
        sleep(0.85);
        cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
        AffichageMainJoueur2(j->getcartej());
        sleep(0.85);
        cout<<"YOUR TURN TO DEFEND"<<endl;
        cout<<"DO YOU WANT TO PLAY (Y/N)?"<<endl;
        cin>>B;
        while ((B!="N")&&(B!="n")&&(B!="Y")&&(B!="y"))
        {  cout<<"Y FOR YES AND N FOR NO"<<endl;
            cin>> B ;
        }
        
        
        int num;
        string sym;
        Carte c1(num,sym) ;
        if(B=="N"||B=="n")
        {

            p.fail((*j));

            k=false ;


        }

        if(B=="Y"||B=="y")
        {
            /**/

            cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
            if(p.getTab().size()!=0)
            {
                cout<<"THIS IS THE CARDS IN THE TABLE:\n";
                sleep(1);
                AffichageMainJoueur2(p.getTab());
            }

            cout<<"CHOOSE THE CARD NUMBER , PRESS ENTER.THEN CHOOSE IT SYMBOLE"<<endl;
            sleep(1);
            cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
            cin>>num>>sym;
            c1.setNumero(num);
            c1.setSymbole(sym);


            A=j->deffence(p.getTab(),c1,symbole);

            while(A==false)
                {

                    cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
                    int num ;
                    string sym ;
                   cout<<"CHOOSE THE CARD NUMBER , PRESS ENTER.THEN CHOOSE IT SYMBOLE"<<endl;
                   sleep(1);
                    cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
                    cin>>num>>sym;
                    c1.setNumero(num);
                    c1.setSymbole(sym);

                    A=j->deffence(p.getTab(),c1,symbole);
                }
           one_gain((*j),p,c1) ;
         k=true;
        }
    }
  else
   {

       cout<<"THIS IS THE PLAYER NUMBER( "<<j->Getnum()<<")'S TURN TO DEFEND"<<endl;
       sleep(1.2);
       Carte cdeffence(0,"None");
       Carte c3=cdeffence;

      for(Carte c1 : j->getcartej())
      {
          bool def=j->deffence(p.getTab(),c1,symbole);
           if (def )
          {
           cdeffence=c1;
           }
        }

        if(cdeffence!=c3)
        {


           one_gain((*j),p,cdeffence);
           k=true ;
           cout<<""<<"HE PLAYED THIS CARD :"<<endl;
           sleep(1);
                cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
                AffichageCarte(cdeffence);
                cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;

                sleep(1);
        }
        else
            {
                cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;

                cout<<j->Getnum()<<"HE SKIPPED HIS TURN"<<endl;
                sleep(1);

                p.fail(*j);

                k=false ;


            }


    }


}


void attacking_process(bool& a,Joueur* j,Partie& p,string symbole)
{
    if (j->Getnum()==1)
    {   
        cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"THIS IS YOUR TURN TO ATTACK!"<<endl;
        
        cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"THIS ARE YOUR CARDS :\n";
        sleep(1);
         AffichageMainJoueur2(j->getcartej());
        int num ;
        string sym ;
        int r=0;
        string B;
        Carte c1(num,sym) ;
        bool A;
        if(p.getTab().size()!=0)
            {   
                cout<<"THIS IS THE CARDS IN THE TABLE :\n";
                cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
                AffichageMainJoueur2(p.getTab());
                sleep(1);
                cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
            }

        cout<<"DO YOU WANT TO ATTACK(Y/N)?"<<endl;
         cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;

           cin>>B;
         while ((B!="N")&&(B!="n")&&(B!="Y")&&(B!="y"))
        {  cout<<"Y FOR YES AND N FOR NO"<<endl;
        
            cin>> B ;
        }
        

        if (B=="Y"||B=="y")
        {
           
           
            if(p.getTab().size()!=0)
            {
                cout<<"THIS IS YOUR CARDS:\n";
                
                AffichageMainJoueur2(p.getTab());
                sleep(1.1);
            }

            cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
            
            cout<<"CHOOSE THE CARD NUMBER , PRESS ENTER.THEN CHOOSE IT SYMBOLE"<<endl;
            
            cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
            cin>>num>>sym;
            c1.setNumero(num);
            c1.setSymbole(sym);
            cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;

            A=j->attaque(p.getTab(),c1);

            while(((A==false)||(!exist(j->getcartej(),c1)))&&(r==0))
             {
                    cout<<"YOU PLAYED A WRONG CARD ! DO YOU WANT TO TRY AGAIN?"<<endl;
                    sleep(0.85);
                    cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
                    sleep(0.85);
                    cin>>B ;
                    if (B=="N"||B=="n")
                    {
                        p.fail();
                        a=false ;
                        r+=1;
                    }
            if(r==0)
            {

                    cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
            sleep(1);
            cout<<"CHOOSE THE CARD NUMBER , PRESS ENTER.THEN CHOOSE IT SYMBOLE"<<endl;
            cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
            cin>>num>>sym;
            c1.setNumero(num);
            c1.setSymbole(sym);
            cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;

                A=j->attaque(p.getTab(),c1);

            }
            }


            if(r==0)
            {
              one_gain(*j,p,c1);
              a=true;
            }

        }
        else if (B=="N"||B=="n")
        {
            cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
            sleep(1.3);
            p.fail();

            a=false ;


        }
        }
    else
    {

     cout<<"THIS IS THE PLAYER NUMBER ("<<j->Getnum()<<") 'S TURN TO ATTACK"<<endl;
     sleep(1);
     cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
     int num2;
     string sym2;
     Carte c2(num2,sym2);
     Carte c1=c2;
      for(Carte c : j->getcartej())
      {

          if(j->attaque(p.getTab(),c))
           {
           c2=c;
           }
       }
                   if(c1!=c2)
            {
                one_gain((*j),p,c2);
                cout<<"HE PLAYED THIS CARD :"<<endl;
                sleep(1);
                cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
                AffichageCarte(c2);
                sleep(1);
                cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
                a=true;
                sleep(1);

            }
            else
            {
                cout<<j->Getnum()<<"HE SKIPPED HIS TURN !"<<endl;
                sleep(1.2);

                p.fail();

                a=false;
            }

 }
}


void actualiser( vector<Joueur*>&  tab )
   {
       vector<Joueur*>  tab1;
       for(Joueur* j:tab)
       {
           if((j->get_ingame())==1)
           {
               tab1.push_back(j) ;
           }
       }
       tab.clear();
       for(Joueur* p:tab1)
       {
           tab.push_back(p);
       }
   }




bool maitre(vector<Joueur*> tab)
{
    for(Joueur* J : tab )
    {    //int c=0 ;
        if (J->get_etat()=="MaitreDurak" )
          {
             return 1 ;
          }
    }
    return 0 ;

}
/*---------------------------------------------
-------------------------------------------------*/
int g=0;
int d;
/*---------------------------------------------
-------------------------------------------------*/
void one_vs_one(bool& k,vector<Joueur*>& tableau_joueurs,string symbole,Partie& p,Joueur* attaquant,vector<Joueur*> tableau_reserve)
{   k=true;
    bool q=true;
    if(tableau_joueurs.size()>1)
    {
     while ((k==true))
        { attacking_process(q,attaquant,p,symbole);
           k=false;


                    if((q==true))
                    { if((attaquant->nbre()==0))
                             {attaquant->set_ingame(0);
                            if(attaquant->Getnum()==1)
                            {
                                d+=1;
                            }
                              if((attaquant->Getnum()!=1)&&(d!=1))
                              {
                               g+=1;
                              }
                              
                             }
                       if(p.getTab().size()!=0)
                        {
                            cout<<"THIS IS THE CARDS IN THE TABLE :\n";
                            sleep(0.85);
                            AffichageMainJoueur2(p.getTab());
                        }
                      deffensing_process(k,get_next(tableau_joueurs,attaquant),p,symbole);


                        if((get_next(tableau_joueurs,attaquant)->nbre())==0)
                           {
                               get_next(tableau_joueurs,attaquant)->set_ingame(0);
                              if(attaquant->Getnum()==1)
                            {
                                d+=1;
                            }
                              if((attaquant->Getnum()!=1)&&(d!=1))
                              {
                               g+=1;
                              }
                            }


                    }
                     actualiser(tableau_joueurs);
        }
    }

}

int actualiser_nbre(vector<Joueur*> tab)
{
    tab4.clear();
    for(Joueur* j:tab)
    {  if((j->get_ingame())==1)
        {
            tab4.push_back(*j);
        }
    }
    return tab4.size();
}
/*int actualiser_nbre(vector<Joueur*> tab)
{
    tab4=convertir(tab);
    actualiser(tab4);
    return(tab4.size());

}*/
void tour_de_table(bool& k,int n,vector<Joueur*>& tableau_joueurs,vector<Joueur*>& tableau_reserve,string symbole,Partie &p,Joueur* player,Bioche &b)
{
    k=true;
    int h=0;
    int n1=tableau_joueurs.size();


            while((h<n1)&&(tableau_joueurs.size()!=1))
            {
                one_vs_one(k,tableau_joueurs,symbole,p,tableau_joueurs[h],tableau_reserve);
                sleep(1);
                h++;
            }
            actualiser(tableau_joueurs) ;
}
     void Creation_Pile(vector<Carte>& v,vector<string> TabSym,vector<int> TabNum)
    {

        for(string s:TabSym)
        {
          for(int i:TabNum)
            {
              Carte c1(i,s) ;
              v.push_back(c1) ;

            }
        } // remplissage d'un tableau par des cartes dans l ' ordre

        srand(time(NULL));// g�n�rer une nouvelle s�rie des nombres al�atoires � chaque fois

         for(int i=0 ; i<36; ++i)
        {
         int j=rand()%36;
         Carte temp=v[i] ;
         v[i] =v[j] ;
         v[j] = temp ;

        } //L'ordre des cartes dans v  devient al�atoire


    }
    void addJoueur(vector<Joueur*> & tab,Joueur *j)
    {
        tab.push_back(j);
    }
    void addJoueur2(vector<Joueur*>& tab,Joueur* j)
    {
        tab.push_back(j);
    }
Joueur* get_next(vector<Joueur*>& t , Joueur* j)
{  int i;
    for(i=0;i<t.size();i++)
    {
        if ((t[i]->Getnum())==(j->Getnum()))
        {
            if ((i==(t.size()-1)))
            {
                return t[0];
            }
            else
            {
               return t[i+1] ;
            }

        }
    }
}

Joueur* get_prev(vector<Joueur*>& t , Joueur* j)
{   int i ;
    for(i=0;i<t.size();i++)
    {
        if ((t[i]->Getnum())==(j->Getnum()))
        {
            if (i==0)
            {
                return t[(t.size())-1];
            }
            else
            {  return t[i-1] ;

            }

        }
    }
}



int main()
{

    vector<Joueur*> tableau_joueurs;//construction de tableau de joeurs
    vector<Joueur*> tableau_resreve;
    Partie p;
    int j=0;



    vector<Carte> v; // un tableau � remplir des cartes
    vector<string> TabSym = {"Coeur","pique","trefle","carreau"};
    vector<int> TabNum={6,7,8,9,10,11,12,13,1};
    vector<Carte> PileBioche;
    Creation_Pile(PileBioche,TabSym,TabNum);

    Bioche b(PileBioche);

    bool Z=true;
    bool w=true;

    int numero;
    string symbole1;
    Carte ATOUT(numero,symbole1);
    int he=0;
    int z;

    int n;
    cout<<"CHOOSE THE NUMBER OF PLAYER (2/3/4):"<<endl;
    cout<<"------------------------------------------------------------------------------------------------------------------------";
    cin>>n;
    int m=n;
    while(n<2||n>4)
    {  
        cout<<"WRONG CHOICE !THE NUMBER HAS TO BE (2/3/4) !!"<<endl;
        cout<<"TRY AGAIN"<<endl;
        cout<<"------------------------------------------------------------------------------------------------------------------------";
        cin>>n;
    }

     if (n==2)
    {

        Joueur* j1= new Joueur("normal",1,1);
        addJoueur(tableau_joueurs,j1);

        addJoueur2(tableau_resreve,j1);
        Joueur* j2=new Joueur("normal",1,2);
        addJoueur(tableau_joueurs,j2);
        addJoueur2(tableau_resreve,j2);

        for(int i=0 ; i<6 ; i++)
        {
            b.Distribuer1(*j1);
            b.Distribuer1(*j2);

        }
    }

    else if(n==3)
    {
        Joueur* j1=new Joueur("normal",1,1);
        addJoueur(tableau_joueurs,j1);
        addJoueur2(tableau_resreve,j1);
        Joueur* j2=new Joueur("normal",1,2);
        addJoueur(tableau_joueurs,j2);
        addJoueur2(tableau_resreve,j2);
        Joueur* j3=new Joueur("normal",1,3);
        addJoueur(tableau_joueurs,j3);
        addJoueur2(tableau_resreve,j3);
        for(int i=0 ; i<6 ; i++)
        {
            b.Distribuer1(*j1);
            b.Distribuer1(*j2);
            b.Distribuer1(*j3);
        }
    }
    else if(n==4)
    {

            Joueur* j1=new Joueur("normal",1,1);
            addJoueur(tableau_joueurs,j1);
            addJoueur2(tableau_resreve,j1);
            Joueur* j2=new Joueur("normal",1,2);
            addJoueur(tableau_joueurs,j2);
            addJoueur2(tableau_resreve,j2);
            Joueur* j3=new Joueur("normal",1,3);
            addJoueur(tableau_joueurs,j3);
            addJoueur2(tableau_resreve,j3);
            Joueur* j4=new Joueur("normal",1,4);
            addJoueur(tableau_joueurs,j4);
            addJoueur2(tableau_resreve,j4);


       for(int i=0 ; i<6 ; i++)
        {
            b.Distribuer1(*j1);
            b.Distribuer1(*j2);
            b.Distribuer1(*j3);
            b.Distribuer1(*j4);
         }
    }

     ATOUT=b.getDernierCarte(); //ATOUT

    //Joueur* attaquant=FirstPlayer(tableau_joueurs,ATOUT.GetSymbole());
    cout<<"THE ATTOT CARD IS : "<<endl;
    sleep(0.85);
    AffichageCarte(ATOUT);
    sleep(0.85);
    cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;


    string symbole;
    symbole=ATOUT.GetSymbole();
    cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"HERE WE GO !! GOOD LUCK !"<<endl;
    sleep(0.85);
    cout<<"------------------------------------------------------------------------------------------------------------------------";

        while(tableau_joueurs.size()>1)

       {
          /* for (Joueur *j : tableau_joueurs)
          {


              if (j->Getnum()==attaquant->Getnum())
                {

                    he++;
                }
          }*/


        actualiser(tableau_joueurs);
        n=tableau_joueurs.size();


        tour_de_table(w,n,tableau_joueurs,tableau_resreve,symbole,p,tableau_joueurs[0],b) ;


        
           if(b.nbre_des_cartes()!=0)
           { 
            for(int i=0;i<tableau_joueurs.size();i++)
           {   while((tableau_joueurs[i]->nbre()<6)&&(b.nbre_des_cartes()!=0))
                { b.Distribuer2(tableau_joueurs[i]);
             
                }
               
               
           }

           }
           

       }
     cout<<"THE END OF A GREAT BATTLE !! "<<endl;
     sleep(0.85);
      cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
       if(g=m)
       {
        cout<<"WHAT A LOSER YOU ARE!! EVRYONE S BEFORE YOU !!\n"<<endl;
        
         cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
       }          
       if(g==0)
       {
           cout<<"YOU ARE SUCH A GREAT PLAYER !!"<<endl;
           
          cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
       }
       if(g==1)
       {
           cout<<"YOU WERE TOO CLOSE TO WIN!! GG"<<endl;
           
            cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
       }
       cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;
       cout<<"YOUR RANK IS !! ("<<g<<") OUT OF ("<<m<<") player"<<endl;
      
       cout<<"------------------------------------------------------------------------------------------------------------------------"<<endl;

    return 0;
}



