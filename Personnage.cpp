#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Personnage.h"
#include "Constantes.h"
#include <string>
#include <iostream>
using namespace std;

//Définition du constructeur de la classe personnage
Personnage::Personnage()
{
    nom="roman";
    prenom ="jose";
    pv= 150;
    pm= 20;
    fr= 5;
    def= 3;
    niv=1;
    maxPv=150;
    maxPm=20;
    exp=0;
    seuil=100;

}

//Surdéfinition du constructeur de la classe personnage
Personnage::Personnage(string n, string p)
{
    nom=n;
    prenom=p;
    pv= 150;
    pm= 20;
    fr= 4;
    def= 2;
    niv=1;
    maxPv=150;
    maxPm=20;
    exp=0;
    seuil=100;

}

//Fonction permettant à un personnage d'attaquer
void Personnage::Attaquer(Personnage &cible, Personnage &attaquant, Arme &armUtilise)
{
    //Appel de la fonction permettant de recevoir des dégats
    cible.RecevoirDegat(armeEquipe.GetDegat(), attaquant.fr);

}

//Définition d'une fonction permettant à un personnage de recevoir des dégats normaux
int Personnage::RecevoirDegat(int degatArme, int forceAdversaire)
{
    int degatRixe= 0, degatEncaisse=0;
    degatRixe=degatArme+forceAdversaire;
    degatEncaisse=degatRixe-(def+casqueEquipe.GetDefPhy()+cuirasseEquipe.GetDefPhy()+bouclierEquipe.GetDefPhy()+jambiereEquipe.GetDefPhy());
    if(degatEncaisse<0)
    {
        degatEncaisse=0;
    }

    pv -=degatEncaisse;

    if(pv<0)
    {
        pv=0;
    }

    return (degatEncaisse);
}

//Définition d'une fonction permettant à un personnage de recevoir des dégats spéciaux
int Personnage::RecevoirDegatSpecial(int degatArme, int CaractAdversaire, int base, std::string nature)
{
    int degatRixe= 0, degatEncaisse=0;

    if (nature=="phy")
    {
        //calcul permettant d'obtenir les dégats du combat
        degatRixe=degatArme+CaractAdversaire+base;
        //calcul permettant d'obtenir les dégats réels subits par les personnages
        degatEncaisse=degatRixe-(def+casqueEquipe.GetDefPhy()+cuirasseEquipe.GetDefPhy()+bouclierEquipe.GetDefPhy()+jambiereEquipe.GetDefPhy());

        //Test permettant d'éviter les dégats négatifs
        if(degatEncaisse<0)
        {
            degatEncaisse=0;
        }

        pv -=degatEncaisse;
        //Test permettant d'éviter les points de vie négatifs
        if(pv<0)
        {
            pv=0;
        }
    }
    else if(nature=="mag")
    {
        //calcul permettant d'obtenir les dégats du combat
        degatRixe=CaractAdversaire+base;

        //calcul permettant d'obtenir les dégats réels subits par les personnages
        degatEncaisse=degatRixe-(vol+casqueEquipe.GetDefMag()+cuirasseEquipe.GetDefMag()+bouclierEquipe.GetDefMag()+jambiereEquipe.GetDefMag());

        //Test permettant d'éviter les dégats négatifs
        if(degatEncaisse<0)
        {
            degatEncaisse=0;
        }

        pv -=degatEncaisse;
        //Test permettant d'éviter les points de vie négatifs
        if(pv<0)
        {
            pv=0;
        }
    }
    else if(nature=="ryuken")
    {
        //calcul permettant d'obtenir les dégats du combat
        degatRixe=CaractAdversaire+base;
        //calcul permettant d'obtenir les dégats réels subits par les personnages
        degatEncaisse=degatRixe-(vol+casqueEquipe.GetDefMag()+cuirasseEquipe.GetDefMag()+bouclierEquipe.GetDefMag()+jambiereEquipe.GetDefMag());

        //Test permettant d'éviter les dégats négatifs
        if(degatEncaisse<0)
        {
            degatEncaisse=0;
        }

        pm -=degatEncaisse;
        pv -=degatEncaisse;
        //Test permettant d'éviter les points de vie négatifs
        if(pv<0)
        {
            pv=0;
        }
        //Test permettant d'éviter les points de magie négatifs
        if(pm<0)
        {
            pm=0;
        }
    }
    return (degatEncaisse);
}

//Définition d'une fonction permettant l'affichage du status du personnage
void Personnage::AffichageEtat()
{
    cout<<"     STATUS      "<<endl;
    cout<<""<<endl;
    cout<<"Nom : "<< nom <<endl;
    cout<<"Prenom : "<< prenom <<endl;
    cout<<"PV: "<< pv <<endl;
    cout<<"PM : "<< pm <<endl;
    cout<<"FORCE : "<< fr <<endl;
    cout<<"DEFENSE : "<< def <<endl;
    cout<<"MAGIE : "<< mag <<endl;
    cout<<"VOLONTE : "<< vol <<endl;
    cout<<"NIVEAU : "<< niv <<endl;
    cout<<"EXPERIENCE : "<< exp <<endl;
    cout<<"EXPERIENCE POUR LE PROCHAIN NIVEAU : "<< seuil <<endl;
    cout<<"ARME EQUIPE : "<<armeEquipe.GetNom()<<endl;
    cout<<""<<endl;
}

int Personnage::GainFr(int bonus)
{
        fr +=bonus;
        return bonus;
}

int Personnage::GainEsq(int bonus)
{
        esq +=bonus;
        return bonus;
}

int Personnage::GainPv(int bonus)
{
        pv +=bonus;
        return bonus;
}

