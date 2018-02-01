#include <SDL/SDL_image.h>
#include "Personnage.h"
#include <string>
#include <iostream>
#include "ChevalierDragon.h"
#include "Lance.h"
#include "Casque.h"
#include <vector>
using namespace std;

ChevalierDragon::ChevalierDragon():Personnage()
{
    nom="DRAGNIR";
    prenom="Sherao";
    classe="Chevalier dragon";
    pv= 200;
    pm= 50;
    fr= 20;
    def= 20;
    mag= 15;
    vol= 10;
    vit= 20;
    cha= 5;
    esq= 11.5;
    prc= 100;
    niv=1;
    exp=0;
    seuil=30;
    maxPv=200;
    maxPm=50;
    Lance arme;
    armeEquipe= arme;
    Casque *ca=new Casque("Casque or", "Lourd");
    casqueEquipe=*ca;
    armureEquipe.push_back(casqueEquipe);
    armureEquipe.push_back(cuirasseEquipe);
    armureEquipe.push_back(bouclierEquipe);
    armureEquipe.push_back(jambiereEquipe);
    armeEquipable="Lance";
    armureEquipable[0]="Standard";
    armureEquipable[1]="Lourd";
}

int ChevalierDragon::CriDuDragon(Personnage &cible, ChevalierDragon &attaquant)
{
    int gain=0, consomation=40;
    if(attaquant.pm-consomation <0)
    {
        cout<<"Vous n'avez plus de PM"<<endl;;
        return gain;
    }
    else
    {
        gain=attaquant.niv*5;
        cible.GainFr(gain);
        attaquant.pm -=consomation;
        return gain;
    }

}

int ChevalierDragon::ChargeDuDragon(Personnage &cible, ChevalierDragon &attaquant)
{
    int base=0, resultat=0;
    base=attaquant.niv*10;
    resultat=cible.RecevoirDegatSpecial(0, attaquant.mag, base, "ryuken");
    attaquant.GainPv(resultat);
    attaquant.GainPm(resultat);
    if(attaquant.pv > attaquant.maxPv)
    {
        attaquant.pv=attaquant.maxPv;
    }
    if(attaquant.pm > attaquant.maxPm)
    {
        attaquant.pm=attaquant.maxPm;
    }
    return resultat;
}

int ChevalierDragon::Saut(Personnage &cible, ChevalierDragon &attaquant)
{
    int base=0, resultat=0;
    base=(attaquant.fr+attaquant.vit)/2;
    resultat=cible.RecevoirDegatSpecial(armeEquipe.GetDegat(), attaquant.fr, base, "phy");
    return resultat;
}
