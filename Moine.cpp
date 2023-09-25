#include <SDL2/SDL_image.h>
#include "Personnage.h"
#include "Moine.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

Moine::Moine() : Personnage()
{
    nom="ALMONI";
    prenom="Sheryfa";
    classe="Moine";
    pv= 150;
    pm= 90;
    fr= 25;
    def= 15;
    mag= 25;
    vol= 20;
    vit= 35;
    cha= 10;
    esq= 30.5;
    prc= 100;
    niv=1;
    exp=0;
    seuil=15;
    maxPv=150;
    maxPm=90;
    Gant arme;
    armeEquipe= arme;
    armureEquipe.push_back(casqueEquipe);
    armureEquipe.push_back(cuirasseEquipe);
    armureEquipe.push_back(bouclierEquipe);
    armureEquipe.push_back(jambiereEquipe);
    armeEquipable="Gant";
    armureEquipable[0]="Standard";
    armureEquipable[1]="Leger";
}

int Moine::Aura(Personnage &cible, Moine &attaquant)
{
    int base=0, resultat=0, consomation=25;
    if(attaquant.pm-consomation <0)
    {
        cout<<"Vous n'avez pas assez de PM"<<endl;;
        return resultat;
    }
    else
    {
        base=(attaquant.fr+attaquant.mag)/2;
        resultat=cible.RecevoirDegatSpecial(armeEquipe.GetDegat(), attaquant.fr, base, "phy");
    }

    return resultat;
}

int Moine::Chakra(Personnage &cible, Moine &attaquant)
{
    int gain=0, consomation=20;
    if(attaquant.pm-consomation <0)
    {
        cout<<"Vous n'avez pas assez de PM"<<endl;;
        return gain;
    }
    else
    {
        gain=attaquant.mag+(attaquant.mag*0.5);
        cible.GainPv(gain);
        cible.GainPm(gain/2);
        if(attaquant.pv > attaquant.maxPv)
        {
            attaquant.pv=attaquant.maxPv;
        }
        if(attaquant.pm > attaquant.maxPm)
        {
            attaquant.pm=attaquant.maxPm;
        }
        return gain;
    }
}

int Moine::Concentration(Moine &cible, Moine &attaquant)
{
    int gain=0, consomation=30;
    if(attaquant.pm-consomation <0)
    {
        cout<<"Vous n'avez plus de PM"<<endl;;
        return gain;
    }
    else
    {
        gain=((cible.fr+cible.mag)/2)*0.25;
        cible.GainFr(gain);
        cible.GainMag(gain);
        return gain;
    }
}