int Personnage::GainPm(int bonus)
{
        pm +=bonus;
        return bonus;
}

int Personnage::GainCha(int bonus)
{
        cha +=bonus;
        return bonus;
}

int Personnage::GainPrc(int bonus)
{
        prc +=bonus;
        return bonus;
}

int Personnage::GainDef(int bonus)
{
        def +=bonus;
        return bonus;
}

int Personnage::GainVol(int bonus)
{
        vol +=bonus;
        return bonus;
}

int Personnage::GainVit(int bonus)
{
        vit +=bonus;
        return bonus;
}

int Personnage::GainNiv(int bonus)
{
        niv +=bonus;
        return bonus;
}

int Personnage::GainMag(int bonus)
{
        mag +=bonus;
        return bonus;
}

int Personnage::ChangementSeuil(int nouvelleValeur)
{
    seuil= nouvelleValeur;
    return seuil;
}

int Personnage::GainExp(int gain)
{
    exp += gain;
    return gain;
}

void Personnage::EquiperArme(Arme &nouvelleArme)
{
    armeEquipe=nouvelleArme;
}

void Personnage::EquiperCasque(Casque &nouveauCasque)
{
    casqueEquipe=nouveauCasque;
}

void Personnage::EquiperCuirasse(Cuirasse &nouvelleCuirasse)
{
    cuirasseEquipe=nouvelleCuirasse;
}

void Personnage::EquiperBouclier(Bouclier &nouveauBouclier)
{
    bouclierEquipe=nouveauBouclier;
}

void Personnage::EquiperJambiere(Jambiere &nouvelleJambiere)
{
    jambiereEquipe=nouvelleJambiere;
}

int Personnage::UtiliserObjet(Personnage &cible, Potion &objet)
{
    std::string impact;
    int bonus=0;
    impact=objet.GetAction();
    bonus=objet.GetEffet();
    if(impact=="PV")
    {
        cible.GainPv(bonus);
        if(cible.pv > cible.maxPv)
        {
            cible.pv=cible.maxPv;
        }
    }

    else if(impact=="PM")
    {
        cible.GainPm(bonus);
        if(cible.pm > cible.maxPm)
        {
            cible.pm=cible.maxPm;
        }
    }

    return bonus;
}

void Personnage::NiveauAcquis()
{
    int tab[4], i=1;
    //Tab contient les différents seuils d'expérience du personnage (ceci évoluera dans la version final)
    tab[0]=30;
    tab[1]=100;
    tab[2]=200;
    tab[3]=300;

    //Boucle permettant l'augmentation du niveau tant que le seuil est dépassé
    while(exp >= seuil)
    {
        this->GainNiv(1);
        this->GainPv(10);
        this->GainPm(2);
        this->GainFr(3);
        this->GainDef(5);
        this->GainVol(1);
        this->ChangementSeuil(tab[i++]);
        if(exp < seuil)
        {
            cout<<"LE PERSONNAGE "<<prenom<<" EST PASSE AU NIVEAU "<<niv<< endl;
            cout<<""<<endl;
        }
    }

}

int Personnage::GetPv()
{
    return pv;
}

int Personnage::GetPm()
{
    return pm;
}

int Personnage::GetMaxPv()
{
    return maxPv;
}

int Personnage::GetMaxPm()
{
    return maxPm;
}

int Personnage::GetExp()
{
    return exp;
}

int Personnage::GetSeuil()
{
    return seuil;
}

int Personnage::GetFr()
{
    return fr;
}

int Personnage::GetDef()
{
    return def;
}

int Personnage::GetMag()
{
    return mag;
}

int Personnage::GetVol()
{
    return vol;
}

int Personnage::GetVit()
{
    return vit;
}

float Personnage::GetEsq()
{
    return esq;
}

float Personnage::GetPrc()
{
    return prc;
}

int Personnage::GetCha()
{
    return cha;
}

int Personnage::GetNiv()
{
    return niv;
}

std::string Personnage::GetNom()
{
    return nom;
}

std::string Personnage::GetPrenom()
{
    return prenom;
}

std::string Personnage::GetClasse()
{
    return classe;
}

Arme Personnage::GetArmeEquipe()
{
    return armeEquipe;
}

Casque Personnage::GetCasqueEquipe()
{
    return casqueEquipe;
}

Cuirasse Personnage::GetCuirasseEquipe()
{
    return cuirasseEquipe;
}

Bouclier Personnage::GetBouclierEquipe()
{
    return bouclierEquipe;
}

Jambiere Personnage::GetJambiereEquipe()
{
    return jambiereEquipe;
}

std::vector<Equipement> Personnage::GetArmureEquipe()
{
    return armureEquipe;
}

std::string Personnage::GetArmeEquipable()
{
    return armeEquipable;
}

std::string *Personnage::GetArmureEquipable()
{
    return armureEquipable;
}

bool Personnage::IsEquipable(std::string type)
{
    if(type==armureEquipable[0])
    {
        return 1;
    }
    else if(type==armureEquipable[1])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Personnage::ModifierArmure(Armure &pieceArmure)
{
    if(pieceArmure.GetCategorie()=="Casque")
    {
        armureEquipe[CASQUE]=pieceArmure;
    }
    else if(pieceArmure.GetCategorie()=="Cuirasse")
    {
        armureEquipe[CUIRASSE]=pieceArmure;
    }
    else if(pieceArmure.GetCategorie()=="Bouclier")
    {
        armureEquipe[BOUCLIER]=pieceArmure;
    }
    else if(pieceArmure.GetCategorie()=="Jambiere")
    {
        armureEquipe[JAMBIERE]=pieceArmure;
    }
    else
    {

    }
}
